/**
 *即使不关闭也不会影响输入输出
 *但是为了安全性还是要关闭多余的端口
 *09时18分41秒--2017/1/27
 */
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main(void)
{	
	int fd[2] = {0};
	pipe(fd);

	pid_t pid = fork();
	if(pid == 0){
//		close(fd[1]);/*关闭子进程的写端*/
		int i;
		for(i=0; i<100; i++){
			int x;
			read(fd[0],&x,4);
			printf("%d ",x);/*不加\n会写入缓冲区*/
			fflush(0);/*将缓冲区中的数据即刻显示*/
		}
		close(fd[0]);
	}
//	close(fd[0]);/*关闭父进程的读端*/
	int i;
	for(i=100;i<200;i++){
		write(fd[1],&i,4);
		usleep(100000);
	}
	close(fd[1]);
	return 0;
}
