/*
	2016��7��29��12:46:41
	�����ͱ���
*/
# include <iostream>
using namespace std;

void swap(int * x, int * y);
void swap(int & x, int & y);//�����������������Ͳ�ͬ���ʿ��Ժ�����������֧�ֺ�������

int main (void)
{
	cout << "��������Ҫ��������x��y:" << endl;
	int x, y;
	cin >> x >> y;
	cout << "����֮ǰ: x = " << x << " y = " << y <<endl;
	cout << "����֮��: ";
	swap(&x,&y);

	cout << "x = " << x << " y = " << y << endl;
	cout << "����֮ǰ: x = " << x << " y = " << y <<endl;
	cout << "����֮��: ";
	swap(x,y);

	cout << "x = " << x << " y = " << y << endl;
	return 0;
}

void swap(int * a,int * b)
{
	int temp = *a;
	*a = *b;
	*b = temp;

	return;
}
void swap(int &x, int &y)
{
	int temp = x;
	x = y;
	y = temp;

	return;
}

