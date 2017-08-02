# include <iostream>
using namespace std;

class Human
{
public:
	Human(){cout << "构造函数执行中..." << endl;i = 99;}//构造函数
	~Human(){cout << "析构函数执行中... "<< endl;}
	void get(int x){i = x;}
	int return_value()const{return i;}
private:
	int i;
};
int main (void)
{
	Human Mike;
	cout << Mike.return_value() << endl;
	Mike.get(120);
	cout << Mike.return_value() << endl;

	Human * p = new Human;//堆中为Human类分配了四个字节的内存，此时调用了构造函数，并将首字节返回给指针p，只能通过指针p对堆内存进行操作
	cout << p->return_value() << endl;//没有名字的对象，只能通过指针进行操作
	p->get(102);
	cout << p->return_value() << endl;

	delete p;//没有释放类的堆内存时，析构函数不执行，而delete p以后就调用了析构函数
	p = 0;

	return 0;
}

/*
	结果：
		构造函数执行中...
		99
		120
		构造函数执行中...
		99
		102
		析构函数执行中...        //程序运行完毕自动执行
		析构函数执行中...        //运行delete p时才执行
		Press any key to continue

*/

/*
	总结：
	析构函数就是用来释放为对象分配的内存的
	当对象在堆中创建，只有执行delete时才会调用析构函数（程序员自行控制）
	而对象在栈中创建时，只要函数执行完毕系统即会自动执行析构函数
	
*/