#include <lib.h>

int main() {
	barrier_alloc(5);

	
	for (int i = 0; i < 6; i++) {
		int who = fork();
		if (who == 0) {
			debugf("I'm son!\n");
			barrier_wait();
			debugf("wake\n");
			//syscall_panic("Wrong block!");
		}
	}

	debugf("I'm finished!\n");
	return 0;
}
