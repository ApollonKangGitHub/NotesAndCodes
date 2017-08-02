# include <stdio.h>

int main (void)
{
	int n;
	int i;
	int sum=0;
	int sum1=0;

	printf("n=");
	scanf("%d",&n);
	for(i=1; i<=n; i++)
		sum = sum+i*((n-i+1));

	printf("s=%d\n",sum);

	return 0;
}