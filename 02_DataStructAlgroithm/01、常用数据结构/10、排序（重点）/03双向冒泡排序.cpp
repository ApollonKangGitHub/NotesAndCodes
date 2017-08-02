/*
	2016��5��17��23:14:02
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
	ѭ����ν�����
	low��0��ʼ���ӣ�up��size-1��ʼ���١���������ǰ����ʱ
	��up=6��index=3��low=3ʱ��������ɣ�֮�����whileѭ���жϣ�3<6������
	�������������,����������ѭ��������ı��ϴ�ѭ����index��index=3,
	up=index=3,low=index=3��
	�ٴν����ж�3<3����������������
	*/
	{
		for(i = low; i < up; i++)
			if(a[i] > a[i+1])
			{
				swap_1(&a[i], &a[i+1]);
				index = i;
			}//���������Ƶ������

		up = index;
		for(i = up; i>low; i--)
			if(a[i] < a[i-1])
			{
				swap_3(&a[i], &a[i-1]);
				index = i;
			}//����С�����Ƶ���ǰ��
		low = index;
	}
}