/*
	2016年5月17日23:14:02
*/
# include <stdio.h>
# include "print.txt"
# include "swap.txt"

void sort (int * a,int size);

int main (void)
{
	int a[11] = {12,25,36,34,84,56,98,75,15,-51,-33};
	
	print1(a,11);
	sort (a,11);
	print2(a,11);

	return 0;
}

void sort (int * a,int size)
{
	int i,j;
	int low = 0;
	int up = size-1;
	int index = 0;
	while(low < up)
	/*
	循环如何结束：
	low从0开始增加，up从size-1开始减少。当排序提前结束时
	如up=6，index=3，low=3时排序已完成，之后进入while循环判断，3<6成立。
	但是排序已完成,所以两个内循环都不会改变上次循环的index即index=3,
	up=index=3,low=index=3。
	再次进行判断3<3不成立，结束排序。
	*/
	{
		for(i = low; i < up; i++)
			if(a[i] > a[i+1])
			{
				swap_1(&a[i], &a[i+1]);
				index = i;
			}//把最大的数移到最后面

		up = index;
		for(i = up; i>low; i--)
			if(a[i] < a[i-1])
			{
				swap_3(&a[i], &a[i-1]);
				index = i;
			}//把最小的数移到最前面
		low = index;
	}
}