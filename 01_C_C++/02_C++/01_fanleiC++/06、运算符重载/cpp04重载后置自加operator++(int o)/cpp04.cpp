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

	const num & operator++()//前自加：先加后用
	{
		++n;
		return *this;
	}
	const num operator++(int o)//后自加：先用后加，不可以按引用型返回，因为临时对象超出作用域会被析构掉
	{
		num TEMP(*this);//临时对象,传递原始对象（当前对象）
		++this->n;//原始对象成员n自加
		return TEMP;//返回的临时对象与原有对象自加前相同
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
	//NUM_ONE++;//三种方式结果相同但是机理不同，而且第三种会多次调用复制构造函数

	cout << "NUM_ONE:" << NUM_ONE.get() << endl;
	
	//num NUM_TWO = ++NUM_ONE;
	num NUM_TWO = NUM_ONE++;

	cout << "NUM_TWO:" << NUM_TWO.get() << endl;
	cout << "NUM_ONE:" << NUM_ONE.get() << endl;

	++NUM_ONE;
	cout << "NUM_ONE:" << NUM_ONE.get() << endl;
	cout << "NUM_TWO:" << NUM_TWO.get() << endl;
	return 0;
}
/*
num NUM_TWO = ++NUM_ONE;前自加运行结果：

构造函数执行中...
NUM_ONE:1
NUM_ONE:2
复制构造函数函数执行中...
NUM_TWO:3
NUM_ONE:3
NUM_ONE:4
NUM_TWO:3
析构函数执行中...
析构函数执行中...
Press any key to continue

num NUM_TWO = NUM_ONE++;后自加运行结果：
构造函数执行中...
NUM_ONE:1
NUM_ONE:2
复制构造函数函数执行中...
复制构造函数函数执行中...		
析构函数执行中...					//临时对象创建之后超出作用域直接被析构
NUM_TWO:2
NUM_ONE:3
NUM_ONE:4
NUM_TWO:2
析构函数执行中...
析构函数执行中...
Press any key to continue

*/