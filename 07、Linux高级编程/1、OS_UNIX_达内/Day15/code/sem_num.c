#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<stdlib.h>
#include<time.h>
/*设置服务器的访问的最大连接数*/
sem_t sem;
void * task(void *p){
	int i = (int)p;
	printf("第%d个线程开始运行\n",i);
	sem_wait(&sem);//计数-1，如果计数已经为0，阻塞等待
	printf("第%d线程连接成功\n",i);
	srand(time(NULL));
	int res = rand()%10;
	sleep(res);//由于睡眠时间不同,所以释放资源次序与连接顺序不一定相同
	printf("第%d个线程连接结束，释放资源\n",i);
	sem_post(&sem);
}
int main(void)
{
	sem_init(&sem, 0, 10);
	int i;
	for(i=1; i<21; i++){
		pthread_t tid;
		pthread_create(&tid, NULL, task,(void *)i);
	}
	while(1);
	return 0;
}
