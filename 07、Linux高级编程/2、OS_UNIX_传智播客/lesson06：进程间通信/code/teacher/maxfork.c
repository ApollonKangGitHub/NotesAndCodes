#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

int main(void)
{
    pid_t pid;
    //调用1次返回2次，在父进程返回子进程的PID，在子进程返回0

    int n = 0, m = 30;
    while (1) {
        pid = fork();  //父子都都出来
        if (pid == 0) {
            break;
        }
        else if (pid > 0)
            printf("%d  ", n++);
        else {
            exit(1);
        }
    }

    while (m--)
        sleep(1);


    return 0;
}
