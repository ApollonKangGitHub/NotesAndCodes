# include<iostream>
using namespace std;
class A
{
public:
	A(int i, int j){x=i;y=j;}
	void set(int s1,int s2){x=s1;y=s2;}
	void print(){cout<<x<<endl;}
	void print()const{cout<<y<<endl;}
private:
	int x;
	int y;
};
int main (void)
{
	/*
		const成员函数只能被const对象调用；
		const修饰的函数体内，不能调用非const成员函数
		非const成员函数只能被非const对象调用；
		这种关系是一一对应的。
		且const对象成员变量不能修改

		const修饰的基类成员函数，可防止派生类覆盖函数恶意篡改数据成员值
	*/
	const A a(1,2);
	a.print();
	//a.set(3,4);
	A b(5,6);
	b.print();
	b.set(7,8);
	b.print();
	return 0;
}