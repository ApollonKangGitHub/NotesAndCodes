#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

void sys_err(char *str, int exitno)
{
    perror(str);
    exit(exitno);
}

int main(int argc, char *argv[])
{
    int fd;
    char buf[1024] = "hello xwp\n";
    if (argc < 2) {
        printf("./a.out fifoname\n");
        exit(1);
    }

    //fd = open(argv[1], O_RDONLY);
    fd = open(argv[1], O_WRONLY);
    if (fd < 0) 
        sys_err("open", 1);

    write(fd, buf, strlen(buf));
    close(fd);

    return 0;
}

