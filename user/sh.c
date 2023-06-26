#include <args.h>
#include <lib.h>
#include <cursor.h>

static char argv_shell[128][32];
static int shared[1024]; 


#define WHITESPACE " \t\r\n"
#define SYMBOLS "<|>&;()"

static int A[1024];
static int B[1024];
static int C[1024];
static int D[1024];

/* Overview:
 *   Parse the next token from the string at s.
 *
 * Post-Condition:
 *   Set '*p1' to the beginning of the token and '*p2' to just past the token.
 *   Return:
 *     - 0 if the end of string is reached.
 *     - '<' for < (stdin redirection).
 *     - '>' for > (stdout redirection).
 *     - '|' for | (pipe).
 *     - 'w' for a word (command, argument, or file name).
 *
 *   The buffer is modified to turn the spaces after words into zero bytes ('\0'), so that the
 *   returned token is a null-terminated string.
 */
// int _gettoken(char *s, char **p1, char **p2) {
// 	*p1 = 0;
// 	*p2 = 0;
// 	if (s == 0) {
// 		return 0;
// 	}

// 	while (strchr(WHITESPACE, *s)) {
// 		*s++ = 0;
// 	}
// 	if (*s == 0) {
// 		return 0;
// 	}

// 	if (strchr(SYMBOLS, *s)) {
// 		int t = *s;
// 		*p1 = s;
// 		*s++ = 0;
// 		*p2 = s;
// 		return t;
// 	}

// 	*p1 = s;
// 	while (*s && !strchr(WHITESPACE SYMBOLS, *s)) {
// 		s++;
// 	}
// 	*p2 = s;
// 	return 'w';
// }

int id_shell = 0;
 
int _gettoken(char *s, char **p1, char **p2) {
    *p1 = 0;
    *p2 = 0;
    if (s == 0) {
        return 0;
    }

    while (strchr(WHITESPACE, *s)) {
        *s++ = 0;
    }
    if (*s == 0) {
        return 0;
    }

    if (strchr(SYMBOLS, *s)) {
        int t = *s;
        *p1 = s;
        *s++ = 0;
        *p2 = s;
        return t;
    }
    // changed code
    if (*s == '\"') {
        *p1 = s + 1;
        *s++ = 0;
        while (*s != '\"' && *s) {
            s++;
        } 
        if (*s == 0) {
            printf("Error: worng \"!\n");
            return 0;
        }
        *s = 0;
        *p2 = s;
    } else {
        *p1 = s;
        while (*s && !strchr(WHITESPACE SYMBOLS, *s)) {
				s++;
        }
        *p2 = s;
    }
    return 'w';
}

int gettoken(char *s, char **p1) {
	static int c, nc;
	static char *np1, *np2;

	if (s) {
		nc = _gettoken(s, &np1, &np2);
		return 0;
	}
	c = nc;
	*p1 = np1;
	nc = _gettoken(np2, &np1, &np2);
	return c;
}

#define MAXARGS 128

int printPwd() {
	char tmp[30];
	memset(tmp, 0, sizeof tmp);
	syscall_get_cwd(0, tmp);
	printf("%s", tmp);
	return strlen(tmp);
}

int parsecmd(char **argv, int *rightpipe, int *multi_task) {
	int argc = 0;
	while (1) {
		char *t;
		int fd, r;
		int c = gettoken(0, &t);
		switch (c) {
		case 0:
			return argc;
		case 'w':
			if (argc >= MAXARGS) {
				debugf("too many arguments\n");
				exit();
			}
			argv[argc++] = t;
			break;
		case '<':
			if (gettoken(0, &t) != 'w') {
				debugf("syntax error: < not followed by word\n");
				exit();
			}
			// Open 't' for reading, dup it onto fd 0, and then close the original fd.
			/* Exercise 6.5: Your code here. (1/3) */

			fd = open(t, O_RDONLY);
			dup(fd, 0);
			close(fd);

			// user_panic("< redirection not implemented");

			break;
		case '>':
			if (gettoken(0, &t) != 'w') {
				debugf("syntax error: > not followed by word\n");
				exit();
			}
			// Open 't' for writing, dup it onto fd 1, and then close the original fd.
			/* Exercise 6.5: Your code here. (2/3) */

			fd = open(t, O_WRONLY | O_CREAT | O_TRUNC);
			dup(fd, 1);
			close(fd);
			// user_panic("> redirection not implemented");

			break;
		case '|':;
			/*
			 * First, allocate a pipe.
			 * Then fork, set '*rightpipe' to the returned child envid or zero.
			 * The child runs the right side of the pipe:
			 * - dup the read end of the pipe onto 0
			 * - close the read end of the pipe
			 * - close the write end of the pipe
			 * - and 'return parsecmd(argv, rightpipe)' again, to parse the rest of the
			 *   command line.
			 * The parent runs the left side of the pipe:
			 * - dup the write end of the pipe onto 1
			 * - close the write end of the pipe
			 * - close the read end of the pipe
			 * - and 'return argc', to execute the left of the pipeline.
			 */
			int p[2];
			/* Exercise 6.5: Your code here. (3/3) */
			pipe(p);
			*rightpipe = fork();
			if (*rightpipe == 0) {
				dup(p[0], 0);
				close(p[0]);
				close(p[1]);				
				return parsecmd(argv, rightpipe, multi_task);
			} else {
				dup(p[1], 1);
				close(p[1]);
				close(p[0]);				
				return argc;
			}
			

			// user_panic("| not implemented");

			break;
		case ';':;

			int semicolon = fork();
			if (semicolon == 0) {
				return argc;
			} else {	
				wait(semicolon);
				close_all();
				if ((r = opencons()) != 0) {
					user_panic("opencons: %d", r);
				}
				// stdout
				if ((r = dup(0, 1)) < 0) {
					user_panic("dup: %d", r);
				}
				return parsecmd(argv, rightpipe, multi_task);
			}
			break;
		
		case '&':;
			int ret = fork();
			if (ret == 0) {
				return argc;
			} else {
				return parsecmd(argv, rightpipe, multi_task);
			}
			break;
		}

	}

	return argc;
}


// 1 for cd
// 2 for pwd
// 0 for normal

void declare(int argc, char **argv) {
	int isLocal = 1;
	int readOnly = 0;
	ARGBEGIN {
		case 'x':
			isLocal = 0;
			break;
		case 'r':
			readOnly = 1;
			break;
		default:
			break;
		}
	ARGEND
	char name[50];
	char value[100];
	int i, j;
	for (i = 0; i < argc; i++) {
		int len = strlen(argv[i]);
		for (j = 0; j < len; j++) {
			if (argv[i][j] == '=') {
				break;
			}
		}
		memset(name, 0, sizeof name);
		memset(value, 0, sizeof value);
		strncpy(name, argv[i], j);
		strcpy(value, argv[i] + j + 1);
		declare_var(id_shell, name, value, isLocal, readOnly);
	}
}



void runcmd(char *s, int shellid) {
	gettoken(s, 0);

	char *argv[MAXARGS];
	int rightpipe = 0;
	int multi_task = 0;
	int argc = parsecmd(argv, &rightpipe, &multi_task);
	if (argc == 0) {
		return;
	}
	argv[argc] = 0;
	// for (int i= 0; i< argc;i++) {
	// 	printf("%s\n", argv[i]);
	// }
	if (!strcmp(argv[0], "cd")) {
		if (argv[1]) {
			int fdnum = open(argv[1], O_RDONLY);
			if (fdnum < 0) {
				printf ("Error: Wrong Format cd!\n");
				return;
			}
			close(fdnum);
			cd(shellid, argv[1]);
			cd(0, argv[1]);
			return;
		} else {
			printf ("Error: No Input cd!\n");
		}
	}

	if (!strcmp(argv[0], "pwd")) {
		pwd(shellid, NULL);
		return;
	}

	if (!strcmp(argv[0], "declare")) {
		if (argc == 1) {
			syscall_declare_all(id_shell);
		}
		declare(argc, argv);
		return;
	}

	if (!strcmp(argv[0], "unset")) {
		for (int i = 1; i < argc; i++) {
			unset_var(id_shell, argv[i]);
		}
		return;
	}


	// debugf("@@@@@@i am spawning %s \n", argv[0]);

	char buf[100];
	memset(buf, 0, sizeof buf);
	if (argv[0][0] == '/') {
		strcpy(buf, argv[0]);
	} else {
		strcat(buf, "/");
		strcat(buf, argv[0]);
	}
	
	int child = spawn(buf, argv);
	close_all();
	if (child >= 0) {
		wait(child);
	} else {
		debugf("spawn %s: %d\n", argv[0], child);
	}

	if (rightpipe) {
		wait(rightpipe);
	}

	exit();
}


void moveDirection(char tmp, int *index, char *buf) {

	switch (tmp) {
	case 'A':
		printf("\x1b[B\x1b[2K\x1b[G");
		getLastHistory(buf);
		printPwd();
			printf(" $ ");
		printf("%s", buf);
		*index = strlen(buf) - 1;
		break;
	case 'B':
		printf("\x1b[2K\x1b[G");
		getNextHistory(buf);
		printPwd();
			printf(" $ ");
		printf("%s", buf);
		*index = strlen(buf) - 1;
		break;
	case 'C':
		if (*index > strlen(buf) - 1) {
			printf("\x1b[D");
			*index -= 1;
		}	
		break;
	case 'D':
		if (*index > 0) {
			*index -= 2;
		} else {
			*index -= 1;
			printf("\x1b[C");
		}
		break;
	default:
		break;
	}
}

void readline(char *buf, u_int n) {
	
	int curHistoryLine = 0;
	int r;
	for (int i = 0; i < n; i++) {
		char c;
		if ((r = read(0, &c, 1)) != 1) {
			if (r < 0) {
				debugf("read error: %d\n", r);
			}
			exit();
		}

		if (c == '\r' || c == '\n') {
			return;
		}
		if (c == '\x1b') {
			char tmp[10];
			memset(tmp, 0, sizeof tmp);

			if ((r = read(0, tmp, 1)) != 1) {
				if (r < 0 || tmp[0] != '[') {
					debugf("read error: %d\n", r);
				}
				exit();
			}
			if ((r = read(0, tmp + 1, 1)) != 1) {
				if (r < 0) {
					debugf("read error: %d\n", r);
				}
				exit();
			}

			moveDirection(tmp[1], &i, buf);
			continue;
		}

		


		if (c == '\b' || c == 0x7f) {
			// if (i == strlen(buf)) {
			// 	delete(buf, i - 1 , 1);
			// 	printf("\b \b");
			// 	i--;
			// 	continue;
			// }
			if (i == 0) {
				// printf("\x1b[1C");
				continue;
			}
			i-=1;
			delete(buf, i , 1);
			printf("\x1b[G\x1b[K");
			int length = printPwd();
			printf(" $ ");
			printf("%s", buf);
			printf("\x1b[G");
			
			for (int col_num = 0; col_num < i + 3 + length; col_num++) {
				printf("\x1b[1C");
			}
			i--;
			continue;
		}


		if (i != strlen(buf)) {
			insert(buf, i, &c, 1);
			printf("\x1b[G\x1b[K");
			int length = printPwd();
			printf(" $ ");
			printf("%s", buf);
			printf("\x1b[G");
			for (int col_num = 0; col_num < i + 4 + length; col_num++) {
				printf("\x1b[1C");
			}
		} else {
			buf[i] = c;
		}



		if (buf[i] == '\r' || buf[i] == '\n') {
			buf[i] = 0;
			return;
		}
		
		if (buf[i] == '\r' || buf[i] == '\n') {
			buf[i] = 0;
			return;
		}
	}
	debugf("line too long\n");
	while ((r = read(0, buf, 1)) == 1 && buf[0] != '\r' && buf[0] != '\n') {
		;
	}
	buf[0] = 0;
}



char buf[1024];

void usage(void) {
	debugf("usage: sh [-dix] [command-file]\n");
	exit();
}

int main(int argc, char **argv) {
	int r;
	int interactive = iscons(0);
	int echocmds = 0;
	int shellid = syscall_getenvid();

	debugf("\n:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
	debugf("::                                                         ::\n");
	debugf("::                     MOS Shell 2077                      ::\n");
	debugf("::                                                         ::\n");
	debugf(":::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
	// debugf("checkpoint %d %s\n", argc, argv[0]);
	ARGBEGIN {
	case 'i':
		interactive = 1;
		break;
	case 'x':
		echocmds = 1;
		break;
	default:
		usage();
	}
	ARGEND

	if (argc > 1) {
		usage();
	}
	echocmds = 1;
	if (argc == 1) {
		close(0);
		if ((r = open(argv[1], O_RDONLY)) < 0) {
			user_panic("open %s: %d", argv[1], r);
		}
		user_assert(r == 0);
	}

	history_init();
	syscall_mem_map(0, argv_shell, 0, argv_shell, PTE_D | PTE_LIBRARY);
	syscall_mem_map(0, shared, 0, shared, PTE_D | PTE_LIBRARY);


	id_shell = syscall_shell_id_alloc();
	// printf("shell id is %d\n", id_shell);
	for (;;) {
		if (interactive) {
			printf("\n");
			printPwd();
			printf(" $ ");
			
		}
		memset(buf, 0, sizeof buf);
		readline(buf, sizeof buf);
		if (!strcmp(buf, "exit")) {
			syscall_destroy_shell(id_shell);
			exit();
		}

		int count = 0;
		for (int i = 0; i < strlen(buf); ++i) {
			if (buf[i] == '\"') {
				count++;
				if (count % 2 == 0) {
					continue;
				}
				int j = i;
				while (buf[j] != ' ' && j > 0) {
					j--;
				}
				for (int k = i - 1; k > j; k--){
					buf[k+1]=buf[k];
				}
				buf[j + 1] = '\"';


			}
		}


		history_save(buf, strlen(buf));

		if (buf[0] == '#') {
			continue;
		}
		if (echocmds) {
			printf("# %s\n", buf);
		}

		char name[50];
		char value[100];
		for (int i = 0; buf[i]; i++) {
			// debugf("for ing  %d\n", i);
			int len = 0;
			if (buf[i] == '$') {
				// debugf("i get name %s\n", name);
				memset(name, 0, sizeof name);
				memset(value, 0, sizeof value);
				name[0] = buf[i];
				// debugf("i get name %s\n", name);
				while (!strchr(SYMBOLS WHITESPACE, buf[i + len + 1]) && buf[i + len + 1]) {
					name[len + 1] = buf[i + len + 1];
					len++;
				}
				// debugf("i get name %s\n", name + 1);
				
				get_var(id_shell, name + 1, value);
				// debugf("i get value %s\n", value);
				replace(buf, name, len + 1, value);
			}
		}

		// if (echocmds) {
		// 	printf("# %s\n", buf);
		// }

		if ((r = fork()) < 0) {
			user_panic("fork: %d", r);
		}
		if (r == 0) {
			runcmd(buf, shellid);
			exit();
		} else {
			wait(r);
		}

		
		flushIndex();

	}
	return 0;
}
