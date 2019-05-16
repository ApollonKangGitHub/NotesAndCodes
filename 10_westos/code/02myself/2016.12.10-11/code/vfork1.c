/*子进程先执行，即使子进程在休眠，只要子进程未结束，父进程就不会执行*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int sta;
int main (void)
{
	int tag = 10;
	pid_t pid = vfork();
	if(pid == 0){
//		tag = 0;
		printf("pid = %d, tag = %d\n",getpid(),tag);
		exit(EXIT_SUCCESS);
	}
	else{
		tag = 20;
		printf("pid = %d, tag = %d\n",getpid(),tag);
	}
	return 0;
}
