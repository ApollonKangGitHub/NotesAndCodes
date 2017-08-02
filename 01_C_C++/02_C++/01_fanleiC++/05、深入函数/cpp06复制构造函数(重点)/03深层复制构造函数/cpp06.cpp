/*
	解决浅层复制带来的问题的方法是：深层复制
	即为新对象创建一块新的内存。对一个对象的操作不会影响另一个
*/
# include <iostream>
using namespace std;

class A
{
public:
	A(){x = new int; *x = 5;cout << "构造函数执行中..." << endl;}
	~A(){delete x; x = NULL;cout << "析构函数执行中..." << endl;}
	A(const A&a)
	{
		cout << "复制构造函数执行中..." << endl;
		x = new int;
		*x = *(a.x);//左边*x为复制构造函数创建的新对象的x成员所指向的空间。右边为接收的旧对象的x成员所指向的空间。
		//两块空间不是一个空间,把旧的复制过来。对新的操作就不会影响旧的了
	}
	void set(int i){*x = i;}
	int print()const{return *x;}//const表示print函数不会修改x指针的值
private:
	int * x;
};
int main (void)
{
	A * a = new A();
	cout << "a:" << a->print() << endl;
	a->set(50);
	cout << "a:" << a->print() << endl;

	A b = (*a);//复制过去时b对象的成员值为50
	a->set(20);//修改a指向的对象的成员值不会改变b对象的成员值
	cout << "a:" << a->print() << endl;
	cout << "b:" << b.print() << endl;

	b.set(80);//修改b指向的对象的成员值也不会改变a对象的成员值
	cout << "a:" << a->print() << endl;
	cout << "b:" << b.print() << endl;

	delete a;
	//cout << "a:" << a->print() << endl;//a指向空间已经释放，无法再使用
	cout << "b:" << b.print() << endl;


	return 0;
}