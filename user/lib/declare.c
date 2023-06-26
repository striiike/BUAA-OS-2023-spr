#include <lib.h>


void declare_var(u_int envid, char *buf, char *value, int isLocal, int readOnly) {
    syscall_declare_var(envid, buf, value, isLocal, readOnly);
}

void declare_all(u_int envid) {
    syscall_declare_all(envid);
}

void unset_var(u_int envid, char *buf) {
    syscall_unset_var(envid, buf);
}

void get_var(u_int envid, char *buf, char *back) {
    syscall_get_var(envid, buf, back);
}