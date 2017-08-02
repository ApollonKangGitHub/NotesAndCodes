#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

int main(void)
{
    pid_t pid, pid_c;

    int n = 10;
    pid = fork();  //父子都都出来

    if (pid > 0) {
        /*in parent*/
        while (1) {
            printf("I am parent %d\n", getpid());
            pid_c = wait(NULL);         //wait是一个阻塞函数,等待回收子进程资源，如果没有子进程，wait返回-1
            printf("wait for child %d\n", pid_c);
            sleep(1);
        }
    }
    else if (pid == 0) {
        /* in child */
        printf("I am child %d\n", getpid());
        sleep(10);
    }
    else {
        perror("fork");
        exit(1);
    }

    return 0;
}
