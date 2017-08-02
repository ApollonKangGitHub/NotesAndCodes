# include <stdio.h>
# define N 1000000
int main (void)
{
	int i, j;
	int cnt = 0;
	for(i = 3; i<N; i++)
	{
		for(j = 2; j<i && i%j != 0; j++);
		if(j == i)
		{
			printf("%d\t",i);
			cnt++;
		}
	}
	printf("\nnumber = %d\n",cnt);
	return 0;
}