# include<stdio.h>
int main(void)
{
	int a[4]={1,2,3,4};	
	int *pa = (int *)((int)a + 1);
	int *pb = *(&a + 1) - 1;
	printf("*pa:%d\n",*pa);
	printf("*pb:%d\n",*pb);
	return 0;
}
