# include <iostream>
using namespace std;
int main (void)
{
	int a[13] = {1,1};
	int i = 0;
	for(i; i<13; i++)
	{
		if(i>1)	a[i] = a[i-1] + a[i-2];
		cout << "��" << i << "���º����������Ϊ��" << a[i] << endl;
	}
	return 0;
}