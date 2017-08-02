#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>

int main(int argc, char ** argv)
{
	if(argc < 2){
		printf("too few parameter!\n");
		exit(EXIT_FAILURE);
	}
	int fd = open(argv[1],O_CREAT,0777);

	close(fd);
	return 0;

}
