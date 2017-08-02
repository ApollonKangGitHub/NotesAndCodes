# include<iostream>
using namespace std;

class A
{
public:
	void Func(){cout<<A::x;}//要访问私有的静态成员变量，只能由已有对象通过调用公有成员函数来调用。
private:
	static int x;//私有的静态成员变量
};
int A::x=1000;
int main(void)
{
	A a;
	a.Func();
	cout<<endl;
	return 0;
}