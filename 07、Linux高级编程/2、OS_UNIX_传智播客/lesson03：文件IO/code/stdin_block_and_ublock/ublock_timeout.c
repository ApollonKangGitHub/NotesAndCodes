/*
*设置超时退出
*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>

#define SIZE 1024
#define MSG_TRY "Try again:\n"
#define MSG_TIMEOUT "Timeout!\n"
#define MAX 5
int main(void)
{
	int fd = open("/dev/tty", O_RDWR | O_NONBLOCK);//打开终端的时候就是以非阻塞的方式打开，tty为当前终端
	if(fd == -1){
		perror("open /dev/tty");//打开失败
		exit(EXIT_FAILURE);
	}

	char buf[SIZE] = {0};
	int ret, i;

	for(i=0; i<MAX; i++){
		ret = read(fd, buf, sizeof(buf));
		if(ret >= 0)
			break;
		if(ret < 0){
			if(errno == EAGAIN){//该errno是当读取文件没有读到内容但是并不是失败时，设置的errno
				sleep(2);
				write(STDOUT_FILENO, MSG_TRY, sizeof(MSG_TRY));
			}
			else{
				perror("read stdin");//读取失败
				exit(EXIT_FAILURE);
			}
		}
	}
	if(i == MAX)
		write(STDOUT_FILENO, MSG_TIMEOUT, sizeof(MSG_TIMEOUT));
	else
		write(STDOUT_FILENO, buf, ret);
	close(fd);

	return 0;
}
