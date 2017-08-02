#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>

void error_sc(const char * ptr_fun)/*error System Call */
{
	perror(ptr_fun);
	exit(EXIT_FAILURE);
}
int main(void)
{
	int fd = open("fcntl.txt",O_RDWR|O_TRUNC);
	if(fd == -1)	error_sc("open fcntl.txt");

	char * buf = "HELLO,I'AM FUNTION OF FCNTL2!\n";

	struct flock rflock = {F_WRLCK,SEEK_SET,0,30,-1};
	int ret_fcntl  = fcntl(fd, F_SETLK, &rflock);
	if(ret_fcntl == -1)
		error_sc("fcntl");
	else{
		printf("Lock of write is success!\n");
		int ret_write = write(fd,buf,strlen(buf));
		if(ret_write == -1) error_sc("write");
	}
	
	return 0;
}
