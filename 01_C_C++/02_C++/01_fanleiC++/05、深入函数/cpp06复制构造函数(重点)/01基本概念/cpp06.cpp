# include <iostream>
using namespace std;
class A
{
public:
	A(){cout << "构造函数运行中..." << endl;}
	~A(){cout << "析构函数运行中..." << endl;}
	A(A&one){cout << "复制构造函数运行中..." << endl;this->n = one.n; this->m = one.m;}
	A(int i, int j){cout << "构造函数运行中..." << endl; n = i; m = j;}//带参数的构造函数
	void print(){cout << n <<  "\t" << m << endl;}
private:
	int n;
	int m;
};
int main (void)
{
	A a(2,4);
	a.print();
	A b(a);//调用类A中复制构造函数,将a的成员全部复制拷贝给b
	b.print();
	
	return 0;
}