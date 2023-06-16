#include <lib.h>

int flag[256];



void tree(char *path, char *prefix, int depth) {
	int fd, n;
	struct File f;
	struct Fd *fileDis;

	if ((fd = open(path, O_RDONLY)) < 0) {
		user_panic("open %s: %d", path, fd);
	}

	while ((n = readn(fd, &f, sizeof f)) == sizeof f) {

		if (f.f_name[0] && (f.f_name[0] != '.' || flag['a'])) {
			if (f.f_type == FTYPE_DIR) {
				char new_path[128];
				for (int i = 0; i < depth; i++){
					printf("│   ");
				}
				printf("├── ");
				if (flag['f']) printf("%s", path);
				printf("%s\n", f.f_name);
				strcpy(new_path, path);
				strcat(new_path, f.f_name);
				if (strcmp(new_path, "/"))
					strcat(new_path, "/");
				tree(new_path, prefix, depth + 1);
			} else if (!flag['d']) {
				for (int i = 0; i < depth; i++){
					printf("│   ");
				}
				printf("├── ");
				if (flag['f']) printf("%s", path);
				printf("%s\n", f.f_name);
			}
		}
	}


	if (n > 0) {
		user_panic("short read in directory %s", path);
	}
	if (n < 0) {
		user_panic("error reading directory %s: %d", path, n);
	}
}

void usage(void) {
	printf("usage: tree [-daf] [file...]\n");
	exit();
}

int main(int argc, char **argv) {
	int i;

	ARGBEGIN {
	default:
		usage();
	case 'd':
	case 'f':
	case 'a':
		flag[(u_char)ARGC()]++;
		break;
	}
	ARGEND

	if (argc == 0) {
		printf(".\n");

		char path[100];
		memset(path, 0, sizeof path);
		syscall_get_cwd(0, path);
		if (strcmp(path, "/"))
			strcat(path, "/");

		tree(path, path, 0);
	} else {
		printf("%s\n", argv[0]);

		char path[100];
		memset(path, 0, sizeof path);	
		strcpy(path, argv[0]);
		if (strcmp(path, "/"))
			strcat(path, "/");
		
		tree(path, path, 0);
	}
	printf("\n");
	return 0;
}
