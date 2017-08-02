#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>

#define BUF_PATHNAME 256
int main (char argc,char * argv[])
{	
	if(argc <= 1){
		printf("parameter is too little!");
		exit(EXIT_FAILURE);
	}
	char * mkdir_buf = argv[1];
	int ret_mkdir = mkdir(mkdir_buf,0777);
	
	if(ret_mkdir == -1){
		perror("mkdir");
		exit(EXIT_FAILURE);
	}

	return 0;
}
