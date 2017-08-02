# include <iostream>
using namespace std;

class A
{
public:
	explicit A(int x){i = x; cout << "构造函数执行中..." << i<< endl;}
	//explicit用来关闭强制转换，防止出现非人为的类型转换出现，但只能关闭隐式转换（隐式转换不易发觉），不能关闭显式转换
	~A(){cout << "析构函数执行中..." << i << endl;}
	void get(){cout << i << endl;}
private:
	int i;
};
int main (void)
{
	A a(99);
	a.get();
	//a.~A();
	//a = 1000;//等价于a = A(1000);调用构造函数创建了一个临时对象，所以需要析构
	a = A(1000);
	//当参数个数不止一个时，采用a = A()的形式
	//a = 1000;为隐式转换。a = A(1000);为显式转换


	return 0;
}