/*
	2016年8月20日17:33:07
	若对象的拷贝成员n为指针，delete one必定会使three的n成为迷途指针带来安全隐患
	所以必须进行深层复制 
*/
# include <iostream>
using namespace std;

class num
{
public:
	num(){n = new int; *n = 1; cout << "构造函数执行中..." << endl;}//构造函数初始化
	num(int i){n = new int; *n = i; cout << "带参数的构造函数执行中..." << endl;}//带参数的构造函数超出作用域之后便会被立刻析构
	num(const num&s){n = new int; *n = s.get(); cout << "复制构造函数函数执行中..." << endl;}//this->n = s.n;
	~num(){delete n; n = NULL; cout << "析构函数执行中..." << endl;}//无论是临时对象还是其它对象，都有一块独立的堆中空间。删除任何一个对象不会影响其他的对象
	int get()const{return *n;}
	void set(int x){*n = x;}

	const num equal(const num &r){*n = r.get(); return *this;}//返回值可以不要
private:
	int *n;
};
int main (void)
{
	num one(49);
	num two(100);
	cout << "one:" << one.get() << endl;
	cout << "two:" << two.get() << endl;
	num three = one.equal(two);//切记不可分开写，因为返回值为const num类型

	cout << "one:" << one.get() << endl;
	cout << "two:" << two.get() << endl;
	cout << "three:" << three.get() << endl;
	return 0;
}
