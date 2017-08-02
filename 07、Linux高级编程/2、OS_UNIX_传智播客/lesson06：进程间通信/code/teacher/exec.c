#include <stdio.h>
#include <unistd.h>

int main(void)
{
    char *argvv[] = {"ls", "-l", NULL};
    printf("hello\n");
    //   /bin/ls
    //execl("/bin/ls", "ls", "-l", NULL);
    //execlp("ls",  "ls", "-l", NULL);
    //execv("/bin/ls", argvv);
    //execvp("ls", argvv);
    execlp("app", "hehe", "11", "aa", NULL);
    //execl("/home/xingwenpeng/teach/code/test", "./test", "11", "aaa", NULL);

    printf("world\n");

    return 0;
} 
