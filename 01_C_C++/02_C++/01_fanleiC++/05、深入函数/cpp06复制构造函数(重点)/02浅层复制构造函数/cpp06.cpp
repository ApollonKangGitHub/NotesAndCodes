/*
	2016年8月19日19:14:41
*/
# include <iostream>
using namespace std;

class A
{
public:
	A(){x = new int; *x = 5;cout << "构造函数执行中..." << endl;}
	~A(){delete x; x = NULL;cout << "析构函数执行中..." << endl;}
	A(const A&a)//定义为const型，引用变量接收的内容将只能使用，不可改变。但是通过指针可以进行直接修改
	{
		cout << "复制构造函数执行中..." << endl;
		x = a.x;//浅层复制（两个对象占用一块儿内存区域）
	}//该复制构造函数与系统默认的复制构造函数基本相同
	void set(int i){*x = i;}
	int print()const{return *x;}//只输出*x,不可以改变*x
private:
	int * x;
};
int main (void)
{
	A * a = new A();
	cout << "a:" << a->print() << endl;
	a->set(50);
	cout << "a:" << a->print() << endl;

	A b = (*a);
	a->set(20);
	cout << "b:" << b.print() << endl;
	b.set(50);
	cout << "b:" << a->print() << endl;
	//将*a传递给复制构造函数，a指向复制构造函数开辟的堆中空间，b的指针域x也指向该堆空间。实现了*a赋给b的目的

	//delete a;
	//由于复制构造函数创建的b对象的x指针指向的堆中空间先释放，释放之后再析构a指向的对象。而a指向对象就是b指向的对象
	//已经释放的空间无法找到变回发生崩溃。这种崩溃产生的原因就是浅层复制
	return 0;
}