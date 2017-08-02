/*
 *传入圆的半径打印圆的面积
 *采用线程实现
 * */
#include<stdio.h>
#include<pthread.h>

#define PI 3.1415926
void *point(void * p){
	printf("圆周率为:%lf\n",PI);
	double * r = p;
	double area = PI * (*r) * (*r);
	printf("圆的面积为:%lf\n",area);
}
int main(void)
{
	pthread_t tid;
	double r = 2.5;
	printf("圆的半径为:%lf\n",r);
	pthread_create(&tid, NULL, point, &r);
//	sleep(1);
	pthread_join(tid, NULL);
	return 0;
}
