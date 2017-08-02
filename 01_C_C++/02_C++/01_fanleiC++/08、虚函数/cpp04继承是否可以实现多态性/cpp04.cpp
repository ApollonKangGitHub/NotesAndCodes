# include <iostream>
using namespace std;
class A
{
public:
	void print(){cout << "a" << endl;}
	//virtual void print(){cout << "a" << endl;}
	/*
		使用virtual时，C++对该函数实行动态联编，
		不使用virtual时，C++对该函数实行静态联编
	*/
};
class B : public A
{
public:
	void print(){cout << "b" << endl;}
};
class C : public A
{
public:
	void print(){cout << "c" << endl;}
};

int main(void)
{
	A a;
	B b;
	C c;
	
	a.print();
	b.print();
	c.print();

	A * pa = &a;
	A * pb = &b;
	A * pc = &c;
	//静态联编是使指针pa，pb，pc一开始就确定了指向为基类。并不会因为后来运行时的三个地址赋给指针而发生改变，而是继续使用默认的地址，指向基类
	//而动态联编只有在给pa，pb，pc分别赋值为&a，&b，&c时才确定了各自的指向为不同的类
	//可见继承想要实现多态性就必须用关键字virtual修饰需要联编的函数

	pa->print();
	pb->print();
	pc->print();

	return 0;
}