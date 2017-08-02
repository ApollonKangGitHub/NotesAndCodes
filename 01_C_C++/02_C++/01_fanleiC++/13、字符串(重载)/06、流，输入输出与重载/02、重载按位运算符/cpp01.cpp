# include<iostream>
using namespace std;
class A
{
public:
	A(int x,int y){rx=x; ry=y;}
		//ostream输出流,重载输出运算符（并非按位左移运算符）
		//返回值类型为ostream&类型是为了可以连续进行cout<<a<<b;
		//如果不返回s，返回值类型也不用为ostream&，而为void，则只能cout<<a;cout<<b;分开输出
		//ostream类没有共有的复制构造函数，所以ostream的对象cout无法调用复制构造函数
		//故而不能按值传递参数（按值传参会调用复制构造函数创建副本），必须按引用传递
	//friend表示友元函数。由于ostream类的对象s无法访问与其无关的类的私有成员，只有将该函数定义为友元函数才可以访问
	friend ostream & operator<<(ostream & s,const A&c)
	{
		s<<c.rx;//cout为参数s,对象a(b)为参数c
		s<<c.ry;
		return s;
	}
private:
	int rx;
	int ry;
};

int main (void)
{
	A a(3,4),b(5,6);
	cout<<a<<b<<endl;//<<运算符在重载以前不能对对象进行操作

	/*按位左移运算符*/
	int num = 52;
	int x = num<<2;//按位（二进制）左移2位，即二进制的右边（后边）加上两个0，再按十进制输出
	cout<<x<<endl;
	return 0;
}