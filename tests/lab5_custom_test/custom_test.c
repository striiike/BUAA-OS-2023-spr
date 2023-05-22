#include <lib.h>
#include <drivers/dev_rtc.h>

int *sec = (int *)(UTEMP + DEV_RTC_SEC);
int *us = (int *)(UTEMP + DEV_RTC_USEC);

int main() {

    int fd = open("/newfile",O_CREAT | O_RDWR);
    debugf("I\n");
    write(fd, "hello", 10);
	fd = open("/newfile", O_RDONLY);
    debugf("2\n");
        
    char buf[10];
    read(fd,buf,10);
    debugf("%s\n",buf) ;
        


    fd = open("/newfolder/", O_MKDIR | O_RDWR);
	debugf("3\n");
	fd = open("/newfolder/newnew", O_CREAT | O_RDWR);

	debugf("4\n");
	


    write(fd, "hellonewnew", 10);
	fd = open("/newfolder/newnew", O_RDONLY);
    
        
    read(fd, buf, 10);
    debugf("%s\n",buf) ;

        
    return 0;
}
