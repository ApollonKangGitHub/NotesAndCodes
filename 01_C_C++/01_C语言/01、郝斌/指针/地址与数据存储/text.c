# include <stdio.h>
int main (void)
{
	double i = 2.25;
	double * p = &i;

	printf("%d,%d\n",*p,*(p+1));
	printf("%d,%d\n",*(int *)p,*(int *)(p+1));
	return 0;
}

/*
i=2.0Ê±£º
0,1073741824
0,1638272
Press any key to continue

i=2.25Ê±£º
0,1073872896
0,1638272
Press any key to continue

*/



