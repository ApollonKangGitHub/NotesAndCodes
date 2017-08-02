/*
	2016Äê6ÔÂ3ÈÕ00:25:01
*/
# include <stdio.h>
# define N 100
int main (void)
{
	int i, j;
	int cnt = 0;
	for(i = 3; i<N; i++)
	{
		for(j = 2; j<i; j++)
		{
			if(i%j == 0)
				break;	
		}
		if(j == i)
		{
			printf("%-10d",i);
			cnt++;
			if(cnt % 15 == 0)
				printf("\n");
		}
	}
	printf("\nnumber = %d\n",cnt);
	return 0;
}