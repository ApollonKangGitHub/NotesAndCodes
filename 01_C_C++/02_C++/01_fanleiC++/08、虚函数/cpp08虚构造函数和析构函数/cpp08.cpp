# include <iostream>
using namespace std;

class A
{
public:
	A(){cout << "创建A" << endl;}
	virtual void func(){cout << "类A" << endl;}
	//~A(){cout << "析构A" << endl;}
	virtual ~A(){cout << "析构A" << endl;}//如果基类中定义了虚函数，那么析构函数也应该定义成虚函数，这样内存的会收会更准确些
};
class B : public A
{
public:
	B(){cout << "创建B" << endl;}
	virtual void func(){cout << "类B" << endl;}
	~B(){cout << "析构B" << endl;}
};
int main (void)
{
	A * p = new B;
	p->func();
	delete p;
	return 0;
}