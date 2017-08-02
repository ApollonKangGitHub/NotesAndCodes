/*
	2016年8月9日18:26:46
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
	void set(int x){i = x;}
private:
	int i;
};

Hello & func(Hello & a)//返回值类型为引用型
{
	cout << "跳转到func()函数中!\n" << endl;
	a.set(66);
	cout << "堆中对象的地址：" << &a << endl;
	return a;

}
int main (void)
{
	Hello * p = new Hello(99);
	func(*p);
	cout << p->get() << endl;

	delete p;//在main函数中创建堆中对象，在main函数中释放

	return 0;
}
/*
总结，第一种按值返回的方法会出现内存泄漏，肯定不应该使用
第二种方法，的重要问题其实也不在空引用（只要在main函数最终结束前释放p就不会产生问题），而是方法过于繁琐容易出错
第三种即本程序，不繁琐，不会出现内存泄漏，但是也会出现空引用，只要在释放之后还想用堆中已经释放的对象也是会出问题的
所以，无论怎样写，记住几个原则：
	>>堆中对象返回的指针在堆中内存释放之前绝对不能丢弃
	>>堆中空间释放之后，创建的对象不能再使用。所以释放堆中内存要注意释放的位置（不一定最后统一释放是最好的）
	>>在哪（那个函数中）申请堆内存就在那个函数中释放堆内存
	>>特别注意按值返回、按址返回以及按引用返回之间，对于复制构造函数与析构函数的调用的区别


