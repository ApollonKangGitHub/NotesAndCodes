# include <stdio.h>
int main (void)
{
	int i;
	int sum = 0;

	for(i=3;i<=100;i=i+3)
	{
		if(i%3 == 0)
			sum+=i;
	}

	printf("sum=%d\n",sum);

	return 0;
}