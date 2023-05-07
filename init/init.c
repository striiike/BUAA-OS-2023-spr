#include <asm/asm.h>
#include <env.h>
#include <kclock.h>
#include <pmap.h>
#include <printk.h>
#include <trap.h>

// When build with 'make test lab=?_?', we will replace your 'mips_init' with a generated one from
// 'tests/lab?_?'.
#ifdef MOS_INIT_OVERRIDDEN
#include <generated/init_override.h>
#else

extern void test_mips(int hello);

void mips_init() {

	test_mips(0x87654321);

	printk("init.c:\tmips_init() is called\n");

	printk("init.c:\tmips_init() is called\n");
    mips_detect_memory();
    mips_vm_init();
    page_init();
    env_init();
    ENV_CREATE(user_shmtest);
    kclock_init();
	enable_irq();
    while(1);
    panic("init.c:\tend of mips_init() reached!");


}

#endif
