# include <stdio.h>

void move_element(int * a,int n);
int main (void)
{
	int i = 0;
	int a[8]={10,20,30,40,50,60,70,80};
	move_element(a,8);

	for(i=0; i<8; i++)
	{
		printf("%d  ",a[i]);
	}
	putchar('\n');

	return 0;
}

void move_element(int * a,int n)
{
	int i,j,t;
	/* 时间复杂度和空间复杂度都较小，但代码量大，不好*/
	for(i=0,j=n-1;j>i;i++,j--)
	{
		t = a[i];
		a[i] = a[j];
		a[j] = t;
	}
	for(i=0,j=n-4;j>i;i++,j--)
	{
		t = a[i];
		a[i] = a[j];
		a[j] = t;
	}
	for(i=n-3,j=n-1;j>i;i++,j--)
	{
		t = a[i];
		a[i] = a[j];
		a[j] = t;
	}
}
