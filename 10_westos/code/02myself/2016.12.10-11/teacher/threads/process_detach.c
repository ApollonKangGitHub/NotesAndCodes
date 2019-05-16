#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
int pthread_detach(pthread_t thread);
int pthread_attr_setdetachstate (pthread_attr_t *__attr, int __detachstate)

如果一个线程调用了这个函数，那么当这个线程终止的时候，和它相关的系统资源将被自动
释放，系统不用也不能用pthread_join()等待其退出。有的时候分离线程更好些，因为它潜在地减
少了一个线程回收的同步点，并且pthread_join()这个API确实也是相当地难用。

一般情况下进程终止的时候，和它相关的系统资源也并不是主动释放的，而是进入一种通常称
为“僵尸”(zombie)的状态。它所占有的资源一直被系统保留，直到它的父进程（如果它直接的父进程先
于它去世，那么它将被init进程所收养，这个时候init就是它的父进程）显式地调用wait
系列函数为其“收尸”。为了让父进程尽快知道它去世的消息，它会在它死去的时候通过向父进程发送
SIGCHLD信号的方式向其“报丧”，父进程通常安装有类似下面的SIGCHLD信号处理函数reap_zombie.
*/
void reap_zombie(int signo)
{
        int errno_old = errno;

        while (waitpid(-1, NULL, WNOHANG) > 0)
                ;

        errno = errno_old;
}

/*
如果只是为了为子进程“收尸”，上面函数reap_zombie足矣！另一方面，如果父进程对子进程的终止状态没有任何兴趣，那么
以上代码无疑又会引入无谓的复杂度，并且还有潜在的同步瓶颈。如果进程能够像处于分离状态的线程
那样死得干干净净，那就完美了！
*/

int main(int argc, char *argv[])
{
        pid_t pid;

        if (argc == 2) {
                if (strcmp(argv[1], "signal") == 0)
                        signal(SIGCHLD, SIG_IGN);
                else if (strcmp(argv[1], "handle") == 0)
                        signal(SIGCHLD, reap_zombie);
                else {
                        struct sigaction act;

                        memset(&act, 0, sizeof(act));
                        act.sa_flags |= SA_NOCLDWAIT;
                        sigaction(SIGCHLD, &act, NULL);
                }
        }
        pid = fork();
        if (pid == 0) {
                fprintf(stderr, "I am child\n");
                sleep(1);
                fprintf(stderr, "Child exits\n");

                return EXIT_SUCCESS;
        }
        sleep(2);
        system("ps -el | grep process_detach");
        wait(NULL);
        perror("wait");

        return EXIT_SUCCESS;
}
