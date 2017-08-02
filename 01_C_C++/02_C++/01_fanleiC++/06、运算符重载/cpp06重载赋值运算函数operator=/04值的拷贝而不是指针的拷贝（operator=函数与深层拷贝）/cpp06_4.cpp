# include <iostream>
using namespace std;

class num
{
public:
	num(){n = new int; *n = 1; cout << "构造函数执行中..." << endl;}//构造函数初始化
	num(int i){n = new int; *n = i; cout << "带参数的构造函数执行中..." << endl;}//带参数的构造函数超出作用域之后便会被立刻析构
	num(const num&s){n = new int; *n = s.get(); cout << "复制构造函数函数执行中..." << endl;}//this->n = s.n;
	~num(){delete n; n = NULL; cout << "析构函数执行中..." << endl;}
	int get()const{return *n;}
	void set(int x){*n = x;}

	operator=(const num&r)
	{
		cout << "operator=函数正在调用..." << endl;
		*n = r.get();
	}
private:
	int *n;
};
int main (void)
{
	num one(49);
	num two(100);
	cout << "one:" << one.get() << endl;
	cout << "two:" << two.get() << endl;
	num three = one = two;

	cout << "one:" << one.get() << endl;
	cout << "two:" << two.get() << endl;
	cout << "three:" << three.get() << endl;

	return 0;
}
