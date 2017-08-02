
# include <iostream>
using namespace std;

class num
{
public:
	num(){n = 1; cout << "构造函数执行中..." << endl;}//构造函数初始化
	~num(){cout << "析构函数执行中..." << endl;}

	//num(num&){cout << "复制构造函数执行中..." << endl;}
	/*
		注意：
		如果写默认复制构造函数，operator+函数返回是按值返回，为浅层拷贝。
		而浅层拷贝在临时对象析构后，复制的值存在的空间（即被拷贝对象的副本空间）会被释放
		最终输出的值为随机值
	*/

	void set(int x){n = x;}
	int get(){return n;}
	void num_add(){++n;}
	num operator++()
	{
		++n;
		num TEMP;//临时对象
		TEMP.set(n);
		return TEMP;
	}
private:
	int n;
};
int main (void)
{
	num NUM_ONE;
	cout << "NUM_ONE:" << NUM_ONE.get() << endl;
	NUM_ONE.num_add();
	//++NUM_ONE;
	cout << "NUM_ONE:" << NUM_ONE.get() << endl;	

	num NUM_TWO = ++NUM_ONE;
	//如果void operator++(){++n;}不变。num NUM_TWO = ++NUM_ONE;那么这种写法是错误的。
	//因为++NUM_ONE调用operator++函数返回值为void类型与NUM_TWO类型不匹配
	//要实现将一个对象自加后赋给一个新的对象，必须创建一个临时对象,即现有的operator++()的写法
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