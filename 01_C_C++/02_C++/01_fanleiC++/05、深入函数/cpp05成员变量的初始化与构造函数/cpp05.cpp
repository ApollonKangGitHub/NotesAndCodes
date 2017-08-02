//构造顺序与析构顺序
# include <iostream>
using namespace std;

class demo
{
public:
	demo () {x= 0; cout << "demo默认的构造函数运行中..." << x << endl;}
	demo (int i) {x = i; cout << "demo的带一个参数的构造函数运行中..." << x << endl;}
	~demo(){cout << "demo的默认析构函数运行中..." << x << endl;}
	int get(){return x;}
	void set(int i){x =i;}
private:
	int x;
};
class rectangle
{
public:

	rectangle(){x = 1000; cout << "rectangle的默认构造函数运行中..." << x << endl;}
	rectangle(int i, int j, int k):x(i),width(j),length(k)//初始化,按照成员列表的顺序构造，按照先构造后析构的原则析构
	{
		cout << "rectangle的带三个参数的构造函数运行中..." << "长方形的面积为："  << length.get() * width.get() << endl;
	}
	~rectangle(){cout << "rectangle的默认析构函数运行中..." << x << endl;}
	int area(){return length.get() * width.get();}
private:
	int x;
	demo length;
	demo width;//一个类中存在另一个类的对象，叫“包容”
	
};
int main (void)
{
	rectangle a(100,200,300);
	return 0;
}