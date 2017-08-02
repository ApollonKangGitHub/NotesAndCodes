/*
	2016年3月17日18:04:59
	冒泡排序法
*/
# include <stdio.h>

void pai(int a[],int len)//int a[]与int * a均可以
{
	int i, j, t;
	for(i=0; i<len-1; i++)//错误：i<len；正确：i<len-1
	{
		for(j=0; j<len-1-i; j++)//注意此处的判断语句因i不同而不同，所以为j<len-1-i
		{
			if(a[j] > a[j+1])
			{
				t = a[j];
				a[j] = a[j+1];
				a[j+1] = t;
			}
		}
	}
}
int main(void)
{
	int a[8];
	int i;
	printf("请输入你要排序的八个数字：\n");
	for(i=0; i<8; i++)
	{
		scanf("%d,",&a[i]);
	}

	pai(a,8);
	for(i=0;i<8;i++)//第一次调试错误，该句后加了不该加的分号
	{
		printf("%-4d",a[i]);
	}
	printf("\n");

	return 0;
}