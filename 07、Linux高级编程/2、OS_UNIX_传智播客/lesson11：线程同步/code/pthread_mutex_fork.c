#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<fcntl.h>
#include<string.h>
#include<sys/mman.h>
#include<sys/stat.h>
#include<sys/types.h>

struct mt{
	int num;
	pthread_mutex_t mutex;
	pthread_mutexattr_t mutexattr;
};
int main(void)
{
	int fd, i;
	struct mt * mm;
	pid_t pid;
	fd = open("mt_test", O_CREAT | O_RDWR, 0777);
	/*不需要write，文件里的初始值为0*/
	ftruncate(fd, sizeof(*mm));
	mm = mmap(NULL, sizeof(*mm), PROT_READ | PROT_WRITE, MAP_SHARED, fd ,0);
	/*文件映射完毕回收文件描述符即可*/
	close(fd);

	memset(mm, 0, sizeof(*mm));
	/*初始化互斥对象属性*/
	pthread_mutexattr_init(&mm->mutexattr);
	/*设置会斥对象为PTHREAD_PROCESS_SHARED共享，即可在多个进程的线程访问，PTHREAD_PROCESS_PRIVATE为同一进程的线程共享*/
	pthread_mutexattr_setpshared(&mm->mutexattr, PTHREAD_PROCESS_SHARED);

	pthread_mutex_init(&mm->mutex, &mm->mutexattr);
	pid = fork();
	printf("process id=%d\tnum=%d\n", getpid(), mm->num);
	if(pid == 0){
		/*子进程10次相当与加10*/
		for(i = 0; i < 10; i++){
			pthread_mutex_lock(&mm->mutex);
			(mm->num)++;
			printf("in %d process,num=num+1=:%d\n", getpid(), mm->num);
			pthread_mutex_unlock(&mm->mutex);
			sleep(1);
		}
	}
	else if(pid > 0){
		/*父进程执行x+2,加十次相当与加20*/
		for(i = 0; i < 10; i++){
			pthread_mutex_lock(&mm->mutex);
			mm->num += 2;;
			printf("in %dprocess,num=num+2=:%d\n", getpid(), mm->num);
			pthread_mutex_unlock(&mm->mutex);
			sleep(1);
		}
		wait(NULL);
	}

	pthread_mutex_destroy(&mm->mutex);
	pthread_mutexattr_destroy(&mm->mutexattr);
	/*父子进程均需要释放*/
	munmap(mm, sizeof(*mm));
	unlink("mt_test");

	return 0;
}
