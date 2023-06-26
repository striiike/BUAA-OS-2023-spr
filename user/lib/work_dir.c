#include <lib.h>


void cd(u_int envid, char *buf) {

    char full_path[100];
	memset(full_path, 0, sizeof full_path);
	if (buf[0] == '/') {
		strcpy(full_path, buf);
	} else {
		syscall_get_cwd(0, full_path);
		if (strcmp(full_path, "/"))
			strcat(full_path, "/");
		strcat(full_path, buf);
	}

    syscall_ch_dir(envid, full_path);
}

void pwd(u_int envid, char *buf) {

    char back[100];
    memset(back, 0, sizeof back);
    syscall_get_cwd(envid, back);
    printf("%s\n", back);
}