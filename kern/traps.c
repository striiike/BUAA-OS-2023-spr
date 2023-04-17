#include <env.h>
#include <pmap.h>
#include <printk.h>
#include <trap.h>

extern void handle_int(void);
extern void handle_tlb(void);
extern void handle_sys(void);
extern void handle_mod(void);
extern void handle_reserved(void);
extern void handle_ov(void);

void (*exception_handlers[32])(void) = {
    [0 ... 31] = handle_reserved,
    [0] = handle_int,
    [2 ... 3] = handle_tlb,
#if !defined(LAB) || LAB >= 4
    [1] = handle_mod,
    [8] = handle_sys,
#endif
    [12] = handle_ov,
};

/* Overview:
 *   The fallback handler when an unknown exception code is encountered.
 *   'genex.S' wraps this function in 'handle_reserved'.
 */
void do_reserved(struct Trapframe *tf) {
	print_tf(tf);
	panic("Unknown ExcCode %2d", (tf->cp0_cause >> 2) & 0x1f);
}

void do_ov(struct Trapframe *tf) {
	
	u_int epc = tf->cp0_epc;
	struct Page *p;
	p = page_lookup(curenv->env_pgdir, epc, NULL);
	u_int epc_pa = (void *)page2pa(p) + (epc & 0xfff);
	u_int instr = *(u_int *)(KADDR(epc_pa));
	if (((instr & 0xfc000000) == 0x0) && ((instr & 0x0000003f) == 0x00000020)) {
		printk("add ov handled\n");
		instr |= 0x00000001;
		*(u_int *)(KADDR(epc_pa)) = instr;
	}	
	
	if (((instr & 0xfc000000) == 0x0) && ((instr & 0x0000003f) == 0x00000022)) {
		printk("sub ov handled\n");
		instr |= 0x1;
		*(u_int *)(KADDR(epc_pa)) = instr;
	}
	if (((instr & 0xfc000000) == 0x20000000)) {
		printk("addi ov handled\n");
		u_int t = ((instr >> 16)) & 0x1f;
		u_int s = (instr >> 21) & 0x1f;
		u_int imm = instr & 0xffff;
		tf->regs[t] = tf->regs[s] / 2 + imm / 2 ;
		tf->cp0_epc = 4;
	}
	// printk("test: %x %x %x\n", epc_pa, KADDR(epc_pa), *(u_int *)(KADDR(epc_pa)));
	// tf->cp0_epc += 4;
	curenv->env_ov_cnt++;
}

























