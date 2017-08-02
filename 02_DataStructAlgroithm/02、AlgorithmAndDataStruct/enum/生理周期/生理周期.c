/*
 *体力(p)周期：23天
 *情商(e)周期：28天
 *智商(i)周期：33天
 *给定p、e、i的日期，给定d，求出下一个p、e、i在同一天的日子k距离d的天数差
*/
#include <stdio.h>

int main(void)
{
	int p,e,i,d,k;
	printf("Please enter p e i d:\n");
	scanf("%d%d%d%d",&p,&e,&i,&d);

	for(k=d+1; (k-p)%23; k++);//寻找下一个体力高峰期
	for(; (k-e)%28; k+=23);//寻找下一个体力、情商双高峰
	for(; (k-i)%33; k+=23*28);//寻找下一个体力、情商、智商高峰期在同一天的日期

	printf("next pQ/eQ/iQ at same day to 'set d' distance is:%d\n",k-d);
	return 0;
}