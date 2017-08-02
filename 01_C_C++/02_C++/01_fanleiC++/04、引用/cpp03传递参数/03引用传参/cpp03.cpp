/*
	引用传参对齐内存进行操作，也是实质上的交换操作
	只不过引用型传参是被调函数定义的引用变量，挂在了主调函数参数的地址上，对被调函数引用变量的操作还是普通变量的操作。
	而传址传参是被调函数接收主调函数参数的地址，对被调函数的操作是用指针操作，为指针型变量的操作。
*/
# include <iostream>
using namespace std;

void swap(int & a,int & b)
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