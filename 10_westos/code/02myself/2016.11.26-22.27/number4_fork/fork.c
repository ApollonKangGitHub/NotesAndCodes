# include<stdio.h>
# include<unistd.h>
int main(void)
{
	printf("pid:%d\n",getpid());
	pid_t pid;
	pid = fork();
	if(pid == 0){
		printf("sleeping\n");
		printf("main sleep5...\n");
		sleep(2);
	}
	sleep(5);
	printf("sleep over\n");
	if(pid == 0){
		printf("child pid = %d\n",getpid());
	}
	printf("pid = %d\n",getpid());
	if(pid == 0){
		printf("child pid = %d\n",getpid());
	}
	printf("pid = %d\n",getpid());
	sleep(5);
	return 0;
}
