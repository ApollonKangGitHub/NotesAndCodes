#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>


void sys_err(const char * ptr){
        perror(ptr);
        exit(EXIT_FAILURE);
}
int main(int argc, char *argv[])
{
    int fd;
    char buf[1024] = "hello world\n";
    if (argc < 2) {
        printf("./fifo_w fifoname\n");
        exit(EXIT_FAILURE);
    }

    fd = open(argv[1], O_WRONLY);
    if (fd < 0) 
        sys_err("open", 1);

    write(fd, buf, strlen(buf));
    close(fd);

    return 0;
}

