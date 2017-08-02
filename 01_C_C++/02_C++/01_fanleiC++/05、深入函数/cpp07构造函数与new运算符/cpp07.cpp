/*
	2016年8月19日18:01:30
	类所占字节数与结构体的遵循规则相同：内存对齐与内存补齐（在栈中和堆中一样）
*/
# include <iostream>
using namespace std;
class A
{
public:
	int get(){return i+j+(int)m;}
	A(int x = 0, int y = 0, char c = ' ', double n = 0.0):i(x),j(y),ch(c),m(n){cout << "调用构造函数" << endl;}
	~A(){cout << "调用A的析构函数..." << endl;}
private:
	const int i;
	const int j;
	const char ch;
	const double m;
};

class B
{
public:
	int get(){return i + j + (int)m;}
	B(int x = 0, int y = 0, char c = ' ', double n = 0.0):i(x),j(y),ch(c),m(n){cout << "调用构造函数" << endl;}
	~B(){cout << "调用B的析构函数..." << endl;}
private:
	int i;
	int j;
	char ch;
	double m;
};
int main (void)
{
	A a(5,7,'2',2.225);
	B * b = new B(5,2,'p',3.665);

	cout << "类A所占内存为：" << sizeof(A) << "字节" << endl;
	cout << a.get() << endl;

	cout << "类B所占内存为：" << sizeof(B) << "字节" << endl;
	cout << b->get() << endl;

	delete b;
	b = 0;
	return 0;
}