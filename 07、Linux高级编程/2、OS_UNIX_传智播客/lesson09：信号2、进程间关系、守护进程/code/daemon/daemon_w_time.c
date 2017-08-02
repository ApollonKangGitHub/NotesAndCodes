//创建一个守护进程：每间隔10秒向/tmp/daemon.log日志中写入当前时间
//把写好的守护进程加到系统开机自启动中便类似与一个系统守护进程
//只不过这个守护进程有点耗费硬盘空间啊～～～～
#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/types.h>
#include<time.h>
#include<string.h>

#define TIME_SIZE 32

void sys_err(const char * ptr)
{
	perror(ptr);
	exit(EXIT_FAILURE);
}
void create_daemon(void)
{
	pid_t pid;
	if((pid = fork()) < 0)//创建子进程
		sys_err("fork");
	else if(pid > 0)
		exit(EXIT_SUCCESS);//结束父进程

	setsid();
	
	if(chdir("/") < 0)//改变目录到根目录下
		sys_err("chdir");
	umask(0);//设置屏蔽字
	
	close(0);//关闭012文件描述符指向的设备
	open("/dev/null", O_RDWR);
	dup2(0,1);
	dup2(0,2);
}

void write_daemonlog(int fd)
{
	char buf[TIME_SIZE] = {};	
	time_t get;
	time(&get);
	ctime_r(&get, buf);//ctime_r为可重入版本
	
	lseek(fd, 0, SEEK_END);
	int ret = write(fd, buf, strlen(buf));
	if(ret == -1)
		sys_err("write");
}
int main(void)
{
	create_daemon();//创建守护进程
	int fd = open("/tmp/daemon.log", O_CREAT|O_RDWR|O_TRUNC);//O_TRUNC表示该守护进程在每次开机启动时都要清空之前的log日志
	if(fd == -1)
		sys_err("open");
	
	while(1){
		write_daemonlog(fd);
		sleep(10);
	}
}
