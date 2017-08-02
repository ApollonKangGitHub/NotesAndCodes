/*
	函数的缺省参数即参数列表的初始化，
	初始化之后，则可以不进行传参，此时初始化的值就是默认的参数进行使用；
	若初始化后进行传参，那么传递的新参数就覆盖初始化的参数，进行使用

*/
# include <iostream>
using namespace std;

class A
{
public:
	void set (int = 30, int = 50);
	//函数声明时不需要带参数名，所以缺省参数（即参数列表初始化）时直接赋值即可
	//void set (int width = 30, int height = 50);
	//也可以带参数名，但是以后的使用只能用已经命名的参数名了。
	void count(bool = false);
	//void count(bool val = false);
private:
	int w;
	int h;
};

void A::set (int width, int height)
{
	w = width;
	h = height;
}

void A::count(bool val)
{
	if(val == true)
		cout << "val的值为真时："  << w*h << endl;
	else
		cout << "val的值为假时："  << w*h/2 << endl;
}

void func(int n = 1, int m = 2)
{
	cout << "n:" << n << "\t" << "m:" << m <<endl;
}

int main (void)
{
	func();
	func(7,12);
	
	A a;
	a.set();
	a.count();
	a.count(true);
	//缺省参数（具有默认值）的函数，也实现了函数重载。一个调用不带参数，一个调用带参数
	//具有默认参数的函数重载的是参数的数值，而重载函数重载的是参数的类型
	//具有默认参数的函数不加标注容易被忽略，而且容易被带有参数的同名函数覆盖

	a.set(25,30);
	a.count();
	a.count(true);

	return 0;
}