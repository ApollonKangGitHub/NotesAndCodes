# include <iostream>
using namespace std;

class A
{
public:
	A(int x){i = x; cout<< "构造函数运行中..." << endl;}
	~A(){cout << "析构函数执行中..." << endl;}
	int get(){return i;}

	operator int(){return i;}//此处不能加返回值类型，没有返回值类型不代表不可以返回值
	//如果加了返回值类型会报错：user-defined conversion cannot specify a return type
	//即用户定义的转换不能指定返回类型
	//若将return i注释掉，main函数中x的输出就是一个随机值

private:
	int i;
};
int main (void)
{
	A a(36);
	cout << a.get() << endl;
	a = 1000;//调用隐式转换，后台自行运行
	cout << a.get() << endl; 
	a = A(20);
	cout << a.get() << endl; 
	
	int x = 999;//调用隐式转换，后台自行运行
	a = x;//我们可以将变量赋给对象
	cout << a.get() << endl; 

	x = a;//将对象a的成员i，通过调用operator int函数返回给变量x
	//由于在类A中定义了operaator int函数才可以将类A定义的对象a的成员转换为int类型并赋给x
	//如果对象a对应的类中找不到operaator int函数以及其功能描述，则x=a的赋值不能成功
	cout << "x:" << x << endl;
	return 0;
}