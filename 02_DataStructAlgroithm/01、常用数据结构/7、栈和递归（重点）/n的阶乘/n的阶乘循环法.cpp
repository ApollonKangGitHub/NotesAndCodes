# include <stdio.h>

int main (void)
{
	int n,k;
	long mult = 1;
	printf("请输入您要求的阶乘，n=:");
	scanf("%d",&n);

	for(k=1;k<=n;k++)
	{
		mult *= k;
	}

	printf("%d的阶乘为：%d! = %ld\n",n,n,mult);
	return 0;
}