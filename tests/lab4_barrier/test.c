#include <lib.h>

int main() {
	barrier_alloc(5);

	
	for (int i = 0; i < 20; i++) {
		int who = fork();
		if (who == 0) {
			if (i > 100) continue;
			debugf("I'm son!%d\n", i);
			barrier_wait();
			debugf("wake\n");
			//syscall_panic("Wrong block!");
		}
	}

	debugf("I'm finished!\n");
	return 0;
}
