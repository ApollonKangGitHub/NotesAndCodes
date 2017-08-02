#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    struct stat s_buf;

    if (argc < 2) {
        printf("./app filename\n"); //perror
        exit(1);
    }
    if (stat(argv[1], &s_buf) < 0) {
        perror("stat");
        exit(1);
    }
    printf("%s\t%ld\n", argv[1], s_buf.st_size);

    return 0;
}
