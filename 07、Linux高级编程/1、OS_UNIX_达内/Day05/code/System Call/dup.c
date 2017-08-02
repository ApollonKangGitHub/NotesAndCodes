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
	int fd3 = open("dup.txt",O_RDONLY);
	if(fd3 == -1)	error_print("open dup.txt");
	int fd4 = dup(fd3);

	int fd5 = open("dup2.txt",O_RDONLY);
	if(fd5 == -1)	error_print("open dup2.txt");
	int fd6 = dup2(fd3,fd5);

	printf("%d,%d,%d,%d\n",fd3,fd4,fd5,fd6);
	
	char buf[30] = {0};
	read(fd3,buf,sizeof(buf));
	printf("fd3:%s\n",buf);
	memset(buf,0,strlen(buf)); //	lseek(fd4,0,SEEK_SET);
	read(fd4,buf,sizeof(buf));
	printf("fd4:%s\n",buf);
	memset(buf,0,strlen(buf));//	lseek(fd5,0,SEEK_SET);
	read(fd5,buf,sizeof(buf));
	printf("fd5:%s\n",buf);
	memset(buf,0,strlen(buf));//	lseek(fd6,0,SEEK_SET);
	read(fd6,buf,sizeof(buf));
	printf("fd6:%s\n",buf);

	close(fd3);//close(fd4);close(fd5);clsoe(fd6);
	return 0;
}
