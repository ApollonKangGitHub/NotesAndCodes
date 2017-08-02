#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
    int mode;
    if (argc < 3) {
        printf("./mychmod mode filename\n");
        exit(1);
    }

    //"0644" -> 八进制
    mode = atoi(argv[1]);
    chmod(argv[2], mode);

    return 0;
}
