# include <stdio.h>

long sum_n (long n);

long sum_n (long n)
{

	if (n == 1)
		return 1;
	else
		return n + sum_n (n-1);
}
 
int main (void)
{
	long sum;
	long n;

	printf("请输入要求的上限，n=");
	scanf("%ld",&n);

	sum = sum_n (n);
	printf("1+2+...+%ld = %ld\n",n,sum);
	
	return 0;
}
