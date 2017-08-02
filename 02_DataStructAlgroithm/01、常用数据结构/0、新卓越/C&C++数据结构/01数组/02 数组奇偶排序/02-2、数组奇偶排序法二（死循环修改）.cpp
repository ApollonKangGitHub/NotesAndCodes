/*
	2016年5月26日22:15:53
*/
# include <stdio.h>
void sort(int *,int);
int main (void)
{
	int a[8] ={3,2,4,8,5,7,6,9};
	sort(a, 8);

	for(int i=0;i<8;i++)
		printf("%-4d",a[i]);
	
	putchar('\n');
	return 0;
}

void sort(int * a, int len)
{
	int i, j, temp, point;
	i = 0;
	point = len-1;

	while(i < point)
	{
		if(a[i] % 2 != 0)
			i ++;
		else
		{
			temp = a[i];
			for(j = i; j < point; j++)
				a[j] = a[j+1];
			a[j] = temp;
			point --;
			//每当偶数向后挪一次，point向前挪一次，则point及后边的元素都已经是偶数。既避免了重复移动，又将死循环消除
		}
	}
}