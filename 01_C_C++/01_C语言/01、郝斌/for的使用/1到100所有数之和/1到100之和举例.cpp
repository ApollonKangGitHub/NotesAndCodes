# include <stdio.h>
int main (void)
{
	int i, sum = 0;

	for (i=1;i<=100;++i)
		sum +=  i; 

	printf("sum=1+2+3+...+100=%d\n",sum);

	return 0;

}