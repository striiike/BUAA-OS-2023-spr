#include <lib.h>

int flag[256];



void usage(void) {
	printf("usage: touch [file...]\n");
	exit();
}

int main(int argc, char **argv) {
	int i;

	ARGBEGIN {
	default:
		usage();
		break;
	}
	ARGEND

	
    int fd = open(argv[0], O_CREAT);
    close(fd);

	return 0;
}
