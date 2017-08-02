# include <iostream>
using namespace std;

class num
{
public:
	num(){n = 1; cout << "构造函数执行中..." << endl;}//构造函数初始化
	~num(){cout << "析构函数执行中..." << endl;}
	void set(int x){n = x;}
	int get(){return n;}
	void num_add(){++n;}
private:
	int n;
};
int main (void)
{
	num NUM;
	cout << "NUM:" << NUM.get() << endl;
	//++NUM;//NUM为对象，要对其成员n自加，不能直接对其对象NUM进行自加操作
	NUM.num_add();//采用成员函数对成员变量进行自加，然后调用成员函数的方法解决对象不可自加的问题
	cout << "NUM:" << NUM.get() << endl;
	NUM.num_add();//但是这种方法看起来比较繁琐
	NUM.num_add();
	cout << "NUM:" << NUM.get() << endl;

	return 0;
}