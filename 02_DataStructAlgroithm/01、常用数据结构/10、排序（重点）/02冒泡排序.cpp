/*
	2016��3��17��18:04:59
	ð������
*/
# include <stdio.h>
# include "print.txt"
# include "swap.txt"

void arr_sort1(int a[],int len);//2016��3��17��18:04:59  ��д
void arr_sort2(int a[],int len);//2016��5��16��20:47:24  �޸�

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
	2016��3��17��18:04:59
*/
void arr_sort1(int a[],int len)//int a[]��int * a������
{
	int i, j;
	for(i=0; i<len-1; i++)//����i<len����ȷ��i<len-1
	{
		for(j=0; j<len-1-i; j++)//ע��˴����ж������i��ͬ����ͬ������Ϊj<len-1-i
		{
			if(a[j] > a[j+1])
				swap_3(&a[j], &a[j+1]);
		}
	}
}
/*
	2016��5��16��20:47:24
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

		if(flag == true)//һ�αȽϺ�û�з����κα仯�����������Ѿ����
			return;
	}
	
}
