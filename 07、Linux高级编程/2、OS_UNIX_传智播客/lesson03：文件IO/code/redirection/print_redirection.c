#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<errno.h>

void sys_err(const char * ptr)
{
	perror(ptr);
	exit(EXIT_FAILURE);
}
int main(void)
{
	int fd = open("test.txt", O_CREAT|O_RDWR, 0777);
	if(fd == -1)
		sys_err("open test.txt");
	int fdnew = dup2(fd, STDOUT_FILENO);
	if(fdnew == -1)
		sys_err("dup2(fd,STDOUT_FILENO)");
	printf("helloworld\n");	/*printf输出重定向到test.txt*/

	close(fd);/*fd和fdnew指向同一个文件，所以关闭一个即可*/
	return 0;
}
