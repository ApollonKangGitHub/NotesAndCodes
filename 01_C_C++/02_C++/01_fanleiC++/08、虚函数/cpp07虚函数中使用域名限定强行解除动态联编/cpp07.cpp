# include <iostream>
using namespace std;
class A
{
public:
	virtual int get(){return 0;}
};
class B:public A
{
public:
	int get(){return 1;}
};
int main (void)
{
	B b;
	B * p = &b;
	A * q = &b;
	cout << p->get() << '\t' << q->get() << endl;
	cout << p->A::get() << '\t' << q->A::get() << endl;//加成员名后强制解除了限制
	cout << (*p).get() << '\t' << (*q).get() << endl; 

	return 0;
}