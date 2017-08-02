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

Hello & func()//返回值类型为引用型
{
	cout << "跳转到func()函数中!\n" << endl;
	Hello * p = new Hello(99);
	cout << "堆中对象a的地址：" << p << endl;
	return *p;

}
int main (void)
{
	Hello & r = func();//r与堆中对象地址相同
	cout << "堆中对象的副本的地址为:" << &r << endl;
	cout << r.get() << endl;

	Hello * p = &r;
	delete p;//delete不能对引用直接操作，所以用指针接收引用的地址然后释放

	cout << r.get() << endl;
	//但是这种方法解决了内存泄漏的问题，但是释放堆中对象之后，r成了一个存放空对象的引用，带来了另一个重大的问题而不是隐患了
	//若果不是提前注意知道这个问题的存在，在没有报错没有警告的情况下是很难察觉的
	return 0;
}
/*
	运行结果：
		跳转到func()函数中!

		调用构造函数,创建了一个对象...
		堆中对象a的地址：00386CA0
		堆中对象的副本的地址为:00386CA0
		99
		析构函数运行中...
		-572662307
		Press any key to continue



*/