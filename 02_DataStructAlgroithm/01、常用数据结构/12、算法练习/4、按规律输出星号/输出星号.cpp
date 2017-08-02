# include <stdio.h>

void star_one (int n);
void star_two (int n);
void star_three (int n);
void star_four (int n);


int main (void)
{
	int i,j,n;
	printf("Please input your number n:");
	scanf("%d",&n);

	putchar('\n');
	star_one (n);
	putchar('\n');
	star_two (n);

	star_three (n);
	putchar('\n');
	star_four (n);
	
	putchar('\n');
	return 0;
}

void star_one (int n)
{
	int i,j;
	for(i=1; i<=n ;i++)
	{
		for(j=1;j<=i;j++)
		{
			printf("* ");
		}
		putchar('\n');
	}

}

void star_two (int n)
{
	int i,j;
	for(i=n; i>=1 ;i--)
	{
		for(j=1;j<=i;j++)
		{
			printf("* ");
		}
		putchar('\n');
	}

}

void star_three (int n)
{
	int i, j;
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n-i;j++)
		{
			printf("  ");
		}
		for(j;j<=n;j++)
		{
			printf("* ");
		}
			putchar('\n');
	}

}

void star_four (int n)
{
	int i,j;
		for(i=n;i>0;i--)
	{
		for(j=1;j<=n-i;j++)
		{
			printf("  ");
		}
		for(j;j<=n;j++)
		{
			printf("* ");
		}
			putchar('\n');
	}


}