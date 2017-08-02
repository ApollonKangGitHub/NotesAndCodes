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
		temp = a[i];//����a[i]��ֵ

		low = 0;
		high = i-1;
		while(high >= low)
		{
			m = (low + high) / 2;
			if(temp < a[m])
				high = m-1;
			else
				low = m+1;
		}//whileѭ���ҳ�a[i]�Ĳ���λ��

		for(j = i; j > high+1; j--)
		{
			a[j] = a[j-1];
		}//����a[i]��������κ���

		a[j] = temp;//��a[i]��ֵ������ȷλ��
	}
}