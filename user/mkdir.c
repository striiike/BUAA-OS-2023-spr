#include <lib.h>

int flag[256];

char path1[50];
char path2[50];
char buf[20];

void usage(void) {
	printf("usage: mkdir [-p] [file...]\n");
	exit();
}

int main(int argc, char **argv) {
	int i;

	ARGBEGIN {
	default:
		usage();
	case 'p':
		flag[(u_char)ARGC()]++;
		break;
	}
	ARGEND

    int mark = 0;
    int len = 0;
    int buflen = 0;



    for (i = 0; argv[0][i] != '\n' && argv[0][i] != '\0'; i++) {
        
        if (argv[0][i] == '/') {
            strcat(path1, buf);
            memset(buf, 0, sizeof buf);
            buflen = 0;
            mark = 1;
        } 
        
        buf[buflen++] = argv[0][i];
        
    }

    if (!mark) strcpy(path1, argv[0]);


    if (flag['p']) {
        open(path1, O_MKDIR);
        open(argv[0], O_MKDIR);
    } else {
        int r = open(path1, O_RDONLY);
        if (r < 0 && strcmp(path1, argv[0])) {
            printf("Error: can't parse!\n");
            return 0;
        }
        open(argv[0], O_MKDIR);
    }

	return 0;
}
