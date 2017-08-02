/* wrapper.c */
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

#define BUF_SIZE 256 
int main(int argc, char *argv[])
{
	int fd;
	if (argc != 2) {
		fputs("usage: wrapper file\n", stderr);
		exit(1);
	}
	fd = open(argv[1], O_RDONLY);
	if(fd<0) {
		perror("open");
		exit(1);
	}
	
	char buf[BUF_SIZE] = {0};
	int retr = read(fd, buf, sizeof(buf));
	int retw = write(STDOUT_FILENO, buf, retr);//输出小写字母
	if(retr==-1 | retw==-1){
		perror("read or write");
		exit(EXIT_FAILURE);
	}
	
	lseek(fd, 0, SEEK_SET);
	dup2(fd, STDIN_FILENO);//标准输入关闭，输入重定向到fd文件中
	close(fd);//fd0指向打开的文件，所以fd3就描述符就可以回收了。
	execl("./upper", "upper", NULL);//调用upper输出大写字母
	perror("exec ./upper");
	exit(1);
}
