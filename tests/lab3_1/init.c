#include <debugk.h>
void mips_init() {
	printk("init.c:\tmips_init() is called\n");
	mips_detect_memory();
	mips_vm_init();
	page_init();

	DEBUGK("page_init success!\n");
	env_init();
	DEBUGK("env_init success!\n");
	env_check();
	halt();
}
