#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

int main(void)
{
    pid_t pid;
    //调用1次返回2次，在父进程返回子进程的PID，在子进程返回0

    int n = 10;
    pid = fork();  //父子都都出来

    if (pid > 0) {
        /*in parent*/
        while (1) {
            printf("I am parent %d\n", n++);
            printf("my pid = %d\n", getpid());
            printf("my parent pid = %d\n", getppid());
            sleep(1);
        }
    }
    else if (pid == 0) {
        /* in child */
        printf("I am child %d\n", n++);
        printf("my pid = %d\n", getpid());
        printf("my parent pid = %d\n", getppid());
        sleep(10);
    }
    else {
        perror("fork");
        exit(1);
    }

    return 0;
}
