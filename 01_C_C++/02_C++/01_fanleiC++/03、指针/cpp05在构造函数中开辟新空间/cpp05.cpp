/*
	2016年8月6日14:39:48
*/
# include <iostream>
using namespace std;

class Human
{
public:
	Human(){cout << "构造函数执行中..." << endl;i = new int(99);}//构造函数中开辟新的空间
	~Human(){cout << "析构函数执行中... "<< endl;delete i;}
	//因为delete p时会删除存储指针i的空间，所以析构函数中指针i指向的空间也必须释放
	//否则i的自身空间释放后会导致内存泄漏
	void get(int x){*i = x;}
	int return_value()const{return *i;}
private:
	int * i;
};
int main (void)
{
	Human Mike;
	cout << Mike.return_value() << endl;
	Mike.get(120);
	cout << Mike.return_value() << endl;

	Human * p = new Human;
	cout << p->return_value() << endl;
	p->get(102);
	cout << p->return_value() << endl;

	delete p;
	return 0;
}
