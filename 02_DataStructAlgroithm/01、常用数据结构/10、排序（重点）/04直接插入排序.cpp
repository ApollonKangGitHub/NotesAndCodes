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
	if(size<2)
		return;
	int temp;
	int i, j;
	for(i=1 ; i<size; i++)
	{
		temp = a[i];
		for(j = i;j > 0 && a[j-1] > temp; j--)
		{
			a[j] = a[j-1];
		}
		a[j] = temp;
	}
}