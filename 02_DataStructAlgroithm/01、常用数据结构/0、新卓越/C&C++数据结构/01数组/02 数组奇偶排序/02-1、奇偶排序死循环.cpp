/*
	2016��5��26��19:43:31
	ע����ѭ��
*/
# include <stdio.h>

void sort(int *, int);

int main (void)
{
	int a[8] = {3,1,11,81,5,7,61,9};
	
	sort(a,8);

	for(int i =0; i<8; i++)
		printf("%-5d",a[i]);

	return 0;
}

void sort(int * a, int len)
{
	int temp;
	int i = 0;

	while(i<len)//ֻҪ��������һ��ż���ͻ�������ѭ��
	{
		if(a[i]%2 != 0)
			i++;
		else
		{
			temp = a[i];
			for(int j = i; j<len; j++)
				a[j] = a[j+1];
			a[j] = temp;
		}
	}
	
}
