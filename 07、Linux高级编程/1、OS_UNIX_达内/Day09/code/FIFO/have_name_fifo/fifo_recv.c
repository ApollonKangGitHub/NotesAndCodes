#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

#define MAX 100
int main(void)
{
	int fd = open("a.pipe",O_RDONLY);/*不能用O_CREA,也不要用O_RDWR，因为O_RDWR就直接打开了管道，不能在无接收进程时阻塞*/
	if(fd == -1){
		perror("open a.pipe");
		exit(EXIT_FAILURE);
	}

	int i, num;
	for(i = 0; i < MAX; i++){
		read(fd,&num,4);
		printf("num = %d\n",num);
	}
	close(fd);
}
