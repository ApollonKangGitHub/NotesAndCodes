#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

int main(void){	
	int i = 10;
	while(i--){
		pid_t pid = fork();
		if(pid == 0){
			sleep(1);
			printf("id=%duser is quit!\n",getpid());
			exit(EXIT_SUCCESS);
		}
	}

	sleep(1);
	return 0;
}
