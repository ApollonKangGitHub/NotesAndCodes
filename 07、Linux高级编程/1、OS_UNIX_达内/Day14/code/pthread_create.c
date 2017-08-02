#include<stdio.h>
#include<pthread.h>
#include<errno.h>

#define MAX 1000
void * point(void * p)
{
	int i;
	for(i = 0; i < MAX; i++){
		printf("point:i = %d\n",i);
		usleep(1);
	}
}
int main(void)
{
	pthread_t tid;
	int res = pthread_create(&tid, NULL, point, NULL);
	if(res)//成功返回0,错误返回错误编码
		printf("create error:%s\n",strerror(res));
		/*线程错误处理，使用将错误编码转换成错误信息的方法实现*/
	int i;
	for(i = 0; i < MAX; i++){
		printf("main:i = %d\n",i);
		usleep(1);
	}
	usleep(10000);//确保主线程先结束时，子线程可以执行完毕再退出,如果睡眠时间小点或者MAX大点子线程就不一定能够执行完了
	return 0;
}
