# include <iostream>
using namespace std;

class num
{
public:
	num(){n = new int; *n = 1; cout << "构造函数执行中..." << endl;}//构造函数初始化
	//num(int i){n = new int; *n = i; cout << "带参数的构造函数执行中..." << endl;}//带参数的构造函数超出作用域之后便会被立刻析构
	//num(const num&s){n = new int; *n = s.get(); cout << "复制构造函数函数执行中..." << endl;}//this->n = s.n;
	~num(){delete n; n = NULL; cout << "析构函数执行中..." << endl;}
	int get()const{return *n;}
	void set(int x){*n = x;}

	//const num &operator=(const num & r)//按引用返回不调用复制构造函数
	num operator=(const num & r)
	{
		if(this == &r)
		{
			return *this;
		}
		cout << "operator=函数正在调用..." << endl;
		*n = r.get();
		return *this;
	}
private:
	int *n;
};
int main (void)
{
	num one, two;
	one.set(14);
	two.set(27);
	cout << "one:" << one.get() << endl;
	cout << "two:" << two.get() << endl;

	//num three = one = two;
	num three;
	three = one = two;
	//思考1：定义和赋值为两句和定义赋值为一句，为什么都是程序出错而输出结果不同呢？？？
	//思考2：改程序为什么会出错？为什么程序cpp06_4 不会出错？？
	//思考3：为什么将复制构造函数的注释符“//”去掉之后问题就解决了呢？？？
	//思考4：为什么不去掉复制构造函数的注释符“//”，
	//而将num operator=(const num&r)改为const num &operator=(const num&r)问题也可以解决呢（和const无关，主要是引用的作用）？？
	cout << "one:" << one.get() << endl;
	cout << "two:" << two.get() << endl;
	cout << "three:" << three.get() << endl;

	return 0;
}
