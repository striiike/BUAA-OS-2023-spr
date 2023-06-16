#include "lib.h"

int main(int argc, char **argv) {
	int i, j, k;
	for (i = 0; i < 1000000000; i++) {
		if (i % 30000000 == 0) {
			debugf("\nI am running in background, i is %d\n", i);
		}
	}
	return 0;
}