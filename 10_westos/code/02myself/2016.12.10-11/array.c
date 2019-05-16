# include<stdio.h>
int main(void)
{
	int a[3][4];
	int b[3][4];
	double c;
	printf("sizeof(a):%d\n",sizeof(a));
	printf("sizeof(&a[0]):%d\n",sizeof((&a[0])));
	printf("sizeof(ar+1):%d\n",sizeof(*(int *)a[2][1]));
	printf("sizeof(&a[0]+1):%d\n",sizeof(&a[0]+1));
	return 0;
}
