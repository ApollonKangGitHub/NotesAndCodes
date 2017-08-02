/*
	选择排序
	2016年5月17日11:59:55
*/
# include <stdio.h>
# include "swap.txt"
# include "print.txt"

void choose (int * ,int );

int main (void)
{
	int arr[12] = {49,58,36,32,63,105,98,66,35,15,24,74};
	print2(arr,12);
	choose(arr,12);
	print2(arr,12);

	return 0;
}


void choose (int * a,int size)
{
	int min;
	for(int i=0; i<size; i++)
	{
		min = i;
		for(int j=i+1; j<size; j++)
		{
			if(a[min] > a[j])
				min = j;
		}
		if(min != i)
			swap_1 (&a[min],&a[i]);
			//swap_2 (&a[min],&a[i],sizeof(int));
			//swap_3 (&a[min],&a[i]);
			//swap_4 (&a[min],&a[i]);
	}
}
