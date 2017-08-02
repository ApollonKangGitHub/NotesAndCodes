# include <stdio.h>
# include "print.txt"

void sort (int * a,int size);

int main (void)
{
	int a[20] = {12,-25,36,34,-84,56,98,75,15,-51,-33,-9,89,101,153,29,-18,111,62,47};
	print1(a,20);
	sort (a,20);
	print2(a,20);

	return 0;
}

void sort (int * a,int size)
{
	int i, j, temp, low, high, m;
	for(i =1 ; i < size; i++)
	{
		temp = a[i];//保存a[i]的值

		low = 0;
		high = i-1;
		while(high >= low)
		{
			m = (low + high) / 2;
			if(temp < a[m])
				high = m-1;
			else
				low = m+1;
		}//while循环找出a[i]的插入位置

		for(j = i; j > high+1; j--)
		{
			a[j] = a[j-1];
		}//将比a[i]大的数依次后移

		a[j] = temp;//将a[i]的值插入正确位置
	}
}