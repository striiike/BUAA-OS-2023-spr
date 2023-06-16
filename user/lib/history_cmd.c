#include <lib.h>
#include <cursor.h>
#include <fs.h>

static int historyLine = 0;
static int curIndex = 0;

void flushIndex() {
    curIndex = historyLine + 1;
}

int getHistoryLine() {
    return historyLine;
}

void history_init() {
    int r;
    if ((r = open("/.history", O_CREAT)) < 0) {
        user_panic(".history can't be initialized\n");
    }
    close(r);
}

void history_save(char *buf, int size) {
    int fd = open("/.history", O_WRONLY | O_APPEND);

    historyLine++;
    char tmp[2];
    tmp[0] = historyLine / 10 + '0';
    tmp[1] = historyLine % 10 + '0'; 
    write(fd, tmp, 2);

    tmp[0] = size / 10 + '0';
    tmp[1] = size % 10 + '0'; 
    write(fd, tmp, 2);

    write(fd, buf, size);
    write(fd, "\n", 1);
    close(fd);
    
}

void getLastHistory(char *back) {
    if (curIndex == 0) return;

    curIndex -= (curIndex != 1);


    char buf[1000];
    memset(buf, 0, sizeof buf);
    int fd = open("/.history", O_RDONLY);
    int n = readn(fd, buf, sizeof buf);
    if (n < 0) user_panic("Error! in read\n");
    close(fd);
    
    int line = 1;
    int index = 0;
    for (;;) {
        int curLine = 0;
        curLine += (buf[index++] - '0') * 10;
        curLine += buf[index++] - '0';

        index += 2;
        if (curLine == curIndex) {
            char c;
            while ((c = buf[index++]) != '\n')
                *back++ = c;
            *back = 0;
            return;
        }

        char c;
        while ((c = buf[index++]) != '\n')
            ;
        line++;
    }

}

void getNextHistory(char *back) {
    if (curIndex == 0 || curIndex > historyLine) return;
    curIndex += (curIndex < historyLine);

    char buf[1000];
    memset(buf, 0, sizeof buf);
    int fd = open("/.history", O_RDONLY);
    int n = readn(fd, buf, sizeof buf);
    if (n < 0) user_panic("Error! in read\n");
    close(fd);

    int line = 1;
    int index = 0;
    for (;;) {

        int curLine = 0;
        curLine += (buf[index++] - '0') * 10;
        curLine += buf[index++] - '0';

        index += 2;
        
        if (curLine == curIndex) {
            char c;
            while ((c = buf[index++]) != '\n')
                *back++ = c;
            *back = 0;
            return;
        }

        char c;
        while ((c = buf[index++]) != '\n')
            ;
        line++;
    }


}



