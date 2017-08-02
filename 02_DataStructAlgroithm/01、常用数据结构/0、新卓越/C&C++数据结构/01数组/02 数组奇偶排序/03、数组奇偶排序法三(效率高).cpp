/*
	2016Äê5ÔÂ26ÈÕ20:50:37
*/
# include <stdio.h>
void sort(int * a, int len);
int main(void)
{
	int a[13] = {3,20,7,2,9,11,48,10,17,12,19,16,21};

	sort(a,13);
	for(int i = 0; i<13; i++)
		printf("%-4d",a[i]);
	printf("\n");

	return 0;
}

void sort(int *a, int len)
{
	int i = 0;
	int j = len-1;
	int temp;

	while(i<j)
	{
		while(i<len && a[i]%2 != 0)		i++;
		while(j>-1 && a[j]%2 == 0)		j--;
		if(i<j)
		{
			temp = a[i];
			a[i] = a[j];
			a[j] = temp;
		}
	}
}




