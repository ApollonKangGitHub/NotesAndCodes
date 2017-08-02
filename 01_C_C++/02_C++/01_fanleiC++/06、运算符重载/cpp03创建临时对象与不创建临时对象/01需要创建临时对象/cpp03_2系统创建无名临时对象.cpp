# include <iostream>
using namespace std;

class num
{
public:
	num(){n = 1; cout << "构造函数执行中..." << endl;}//构造函数初始化
	num(int i){n = i; cout << "带参数的构造函数执行中..." << endl;}
	~num(){cout << "析构函数执行中..." << endl;}

	void set(int x){n = x;}
	int get()const{return n;}
	void num_add(){++n;}
	num operator++()
	{
		++n;
		return num(n);//将n++赋给了新的对象的成员n,返回的是带参数的构造函数创建的临时对象。而这个临时对象没有名字
	}
private:
	int n;
};
int main (void)
{
	num NUM_ONE;
	cout << "NUM_ONE:" << NUM_ONE.get() << endl;
	//NUM_ONE.num_add();//不会创建临时对象
	++NUM_ONE;//会创建临时对象
	cout << "NUM_ONE:" << NUM_ONE.get() << endl;
	
	num NUM_TWO = ++NUM_ONE;
	cout << "NUM_TWO:" << NUM_TWO.get() << endl;
	cout << "NUM_ONE:" << NUM_ONE.get() << endl;

	++NUM_ONE;
	cout << "NUM_ONE:" << NUM_ONE.get() << endl;
	cout << "NUM_TWO:" << NUM_TWO.get() << endl;
	cout << "对NUM_ONE操作会改变NUM_ONE的值，但不会改变NUM_TWO的值" << endl;
	++NUM_ONE;
	cout << "NUM_ONE:" << NUM_ONE.get() << endl;
	cout << "NUM_TWO:" << NUM_TWO.get() << endl;
	cout << "对NUM_ONE操作会改变NUM_ONE的值，但不会改变NUM_TWO的值" << endl;
	++NUM_TWO;
	cout << "NUM_ONE:" << NUM_ONE.get() << endl;
	cout << "NUM_TWO:" << NUM_TWO.get() << endl;
	cout << "对NUM_TWO操作会改变NUM_TWO的值，但不会改变NUM_ONE的值" << endl;

	return 0;
}