/*
	��ֵ����ֻ�ܴﵽЧ������Ч�����ܴﵽʵ����Ч
*/
# include <iostream>
using namespace std;

void swap(int a,int b)
{
	int c;
	cout << "����ǰ��swap������a = " << a << "�� b = " << b << endl;
	c = a;
	a = b;
	b = c;
	cout << "������swap������a = " << a << "�� b = " << b << endl;
}
int main (void)
{
	int a = 2;
	int b = 3;

	cout << "����ǰ��main������a = " << a << "�� b = " << b << endl;
	swap(a,b);
	cout << "������mian������a = " << a << "�� b = " << b << endl;

	return 0;
}