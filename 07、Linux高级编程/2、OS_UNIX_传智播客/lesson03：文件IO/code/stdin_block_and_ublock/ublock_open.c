/*
*由于open时设置为O_NONBLOCK,所以read读取/dev/tty时并不阻塞，
*因而read之后的代码能够执行，而block.c中read处于阻塞状态，read后的代码均不能执行
*当然我们也可以将goto改成for循环，设定超时退出，比如循环5次就结束循环不再等待
*
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
#define MSG_TRY "try again\n"

int main(void)
{
	int fd = open("/dev/tty", O_RDWR | O_NONBLOCK);//打开终端的时候就是以非阻塞的方式打开，tty为当前终端
	if(fd == -1){
		perror("open /dev/tty");//打开失败
		exit(EXIT_FAILURE);
	}

	char buf[SIZE] = {0};
	int ret;
tryagain:
	ret = read(fd, buf, sizeof(buf));
	if(ret < 0){
		if(errno == EAGAIN){//该errno是当读取文件没有读到内容但是并不是失败时，设置的errno
			sleep(2);
			write(STDOUT_FILENO, MSG_TRY, sizeof(MSG_TRY));
			goto tryagain;
		}
		perror("read stdin");//读取失败
		exit(EXIT_FAILURE);
	}
	write(STDOUT_FILENO, buf, ret);
	close(fd);

	return 0;
}
