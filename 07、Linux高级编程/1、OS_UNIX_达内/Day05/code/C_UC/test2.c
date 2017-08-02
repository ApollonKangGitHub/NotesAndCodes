#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

#define MAX 1000000

int main (void)
{
	int fd = open("test2.txt",O_RDWR|O_TRUNC|O_CREAT,0666);
	if(fd == -1){
		perror("open test2.txt");
		exit(EXIT_FAILURE);
	}

	int i;
	for(i = 0; i < MAX; i++){
		write(fd, &i, sizeof(int));
	}

	close(fd);
	return 0;
}
