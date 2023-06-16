#include <lib.h>
#include <cursor.h>


char buf[1000];
void main(int argc, char **argv) {
    int fd = open("/.history", O_RDONLY);
    
    int n = readn(fd, buf, sizeof buf);
    if (n < 0) user_panic("Error! in read\n");
    int index = 0;
    for (; buf[index] != '\0';) {
        index += 4;
        char c;
        while ((c = buf[index++]) != '\n')
            printf("%c", c);
        printf("\n");
    }
}