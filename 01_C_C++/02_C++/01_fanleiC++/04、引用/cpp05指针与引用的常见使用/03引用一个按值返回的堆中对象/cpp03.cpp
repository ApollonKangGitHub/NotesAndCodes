/*
	2016年8月9日18:09:57
*/
# include <iostream>
using namespace std;

class Hello
{
public:
	Hello(int x){i = x;cout << "调用构造函数,创建了一个对象...\n";}
	Hello(Hello&a){i = a.i;cout << "执行复制构造函数，创建该对象的一个副本。\n";}
	~Hello(){cout << "析构函数运行中...\n";}
	int get()const{return i;}
private:
	int i;
};

Hello func()//返回值类型非引用型非指针型
{
	cout << "跳转到func()函数中!\n" << endl;
	Hello * p = new Hello(99);
	cout << "堆中对象a的地址：" << p << endl;
	return *p;
	//返回值*p不是指针不是引用，所以会调用复制构造函数创建副本，返回的是对象的副本
	//严重的错误之处：由于p指针保存了系统分配的内存地址，而return *p之后，p指向的空间并没有释放
	//p自身却已经释放，导致内存泄漏
}
int main (void)
{
	Hello & r = func();//func()函数返回堆中对象的副本，而不是该对象
	cout << "堆中对象的副本的地址为:" << &r << endl;
	cout << r.get() << endl;
	
	//Hello * p = &r;
	//delete p;
	//由于func()函数返回的是堆中对象的副本，这样删除的并不是对象的内存
	//并且这个副本由复制构造函数创建，保存在栈中，而不是堆中，由系统自动释放
	//不能由程序员delete，所以会发生崩溃，所以这种操作本身就不具备可执行性
	return 0;
}
