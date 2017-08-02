#include<stdio.h>
#include<pthread.h>

void *point(void *p){//p就是pthread_create()函数的第四个参数
	int *pi = p;
	printf("*pi = %d\n",*pi);
	*pi = 200;
}
int main(void)
{
	pthread_t tid1,tid2;
	int x = 100;
	pthread_create(&tid1, NULL, point, &x);
	tid2 = pthread_self();//取当前线程id
	printf("tid1 = %u,main = %u\n",tid1,tid2);
	sleep(1);
	printf("x = %d\n",x);

	return 0;
}
