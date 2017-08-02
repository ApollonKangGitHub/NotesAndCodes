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
	int flags = fcntl(STDOUT_FILENO, F_GETFL);
	flags |= O_NONBLOCK;
	if((fcntl(STDOUT_FILENO, F_SETFL, flags)) == -1){
		perror("fcntl SETFL flags");
		exit(EXIT_FAILURE);
	}

	char buf[SIZE] = {0};
	int ret;
tryagain:
	ret = read(STDOUT_FILENO, buf, sizeof(buf));
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

	return 0;
}
