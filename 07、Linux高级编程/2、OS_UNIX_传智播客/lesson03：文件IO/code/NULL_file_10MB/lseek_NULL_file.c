#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<stdlib.h>

#define SIZE_FILE 1024*1024*10 //10MB = 10*1024KB = 10*1024*1024Byte
int main(void)
{
	int fd = open("file_10M.txt",O_CREAT | O_TRUNC | O_RDWR, 0777);
	if(fd == -1){
		perror("open file_10M.txt");
		exit(EXIT_FAILURE);
	}
//lseek函数扩展文件必须有一次写操作
	off_t ret = lseek(fd, SIZE_FILE-1, SEEK_END);
	printf("ret = %ld\n",ret);
	write(fd, "", 1);

	close(fd);
	return 0;
}
