#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

#define MAX 1000000
#define BUF_SIZE 1000
int main (void)
{
	int fd = open("test3.txt",O_RDWR|O_TRUNC|O_CREAT,0666);
	if(fd == -1){
		perror("open test3.txt");
		exit(EXIT_FAILURE);
	}

	int i;
	int buffer[BUF_SIZE] = {0};
	for(i = 0; i < MAX; i++){
		buffer[i%BUF_SIZE] = i;
		if(i%BUF_SIZE == BUF_SIZE-1)
			write(fd, buffer, sizeof(buffer));
	}

	close(fd);
	return 0;
}
