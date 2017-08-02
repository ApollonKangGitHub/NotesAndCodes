# include<stdio.h>
int main(void)
{
	register int a = 6;//无需回写
	printf("%d\n",a);
	
	volatile int b = 8;//需要回写
	printf("%d\n",b);

	register volatile int c = 10;//似乎矛盾,其实不矛盾，与多线程的锁功能相似
	printf("%d\n",c);

	const volatile int d = 12;//const只读变量，而volatile易变的,似乎矛盾其实不矛盾
	printf("%d\n",d);
	return 0;
}
