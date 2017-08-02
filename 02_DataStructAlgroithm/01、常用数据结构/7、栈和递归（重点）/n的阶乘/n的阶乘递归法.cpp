# include <stdio.h>

long factorial (long n);

long factorial (long n)
{
	//long mult;

	if (n == 1)
		return 1;
	else
		return n * factorial(n-1);
}
 
int main (void)
{
	long mult;
	long n;

	printf("请输入要求的阶乘，n=");
	scanf("%d",&n);

	mult = factorial (n);
	printf("%ld! = %ld\n",n,mult);
	
	return 0;
}
