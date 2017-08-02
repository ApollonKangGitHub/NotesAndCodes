#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>

#define SIZE 128

int main(int argc, char ** argv){
	if(argc <= 2){
		printf("too few parameter!\n");
		exit(EXIT_FAILURE);
	}
	int fd_old, fd_new, len;
	fd_old = open(argv[1], O_RDONLY);
	fd_new = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, 0664);
	char buf[SIZE] = {};
	while((len = read(fd_old, buf, SIZE)) > 0){
		write(fd_new, buf, len);
		memset(buf, 0, strlen(buf));
	}
	close(fd_old);
	close(fd_new);
	return 0;
}
