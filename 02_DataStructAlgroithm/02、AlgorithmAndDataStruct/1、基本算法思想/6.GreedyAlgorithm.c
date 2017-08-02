/*
 *贪心算法：并非整体最优解，但是时效性最优解
 *2017年4月26日17:15:58
*/
#include<stdio.h>
#define MAXN 12

//单位是分,若将某个面值去掉(修改掉也可以测试)
//eg:将200(即2元)修改为20000(200元),就相当于这个面值没有了
//注意：测试值应该小于100
int parvalue[MAXN] = {5000,2000,1000,500,200,100,50,20,10,5,2,1};	
int num[MAXN] = {0};

void exchange(int n)
{
	int i = 0;
	while(n>0 && i<MAXN){	//n大于零则继续找零钱
		if(n>=parvalue[i]){	//
			n -= parvalue[i];
			num[i]++;
		}
		else{
			i++;	//否则计算当前面值完毕计算下一个小的面值
		}
	}
}
int main(void)
{
	//用78.45测试float_%f与double_%lf还是有区别的
	double money;
	int i;
	printf("请输入要找零钱的余额:\n");
	scanf("%lf",&money);
	exchange((int)(money*100));	//以元为单位转换成以分为单位
	printf("找零方案：%.2lf:\n",money);
	for(i=0; i<MAXN; i++)
		if(num[i]>0)
			printf("%6.2lf:%d张\n", (float)(parvalue[i]/100.0),num[i]);
	printf("%X\n",money);
	return 0;
}
