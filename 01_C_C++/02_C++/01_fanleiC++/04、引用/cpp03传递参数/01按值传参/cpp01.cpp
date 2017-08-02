/*
	按值传参只能达到效果上有效，不能达到实质有效
*/
# include <iostream>
using namespace std;

void swap(int a,int b)
{
	int c;
	cout << "交换前，swap函数中a = " << a << "， b = " << b << endl;
	c = a;
	a = b;
	b = c;
	cout << "交换后，swap函数中a = " << a << "， b = " << b << endl;
}
int main (void)
{
	int a = 2;
	int b = 3;

	cout << "交换前，main函数中a = " << a << "， b = " << b << endl;
	swap(a,b);
	cout << "交换后，mian函数中a = " << a << "， b = " << b << endl;

	return 0;
}