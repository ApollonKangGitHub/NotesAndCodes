/*
	类名 &变量名2 = 变量名1;
	因为类是一种类型，并非变量，没有具体的地址，所以不能为类取别名。
*/
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
	/*	栈中引用型变量	*/
	Human Mike;
	Human &Miker = Mike;
	cout << &Mike << '\t' << &Miker << endl;
	
	cout << Mike.return_value() << '\t' << Miker.return_value() << endl;
	Mike.get(122);
	cout << Mike.return_value() << '\t' << Miker.return_value() << endl;
	Miker.get(124);
	cout << Mike.return_value() << '\t' << Miker.return_value() << endl;
	
	/*	堆中引用型变量	*/
	Human * p = new Human;//堆中为Human类分配了四个字节的内存，此时调用了构造函数，并将首字节返回给指针p，只能通过指针p对堆内存进行操作
	Human * &pr = p;//pr和p皆为指针变量，而pr又是挂在p地址上的引用型变量，所以pr与p指向同一个对象
	cout << pr << '\t' << p << endl;//输出pr和p的值，即pr和p的指向地址

	cout << p->return_value() << '\t' << pr->return_value() << endl;//通过别名指针操作
	p->get(102);
	cout << p->return_value() << '\t' << pr->return_value() << endl;
	pr->get(104);
	cout << p->return_value() << '\t' << pr->return_value() << endl;
	
	delete p;//没有释放类的堆内存时，析构函数不执行，而delete p以后就调用了析构函数
	p = 0;
	//delete pr;//不需要该句，因为p和pr指向同一块空间，释放一次即可，只需将pr指向0地址即可
	//pr = 0;//该句也不需要，因为p为0时;引用型变量pr也随之为0.

	return 0;
}
