# include <stdio.h>
# include <stdlib.h>

long Fibonacci (long n);

long Fibonacci (long n)
{
	if (1 == n || 2 == n)
		return 1;
	else 
		return Fibonacci (n-1) + Fibonacci (n-2);

}
int main(void)
{
	long n;
	long sum;

		printf("请直接输入您要查找的项数n(由于数据类型限制，请输入0<n<47)：\n");
		scanf("%ld",&n);
		sum = Fibonacci (n);

		printf("斐波那契数列第%ld项为:%ld\n",n,sum);
	
	return 0;
}


