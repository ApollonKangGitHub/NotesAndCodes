# include<stdio.h>
# include<unistd.h>
int pag = 10;
int main(void)
{
	printf("begin!\n");
	pid_t pid;
	int tag = 30;
	pid = fork();
	printf("pid = %d,tag=%d,pag=%d\n",getpid(),tag,pag);
	sleep(5);
	if(pid == 0){
		tag = 20;
		pag = 20;
		printf("pid = %d,tag=%d,pag=%d\n",getpid(),tag,pag);
		pid_t pid_2 = fork();
		printf("new begin!\n");
		if(pid_2 == 0){
			tag = 10;
			pag = 30;
			printf("pid = %d,tag=%d,pag=%d\n",getpid(),tag,pag);
		}
		printf("pid = %d,tag=%d,pag=%d\n",getpid(),tag,pag);
	}
	printf("pid = %d,tag=%d,pag=%d\n",getpid(),tag,pag);
	printf("over!\n");
	return 0;
}
