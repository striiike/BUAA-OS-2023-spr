#include <lib.h>
#include <drivers/dev_rtc.h>

int *sec = (int *)(UTEMP + DEV_RTC_SEC);
int *us = (int *)(UTEMP + DEV_RTC_USEC);

int main() {
        int r;
        if ((r = syscall_mem_alloc(0, (void *)UTEMP, PTE_D)) != 0) {
                user_panic("mem alloc: %d", r);
        }
        if ((r = fork()) < 0) {
                user_panic("fork: %d", r);
        }
        if (r == 0) {
                printf("I am child.\n");
                return 0;
        }
        if ((r = syscall_read_dev((void *)UTEMP, DEV_RTC_ADDRESS, 0x30)) != 0) {
                user_panic("read dev: %d", r);
        }
        printf("time: %d.%06ds\n", *sec, *us);
        printf("COW in kernel: Good!\n");
        return 0;
}
