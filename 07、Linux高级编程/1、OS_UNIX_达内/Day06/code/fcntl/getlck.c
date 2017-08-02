#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

int main(void)
{
	int fd = open("fcntl.txt",O_RDWR);
	if(	fd == -1){
		perror("open");
		exit(EXIT_FAILURE);
	}
	struct flock lock={F_RDLCK,SEEK_SET,0,20,-1};
	/*
	struct flock lock;
	
	lock.l_type = F_RDLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = 0;
	lock.l_len = 20;
	lock.l_pid= -1;
	*/
	printf("type = %d\n",lock.l_type);
	printf("F_WRLCK:%d\nF_RDLCK:%d\nF_UNLCK:%d\n",F_WRLCK,F_RDLCK,F_UNLCK);
	fcntl(fd,F_GETLK,&lock);
	printf("F_RDLCK:type=%d,pid=%d\n",lock.l_type,lock.l_pid);

	lock.l_type = F_WRLCK;
	fcntl(fd,F_GETLK,&lock);
	printf("F_WRLCK:type=%d,pid=%d\n",lock.l_type,lock.l_pid);


	return 0;
}

