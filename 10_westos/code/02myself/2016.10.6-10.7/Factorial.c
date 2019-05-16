# include<stdio.h>

int factorial(int a)
{
	if(a == 1)
		return 1;
	else
		return factorial(a-1) * a;
}
int main(void)
{
	int a = 2;
        int b = factorial(a);
	printf("b=%d",b);
}
