#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(void)
{
#if 0
	pid_t pid = fork();
	if(pid == 0){
		sleep(3);
	}
	else if(pid > 0)
#endif	
		wait(NULL);
	printf("over\n");
	return 0;
	
}
