# include <iostream>
using namespace std;

class num
{
public:
	num(){n = 1; cout << "构造函数执行中..." << endl;}//构造函数初始化
	num(int i){n = i; cout << "带参数的构造函数执行中..." << endl;}
	~num(){cout << "析构函数执行中..." << endl;}
	num(const num&s){n = s.n; cout << "复制构造函数函数执行中..." << endl;}//this->n = s.n;

	void set(int x){n = x;}
	int get()const{return n;}
	void num_add(){++n;}
	const num & operator++()//不想创建副本则按别名返回
	{
		++n;
		return *this;
	}
private:
	int n;
};
int main (void)
{
	num NUM_ONE;
	cout << "NUM_ONE:" << NUM_ONE.get() << endl;
	//NUM_ONE.num_add();//不会创建临时对象
	++NUM_ONE;//由于this指针接收原有对象自加后的值，也不会创建临时对象
	cout << "NUM_ONE:" << NUM_ONE.get() << endl;
	
	num NUM_TWO = ++NUM_ONE;//由于返回值为const所以不能++NUM_ONE之后再自加，即++++NUM_ONE
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