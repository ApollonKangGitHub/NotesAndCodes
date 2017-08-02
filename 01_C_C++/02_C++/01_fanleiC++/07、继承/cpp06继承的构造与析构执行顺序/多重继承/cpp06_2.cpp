/*
	2016年8月22日13:14:52
	运行结果：
		构造e...
		构造b...
		构造c...
		构造d...
		构造a...
		构造f...
		析构f...
		析构a...
		析构d...
		析构c...
		析构b...
		析构e...
		Press any key to continue

	多重继承的构造函数与析构函数执行顺序：
	>>基类的构造函数执行顺序是按照继承时，代码中给定的顺序执行的
	>>析构函数执行顺序则是按先构造后析构，后构造先析构的顺序执行的
	>>子类的构造函数在基类构造函数执行完以后执行，即子类构造函数最后执行，析构函数最先执行


*/
# include <iostream>
using namespace std;

class a
{
public:
	a(){cout << "构造a..." << endl;}
	~a(){cout << "析构a..." << endl;}
};
class b
{
public:
	b(){cout << "构造b..." << endl;}
	~b(){cout << "析构b..." << endl;}
};
class c
{
public:
	c(){cout << "构造c..." << endl;}
	~c(){cout << "析构c..." << endl;}
};
class d
{
public:
	d(){cout << "构造d..." << endl;}
	~d(){cout << "析构d..." << endl;}
};
class e
{
public:
	e(){cout << "构造e..." << endl;}
	~e(){cout << "析构e..." << endl;}
};

class f:public e, public b, public c, public d, public a
{
public:
	f(){cout << "构造f..." << endl;}
	~f(){cout << "析构f..." << endl;}
};
int main (void)
{
	f five;

	return 0;
}