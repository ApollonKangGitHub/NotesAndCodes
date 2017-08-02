#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
int main(void)
{
    pid_t pid;
    int n  = 3;
    while (n--) {
        pid = fork();
        if (pid == 0)
            break;
    }

    if (pid == 0) {
        {
            printf("I am child %d\n", getpid());
            sleep(3);
        }
    }
    else if (pid > 0) {
        printf("n = %d\n", n);
        n++;
        pid_t pid_c;
        while (1) {
            //pid_c = wait(NULL);
            printf("I am parent \n");
            pid_c = waitpid(0, NULL, WNOHANG);
            if (pid_c > 0)  {
                n++;
            }
            if (pid_c == -1)
                continue;
            else
                printf("wait for child %d\n", pid_c);
            if (n == 3)
                break;
            sleep(1);
        }
    }
    return 0;
}
