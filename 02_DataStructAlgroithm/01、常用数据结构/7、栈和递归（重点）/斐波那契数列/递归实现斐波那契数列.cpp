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

		printf("��ֱ��������Ҫ���ҵ�����n(���������������ƣ�������0<n<47)��\n");
		scanf("%ld",&n);
		sum = Fibonacci (n);

		printf("쳲��������е�%ld��Ϊ:%ld\n",n,sum);
	
	return 0;
}


