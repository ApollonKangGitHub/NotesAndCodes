#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

int main(char argc,char ** argv){
	char * buf = argv[1];
	int ret = chdir(buf);

	if(ret == -1){
		perror("chdir error:");
		exit(EXIT_FAILURE);
	}

	return 0;
}
