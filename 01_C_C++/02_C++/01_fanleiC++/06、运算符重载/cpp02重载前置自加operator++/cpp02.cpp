/*
	新的关键字：operator重载操作符；经常与运算符连用并带一个()，表示一个函数
	eg：operator++()便是一个函数

	C++中运算符的使用实质是函数的调用：
	如：
	1+2;  =>  会调用类似operator+(int,int)函数
	4.5+5.6;  =>  会调用类似operator+(double,double)函数

	上面两个函数名相同但参数列表不同，不实现运算符的重载，也体现了函数得重载
*/
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
	void operator++(){++n;}
private:
	int n;
};
int main (void)
{
	num NUM;
	cout << "NUM:" << NUM.get() << endl;
	NUM.num_add();//调用函数自加
	cout << "NUM:" << NUM.get() << endl;
	++NUM;//运算符重载自加，会自动调用i.operator++()函数
	cout << "NUM:" << NUM.get() << endl;

	return 0;
}