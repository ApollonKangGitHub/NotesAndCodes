/*
	2016年8月9日15:46:59
	引用相对于指针的优点之一：不用过多的const修饰（因为引用本身就是一个常量，初始化后不能再修改）
*/
# include <iostream>
using namespace std;

class A
{
public:
	A(){cout << "执行构造函数构造一个对象。\n";}//构造函数
	A(A&){cout << "执行复制构造函数，创建该对象的一个副本。\n";}//复制构造函数
	~A(){cout << "执行析构函数,删除对象...\n";}//析构函数
	void set(int x){i = x;}
	int get()const{return i;}
private:
	int i;
};

A & func (A & one)									
{			
	one.get();
	one.set(10);//A并没有被限制，因此可以通过别名来修改成员，如果A前面加const修饰，则不能通过别名修改对象值，但仍然可以通过自身变量名修改
	return one;	//返回的虽然不是地址，而是对象a的别名，但是也不会调用复制构造函数，引用就类似与用地址进行操作（拥有指针的功能，有别于指针的特性）
}
int main (void)
{
	A a;
	a.set(11);
	cout << a.get() << endl;
	//A b = func(a);//不会引起编译错误，但是程序功能不会成功，这样的b并不是a的别名
	A & b = func(a);

	cout << "b的地址：" << &b << endl << "对象a的地址：" << &a << endl;
	a.set(20);//不管A被修饰否，都能复制成功
	b.set(50);//如果A被修饰则不能成功，会报错
	cout << b.get() << endl;

	return 0;
					
}
