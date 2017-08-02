/*
	2016年8月22日16:20:06
	两义性：
	即多重继承时，一个子类的不同的基类含有成员名相同的成员，而子类对象调用时，那没有加以区分。
	编译器不知该调用哪个基类中的成员，导致出错的现象

	解决办法：
	在调用基类成员时，在成员名前加上类名与作用域操作符即（对象名 类名::成员名）

	总结：
	编译器无法区分的要加作用域操作符，编译器可以区分的没必要加作用域操作符
*/
# include <iostream>
using namespace std;
class ONE
{
public:
	void hello(){cout << "基类ONE的hello函数" << endl;}
	void print(){cout << "基类ONE的hello函数" << endl;}
};

class TWO
{
public:
	void hello(){cout << "基类TWO的hello函数" << endl;}
	void print(){cout << "基类TWO的print函数" << endl;}
};

class THREE:public ONE,public TWO
{
public:
	void print(){cout << "子类THREE的hello函数" << endl;}
};

int main (void)
{
	THREE Mike;
	//Mike.hello();含混不清，因为两个基类中都有hello()函数
	//Mike.THREE::hello();//还是错的因为Mike::hello()还会产生两义性
	
	Mike.ONE::hello();
	Mike.TWO::hello();
	Mike.ONE::print();
	Mike.TWO::print();
	Mike.print();
	//不会产生两义性问题，因为子类中有print()函数，编译器直接调用子类的print()函数，不会访问基类也不会牵扯基类的两义性问题

	ONE Danny;
	Danny.ONE::hello();//没有必要加::
	Danny.hello();
	
	return 0;
}