# include<stdio.h>
# include<unistd.h>
int main(void)
{
	pid_t pid;
	int tag = 10;
	printf("%d,%d,%d\n",getppid(),getpid(),tag);
	pid = fork();
	if(pid == 0){
		sleep(1);
		tag = 5;
		printf("pid = %d,%d,%d\n",getppid(),getpid(),tag);
	}
	printf("pid = %d,%d,%d\n",getppid(),getpid(),tag);
	return 0;
}
