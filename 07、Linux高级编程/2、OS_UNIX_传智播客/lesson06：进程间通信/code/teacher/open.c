#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


int main(int argc, char *argv[])
{
    int fd;
    char buf[1024] = "hello";
    if (argc < 2) {
        printf("./app filename\n");
        exit(1);
    }

    umask(0);
    fd = open(argv[1], O_CREAT | O_RDWR | O_EXCL, 0777);
    //fd = open(argv[1], O_WRONLY | O_APPEND);
    //write(fd, buf, strlen(buf));

    printf("fd = %d\n", fd);

    close(fd);

    return 0;
}
