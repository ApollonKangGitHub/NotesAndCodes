#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>

void create_daemon(void)
{
	pid_t pid;
	if((pid = fork()) < 0){
		perror("daemon fork\n");
		exit(EXIT_FAILURE);
	}
	else if(pid > 0)
		exit(EXIT_SUCCESS);

	setsid();
	
	if(chdir("/") < 0){
		perror("chdir");	
		exit(EXIT_FAILURE);
	}

	umask(0);
	
	close(0);
	open("/dev/null", O_RDWR);
	dup2(0,1);
	dup2(0,2);

}
int main(void)
{
	create_daemon();
	while(1);
}
