/*当pthread_cancel结束一个线程时
 *被结束的线程在下次调用系统调用的时候才会真正结束
 *测试时：
 *不注释sleep注释pthread_testcancel()
 *注释sleep注释pthread_testcancel()
 *注释sleep不注释pthread_testcancel()
 *分别测试ps -eLf
 * */
#include<stdio.h>
#include<pthread.h>

void * deal_pthread(void * arg)
{
	int * p = (int *)arg;
	printf("thread ID in child thread= %x\n", pthread_self());
	printf("process ID in child thread = %d\n", getpid());
	printf("*arg = %d\n", *p);
	int i = 0;
	while(1){
		i++;
		//sleep(1);
		//pthread_testcancel();
	}
}
int main(void)
{
	pthread_t tid;
	int n = 10;
	pthread_create(&tid, NULL, 	deal_pthread, (void *)&n);
	printf("thread ID in main create = %x\n", tid);
	printf("thread ID in main thread = %x\n", pthread_self());
	printf("process ID in main process = %d\n", getpid());
	
	sleep(1);//先睡眠一秒，防止getpid()后调用而pthread_cancel先发送影响子线程中sleep效果测试
	pthread_cancel(tid);
	while(1)
		sleep(1);
	return 0;
}
