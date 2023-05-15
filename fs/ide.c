/*
 * operations on IDE disk.
 */

#include "serv.h"
#include <drivers/dev_disk.h>
#include <lib.h>
#include <mmu.h>

int user_cmp(void *a, void *b) {
	int i;
	char *c = (char *) a;
	char *d = (char *) b;
	for (i = 0; i < 512; i++) {
		if (c[i] != d[i]) {
			break;
		}
	}
	if (i == 512) {
		return 1;
	}
	return 0;
}

// Overview:
//  read data from IDE disk. First issue a read request through
//  disk register and then copy data from disk buffer
//  (512 bytes, a sector) to destination array.
//
// Parameters:
//  diskno: disk number.
//  secno: start sector number.
//  dst: destination for data read from IDE disk.
//  nsecs: the number of sectors to read.
//
// Post-Condition:
//  Panic if any error occurs. (you may want to use 'panic_on')
//
// Hint: Use syscalls to access device registers and buffers.
// Hint: Use the physical address and offsets defined in 'include/drivers/dev_disk.h':
//  'DEV_DISK_ADDRESS', 'DEV_DISK_ID', 'DEV_DISK_OFFSET', 'DEV_DISK_OPERATION_READ',
//  'DEV_DISK_START_OPERATION', 'DEV_DISK_STATUS', 'DEV_DISK_BUFFER'
void ide_read(u_int diskno, u_int secno, void *dst, u_int nsecs) {
	u_int begin = secno * BY2SECT;
	u_int end = begin + nsecs * BY2SECT;

	for (u_int off = 0; begin + off < end; off += BY2SECT) {
		uint32_t temp = diskno;
		/* Exercise 5.3: Your code here. (1/2) */

		panic_on(syscall_write_dev(&temp, DEV_DISK_ADDRESS + DEV_DISK_ID, 4));
		temp = begin + off;
		panic_on(syscall_write_dev(&temp, DEV_DISK_ADDRESS + DEV_DISK_OFFSET, 4));
		temp = DEV_DISK_OPERATION_READ;
		panic_on(syscall_write_dev(&temp, DEV_DISK_ADDRESS + DEV_DISK_START_OPERATION, 4));

		uint32_t flag;
		panic_on(syscall_read_dev(&flag, DEV_DISK_ADDRESS + DEV_DISK_STATUS, 4));
		if (flag == 0) {
			panic_on("Error: Fail to Ide_read\n");
		}
		panic_on(syscall_read_dev(dst + off, DEV_DISK_ADDRESS + DEV_DISK_BUFFER, DEV_DISK_BUFFER_LEN));

	}
}

// Overview:
//  write data to IDE disk.
//
// Parameters:
//  diskno: disk number.
//  secno: start sector number.
//  src: the source data to write into IDE disk.
//  nsecs: the number of sectors to write.
//
// Post-Condition:
//  Panic if any error occurs.
//
// Hint: Use syscalls to access device registers and buffers.
// Hint: Use the physical address and offsets defined in 'include/drivers/dev_disk.h':
//  'DEV_DISK_ADDRESS', 'DEV_DISK_ID', 'DEV_DISK_OFFSET', 'DEV_DISK_BUFFER',
//  'DEV_DISK_OPERATION_WRITE', 'DEV_DISK_START_OPERATION', 'DEV_DISK_STATUS'
void ide_write(u_int diskno, u_int secno, void *src, u_int nsecs) {
	u_int begin = secno * BY2SECT;
	u_int end = begin + nsecs * BY2SECT;

	for (u_int off = 0; begin + off < end; off += BY2SECT) {
		uint32_t temp = diskno;
		/* Exercise 5.3: Your code here. (2/2) */

		panic_on(syscall_write_dev(&temp, DEV_DISK_ADDRESS + DEV_DISK_ID, 4));
		temp = begin + off;
		panic_on(syscall_write_dev(&temp, DEV_DISK_ADDRESS + DEV_DISK_OFFSET, 4));
		panic_on(syscall_write_dev(src + off, DEV_DISK_ADDRESS + DEV_DISK_BUFFER, DEV_DISK_BUFFER_LEN));
		temp = DEV_DISK_OPERATION_WRITE;
		panic_on(syscall_write_dev(&temp, DEV_DISK_ADDRESS + DEV_DISK_START_OPERATION, 4));
		

		uint32_t flag;
		panic_on(syscall_read_dev(&flag, DEV_DISK_ADDRESS + DEV_DISK_STATUS, 4));
		if (flag == 0) {
			panic_on("Error: Fail to Ide_write\n");
		}
		
	}
}

int map[50];
int map_reverse[50];
int able[50];
int erase_n[50];

void ssd_init() {
	memset(map, -1, sizeof(map));
	memset(map_reverse, -1, sizeof(map_reverse));
	memset(able, 1, sizeof(able));
	memset(erase_n, 0, sizeof(erase_n));

}

int ssd_read(u_int logic_no, void *dst) {
	if (map[logic_no] == -1) {
		return -1;
	}
	ide_read(0, map[logic_no], dst, 1);
	return 0;
}

int find() {
	for (int i = 0; i < 32; i++) {
		if (map_reverse[i] == -1 && able[i] == 1) {
			return i;
		}	
	}
}


void ssd_write(u_int logic_no, void *src) {
	int alloc;
	int phy_no = map[logic_no];
	if (phy_no == -1) {
		
	} else {
		ssd_erase(logic_no);
	}
	alloc = find();

	map[logic_no] = alloc;
	map_reverse[alloc] = logic_no;

	ide_write(0, alloc, src, 1);

	able[alloc] = 0;
}

void ssd_erase(u_int logic_no) {
	if (map[logic_no] == -1) {
		return;
	} else {
		int phy_no = map[logic_no];

		map[logic_no] = -1;
		map_reverse[phy_no] = -1;

		char tmp[512];
		memset(tmp, 0, sizeof(tmp));
		ide_write(0, phy_no, tmp, 1);

		erase_n[phy_no]++;

		able[phy_no] = 1;
	}

}











































