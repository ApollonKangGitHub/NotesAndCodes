# include<stdio.h>

int i;
int main(void)
{
	static int j;
	int k;

	printf("i:%dj:%dk:%d\n",i,j,k);
	return 0;
}
