# include <stdio.h>
int main (void)
{
	int sum = 0;
	int n;
	printf("please input n:\n");
	scanf("%d",&n);

	int i = 1;
	while(i<n+1)
	{
		sum += i;
		++i;
	}
	printf("sum=1+2+...+%d=%d\n",n,sum);

	return 0;
}
