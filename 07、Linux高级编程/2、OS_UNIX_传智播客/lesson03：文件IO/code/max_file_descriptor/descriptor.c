/**
**0~1024总共1025个描述符号
**0~2被占用
**所以最多能创建1022个文件
**即创建失败时会打印的是1022最后一个文件
*/

#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
int main(void)
{
	char bufname[10] = {0};	
	int i = 0, fd;
	while(1){
		sprintf(bufname, "file%d", ++i);
		fd = open(bufname, O_CREAT, 0777);
		printf("fd = %d\n",i);
		if(fd == -1){
			perror("open create");
			exit(EXIT_FAILURE);
		}
	}
	return 0;
}
