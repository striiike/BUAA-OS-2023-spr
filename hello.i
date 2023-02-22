# 0 "hello.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 0 "<command-line>" 2
# 1 "hello.c"
# 1 "output.h" 1



void print_str(const char *buf);
void printcharc(char ch);
void print_num(unsigned long u);
void halt(void);
# 2 "hello.c" 2
# 1 "/usr/lib/gcc/x86_64-linux-gnu/11/include/stddef.h" 1 3 4
# 143 "/usr/lib/gcc/x86_64-linux-gnu/11/include/stddef.h" 3 4

# 143 "/usr/lib/gcc/x86_64-linux-gnu/11/include/stddef.h" 3 4
typedef long int ptrdiff_t;
# 209 "/usr/lib/gcc/x86_64-linux-gnu/11/include/stddef.h" 3 4
typedef long unsigned int size_t;
# 321 "/usr/lib/gcc/x86_64-linux-gnu/11/include/stddef.h" 3 4
typedef int wchar_t;
# 415 "/usr/lib/gcc/x86_64-linux-gnu/11/include/stddef.h" 3 4
typedef struct {
  long long __max_align_ll __attribute__((__aligned__(__alignof__(long long))));
  long double __max_align_ld __attribute__((__aligned__(__alignof__(long double))));
# 426 "/usr/lib/gcc/x86_64-linux-gnu/11/include/stddef.h" 3 4
} max_align_t;
# 3 "hello.c" 2


# 4 "hello.c"
void hello(int a, int b, int c, int d, int e, int f) {
 print_str("hello world\n");
 print_num(a);
 print_str("\n");
 print_num(b);
 print_str("\n");
 print_num(c);
 print_str("\n");
 print_num(d);
 print_str("\n");
 print_num(e);
 print_str("\n");
 print_num(f);
 print_str("\n");
 halt();
}
