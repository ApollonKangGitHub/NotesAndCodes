/*
	2016年3月17日18:04:59
	冒泡排序法
*/
# include <stdio.h>
# include "print.txt"
# include "swap.txt"

void arr_sort1(int a[],int len);//2016年3月17日18:04:59  初写
void arr_sort2(int a[],int len);//2016年5月16日20:47:24  修改

int main(void)
{
	int a[8] = {11,22,88,77,66,54,33,29};
	
	print1(a,8);
	//arr_sort1(a,8);
	arr_sort2(a,8);
	print2(a,8);

	return 0;
}

/*
	2016年3月17日18:04:59
*/
void arr_sort1(int a[],int len)//int a[]与int * a均可以
{
	int i, j;
	for(i=0; i<len-1; i++)//错误：i<len；正确：i<len-1
	{
		for(j=0; j<len-1-i; j++)//注意此处的判断语句因i不同而不同，所以为j<len-1-i
		{
			if(a[j] > a[j+1])
				swap_3(&a[j], &a[j+1]);
		}
	}
}
/*
	2016年5月16日20:47:24
*/
void arr_sort2(int a[],int n)
{
	int i, j;
	bool flag;

	for(i = n-1;  i >= 1; i--)
	{
		flag = true;
		for(j=0; j<i; j++)
			if(a[j] > a[j+1])
			{
				swap_4(&a[j], &a[j+1]);
				flag = false;
			}

		if(flag == true)//一次比较后没有发生任何变化则，数组排序已经完成
			return;
	}
	
}
