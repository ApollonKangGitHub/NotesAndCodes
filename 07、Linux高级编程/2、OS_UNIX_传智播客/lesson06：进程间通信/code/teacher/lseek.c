#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    int fd = open("abc", O_RDWR);
    if (fd < 0) {
        perror("open abc");    
        exit(-1);
    }

    //拓展一个文件，一定要有一次写操作
    lseek(fd, 0x1000, SEEK_SET);
    write(fd, "a", 1);

    close(fd);


    fd = open("hello", O_RDWR);
    if (fd < 0) {
        perror("open hello");    
        exit(-1);
    }
    printf("hello size = %d\n", lseek(fd, 0, SEEK_END));
    close(fd);


    return 0;
}
