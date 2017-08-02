# include <iostream>
using namespace std;

class num
{
public:
	num(){n = 1; cout << "构造函数执行中..." << endl;}//构造函数初始化
	num(int i){n = i; cout << "带参数的构造函数执行中..." << endl;}//带参数的构造函数超出作用域之后便会被立刻析构
	~num(){cout << "析构函数执行中..." << endl;}
	num(const num&s){n = s.n; cout << "复制构造函数函数执行中..." << endl;}//this->n = s.n;

	void set(int x){n = x;}
	int get()const{return n;}

	//将this的n和r的n相加，作为构造函数num的参数。减法与加法大同小异
	num num_add(const num&r){return num(n+r.get());}//人为自行调用函数的方法，返回相加后的对象
	const num operator+(const num&r){return num(n+r.get());}//运算符重载的方法，是系统自行调用函数的方法
private:
	int n;
};
int main (void)
{
	num one(12), two(20), three;//one对象和two对象初始化

	//three = one.num_add(two);
	//three = two.num_add(one);//两种写法是一样的
	three = one + two;//自动调用operator+()函数，一个对象作为this指针所指向的对象，另一个则作为operator+的参数

	cout << "one:" << one.get() << endl;
	cout << "two:" << two.get() << endl;
	cout << "three:" << three.get() << endl;

	return 0;
}
