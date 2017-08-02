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

	const num equal(const num & r){n = r.get(); return *this;}//返回值可以不要
private:
	int n;
};
int main (void)
{
	num one(49);
	num two(100);
	num three;

	cout << "one:" << one.get() << endl;
	cout << "two:" << two.get() << endl;
	three = one.equal(two);//将two赋给one，调用复制构造函数将one复制给three
	cout << "one:" << one.get() << endl;
	cout << "two:" << two.get() << endl;
	cout << "three:" << three.get() << endl;
	return 0;
}
