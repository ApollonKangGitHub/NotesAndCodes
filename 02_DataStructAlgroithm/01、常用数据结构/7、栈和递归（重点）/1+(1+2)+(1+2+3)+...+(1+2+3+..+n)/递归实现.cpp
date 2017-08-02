/*
	2016年5月15日00:35:14
	题目：sum=1+(1+2)+(1+2+3)+(1+2+3+4)+...+(1+2+3+4+..+n)

	分析：sum=n*1 + (n-1)*2 + (n-2)*3 + ... + 2*(n-1) + 1*n
*/
# include <stdio.h>

int SumMain(int n);//递归函数
int sum_n(int n);

int SumMain(int n)
{
	if (1 == n)
		return 1;
	else
		return SumMain(n-1) + sum_n(n);
}
int sum_n(int n)
{
	int sum = 0;
	for(int i=1; i<=n; i++)
	{
		sum +=i;
	}
	return sum;
}
int main (void)
{
	int n;
	int sum;

	printf("n=");
	scanf("%d",&n);
	sum = SumMain(n);
	
	printf("s=%d\n",sum);

	return 0;
}