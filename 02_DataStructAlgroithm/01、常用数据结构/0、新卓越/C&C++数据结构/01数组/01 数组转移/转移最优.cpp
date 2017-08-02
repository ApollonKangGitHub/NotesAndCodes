
/*
	2016年4月28日21:03:17
	最优代码
*/
# include <stdio.h>

void move_element(int * a, int s, int e)
{
	int i, j, temp;

	for(i=s,j=e;i<j;i++,j--)
	{
		temp = a[i];
		a[i] = a[j];
		a[j] = temp;
	}

	return;
}
int main (void)
{
	int i = 0;
	int a[8]={10,20,30,40,50,60,70,80};

	move_element(a,0,7);
	move_element(a,0,4);//传区间
	move_element(a,5,7);

	for(i=0; i<8; i++)
	{
		printf("%-5d",a[i]);
	}
	putchar('\n');

	return 0;
}//所有数据集合的移动算法都可以通过浪费空间来解决。
//描写算法不可以浪费空间为前提
