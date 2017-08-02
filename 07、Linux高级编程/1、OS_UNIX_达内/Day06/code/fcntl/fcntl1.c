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

	char * buf = "hello,i'am function of fcntl1.c!\n";

	struct flock wflock = {F_WRLCK,SEEK_SET,0,30,-1};
	int ret_fcntl  = fcntl(fd, F_SETLK, &wflock);
	if(ret_fcntl == -1)
		error_sc("fcntl");
	else{
		printf("Lock of write is success!\n");
		int ret_write = write(fd,buf,strlen(buf));
		if(ret_write == -1) error_sc("write");
	}
	sleep(30);
	printf("fcntl flock is over!\n");
	sleep(20);
	printf("process of fcntl1 is over!\n");
	
	return 0;
}
