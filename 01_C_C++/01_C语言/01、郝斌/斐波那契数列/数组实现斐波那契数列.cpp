/*����ʵ��쳲���������*/
# include <stdio.h>
int main (void)
{
	long fei[50]={1,1};

	int i;
	for(i=2;i<46;i++)
	{
		fei[i] = fei[i-1] + fei[i-2];
	}
	printf("쳲���������ǰ47��Ϊ:\n");
	for(i=0;i<46;i++)
	{
		printf("%-12ld",fei[i]);
		if((i+1)%6 == 0)
			putchar('\n');
	}

	putchar('\n');
	return 0;
}