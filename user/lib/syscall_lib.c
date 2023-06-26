#include <env.h>
#include <lib.h>
#include <mmu.h>
#include <syscall.h>
#include <trap.h>

void syscall_putchar(int ch) {
	msyscall(SYS_putchar, ch);
}

int syscall_print_cons(const void *str, u_int num) {
	return msyscall(SYS_print_cons, str, num);
}

u_int syscall_getenvid(void) {
	return msyscall(SYS_getenvid);
}

void syscall_yield(void) {
	msyscall(SYS_yield);
}

int syscall_env_destroy(u_int envid) {
	return msyscall(SYS_env_destroy, envid);
}

int syscall_set_tlb_mod_entry(u_int envid, void (*func)(struct Trapframe *)) {
	return msyscall(SYS_set_tlb_mod_entry, envid, func);
}

int syscall_mem_alloc(u_int envid, void *va, u_int perm) {
	return msyscall(SYS_mem_alloc, envid, va, perm);
}

int syscall_mem_map(u_int srcid, void *srcva, u_int dstid, void *dstva, u_int perm) {
	return msyscall(SYS_mem_map, srcid, srcva, dstid, dstva, perm);
}

int syscall_mem_unmap(u_int envid, void *va) {
	return msyscall(SYS_mem_unmap, envid, va);
}

int syscall_set_env_status(u_int envid, u_int status) {
	return msyscall(SYS_set_env_status, envid, status);
}

int syscall_set_trapframe(u_int envid, struct Trapframe *tf) {
	return msyscall(SYS_set_trapframe, envid, tf);
}

void syscall_panic(const char *msg) {
	int r = msyscall(SYS_panic, msg);
	user_panic("SYS_panic returned %d", r);
}

int syscall_ipc_try_send(u_int envid, u_int value, const void *srcva, u_int perm) {
	return msyscall(SYS_ipc_try_send, envid, value, srcva, perm);
}

int syscall_ipc_recv(void *dstva) {
	return msyscall(SYS_ipc_recv, dstva);
}

int syscall_cgetc() {
	return msyscall(SYS_cgetc);
}

int syscall_write_dev(void *va, u_int dev, u_int len) {
	/* Exercise 5.2: Your code here. (1/2) */

	return msyscall(SYS_write_dev, va, dev, len);
}

int syscall_read_dev(void *va, u_int dev, u_int len) {
	/* Exercise 5.2: Your code here. (2/2) */

	return msyscall(SYS_read_dev, va, dev, len);
}


void syscall_ch_dir(u_int envid, char *buf) {
	msyscall(SYS_ch_dir, envid, buf);
}


void syscall_get_cwd(u_int envid, char *back) {
	msyscall(SYS_get_cwd, envid, back);
}

void syscall_declare_all(u_int envid) {
	msyscall(SYS_declare_all, envid);
}

void syscall_declare_var(u_int envid, char *buf, char *value, int isLocal, int readOnly) {
	msyscall(SYS_declare_var, envid, buf, value, isLocal, readOnly);
}

void syscall_unset_var(u_int envid, char *buf) {
	msyscall(SYS_unset_var, envid, buf);
}

void syscall_get_var(u_int envid, char *buf, char *back) {
	msyscall(SYS_get_var, envid, buf, back);
}

int syscall_shell_id_alloc() {
	msyscall(SYS_shell_id_alloc);
}

void syscall_destroy_shell(u_int shellid) {
	msyscall(SYS_destroy_shell, shellid);
}