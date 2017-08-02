/*
	2016Äê5ÔÂ19ÈÕ23:03:35
*/
# include <stdio.h>
# include "print.txt"

void sort(int * a, int len);
int main (void)
{
	int a[15] = {12,-5,23,-9,65,45,11,-8,10,-101,37,99,-1,0,2};
	print1(a,15);
	sort(a,15);
	print2(a,15);

	printf("%d",13/2);

	return 0;
}

void sort(int * a, int len)
{
	int gap = len/2;
	int i;
	for(gap; gap>0; gap=gap==2?1:static_cast<int>(gap/2))
	{
		for(i = gap; i<len; i++)
		{
			int temp = a[i];
			int j;

			for(j = i; j>=gap&&temp<a[j-1]; j = j-gap)
			{
				a[j] = a[j-gap];
			}
			a[j] = temp;
		}
	}
	return;
}

