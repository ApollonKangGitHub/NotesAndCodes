/*
	2016年2月2日12:45:39
	求从m开始到n的奇数之和(m,n可赋值)
*/
# include <stdio.h>
int main (void)
{
	int i,n,m;
	int sum = 0;
	printf("please input m&n(m<n)(m=_,n=_):\n");
	scanf("m=%d,n=%d",&m,&n);

	for(i=m; i<=n; i +=2)
		sum += i;

	printf("%d到%d之间所有奇数之和为：sum=%d\n",m,n,sum);

	return 0;
}