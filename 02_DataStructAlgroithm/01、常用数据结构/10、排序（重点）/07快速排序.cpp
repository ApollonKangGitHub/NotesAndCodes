/*
	2016��5��9��17:25:41
	��������
*/
# include <stdio.h>
# include "print1.txt"
# include "print2.txt"

void QuickSort(int * a, int low, int high);
int FindPos(int * a, int low, int high);

int main (void)
{
	int a[15] = {2,-7,9,-12,13,25,-37,65,94,32,19,-8,20,14,-15};
	int i;

	print1(a,15);
	QuickSort(a, 0, 14);//a,0,14�ֱ�Ϊ������Ԫ�ص�ַ����Ԫ���±��Լ�ĩԪ���±�
	print2(a,15);

	return 0;
}

void QuickSort(int * a, int low, int high)
{
	int pos;

	if(low < high)
	{
		pos = FindPos(a, low, high);
		QuickSort(a, low, pos-1);
		QuickSort(a, pos+1, high);
	}
}

int FindPos(int * a, int low, int high)
{
	int val = a[low];

	while(low < high)//�ѱ�valС��ȫ���Ƶ�val��ߣ����ȫ���Ƶ�val�ұ�
	{
		while(low < high && a[high] >= val)
			high--;
		a[low] = a[high];

		while(low < high && a[low] <= val)
			low++;
		a[high] = a[low];
	}//��ֹ��low��high���

	a[low] = val;

	return low;//return highҲ����.
}