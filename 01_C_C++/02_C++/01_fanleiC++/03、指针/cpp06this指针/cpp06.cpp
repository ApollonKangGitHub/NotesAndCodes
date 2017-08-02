# include <iostream>
using namespace std;

class Human
{
public:
	int get_i()const{return i;}
	void set_i (int x){i = x;cout << "this指针保存的内存地址为：\t" << this << endl;}
//	int get_j()const{return j;}
//	void set_j (int x){j = x;cout << "this指针保存的内存地址为：\t" << this << endl;}
private:
	int i;
//	int j;
};
int main (void)
{
	Human a;
	a.set_i(9);
//	a.set_j(90);
	cout << "对象a的内存地址为：\t\t" << &a << endl;
	cout << a.get_i() <<endl;
//	cout << a.get_j() <<endl;

	Human b;
	b.set_i(99);
//	b.set_j(909);
	cout << "对象b的内存地址为：\t\t" << &b <<endl;
	cout << b.get_i() <<endl;
//	cout << b.get_j() <<endl;

	cout << sizeof(a) << endl;
	cout << sizeof(b) << endl;
	
	return 0;
}
/*

void set_i (int x){i = x;cout << "this指针保存的内存地址为：\t" << this << endl;}
原型语句为:
void set (int x){this->i = x;cout << "this指针保存的内存地址为：\t" << this << endl;}
this可以省略不谢，编译器自动会加上this


this变量记录每个对象的地址，然后通过间接访问运算符->，访问该对象的成员
this记录的是对象的地址，某对象中有多个变量。对象地址首字节即与第一个变量的地址首字节相同

*/