// User-level IPC library routines

#include <env.h>
#include <lib.h>
#include <mmu.h>

// Send val to whom.  This function keeps trying until
// it succeeds.  It should panic() on any error other than
// -E_IPC_NOT_RECV.
//
// Hint: use syscall_yield() to be CPU-friendly.
void ipc_send(u_int whom, u_int val, const void *srcva, u_int perm) {
	int r;
	while ((r = syscall_ipc_try_send(whom, val, srcva, perm)) == -E_IPC_NOT_RECV) {
		syscall_yield();
	}
	user_assert(r == 0);
}

// Receive a value.  Return the value and store the caller's envid
// in *whom.
//
// Hint: use env to discover the value and who sent it.
u_int ipc_recv(u_int *whom, void *dstva, u_int *perm) {
	int r = syscall_ipc_recv(dstva);
	if (r != 0) {
		user_panic("syscall_ipc_recv err: %d", r);
	}

	if (whom) {
		*whom = env->env_ipc_from;
	}

	if (perm) {
		*perm = env->env_ipc_perm;
	}

	return env->env_ipc_value;
}

static int block = 0;

void barrier_alloc (int n){
	block = n;
	syscall_write_dev(0, 0, n);
	// debugf("%d %d %d\n", block, syscall_read_dev(0, 0, 0), n);
}	




void barrier_wait(void) {
	
	//syscall_read_dev(0, 2, 0);

	syscall_read_dev(0,1,0);
	/*int blockNum = syscall_read_dev(0, 0, 0);
	//block--;
	if (blockNum <= 0 || block <= 0){ 
		syscall_yield();
		return;}
	*/
	int r;
	while((r = syscall_read_dev(0, 0, 0)) > 0 ) {
	// 	debugf("%d %d\n", r, r); 
		if (r > 0) {syscall_yield();}
	
	}
	 /*while(block > 0 ) {
                debugf("%d %d\n", block, block); 
                if (block > 0) {syscall_yield();}
        
        }*/
	// syscall_yield();
}






