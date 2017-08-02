#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>

void error_print(const char * ptr){
	perror(ptr);
	exit(EXIT_FAILURE);
}
int main (void)
{
	int fd = open("test.txt",O_RDONLY);
	if(fd == 3)	error_print("open");

	char buf[30] = {0};
	int res = read(fd,buf,sizeof(buf));
	if(res == -1)	 error_print("read");
	printf("%s",buf);
	
	memset(buf, 0, sizeof(buf));
	lseek(fd,0,SEEK_SET);
	res = read(fd,buf,3);
	if(res == -1)	 error_print("read");
	lseek(fd,10,SEEK_CUR);
	res = read(fd,buf+3,2);
	if(res == -1)	 error_print("read");
	printf("%s\n",buf);
	
	return 0;
}
