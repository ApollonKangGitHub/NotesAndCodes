#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<sys/types.h>

int main(int argc, char * argv[])
{
	if(argc < 3){
		printf("./mykill signal pid");
		exit(EXIT_FAILURE);
	}

	if( kill( (pid_t)atoi(argv[2]), atoi(argv[1]) ) < 0){
		perror("kill");
		exit(EXIT_FAILURE);
	}
	return 0;
}
