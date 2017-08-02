# include <stdio.h>
int main (void)
{
	int i, j, n, t, l;

	printf("please input n:");
	scanf("%d",&n);

	for(i=1;i<=n;i++)
	{
		l = 2*(i-1)+1;
		t = (n-l)/2;

		if(0 > t)
		{
			l = 2*(n-i)+1;
			t = (n-l)/2;
		}
		for(j=1; j<=t; j++)		printf("  ");
		for(j; j<=n-t; j++)		printf("* ");
		for(j; j<=n-1; j++)		printf("  ");

		printf("\n");
	}
	return 0;	
}