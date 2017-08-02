# include <iostream>
using namespace std;
class A
{
public:
	void Set(int x, int y)
	{
		a=x;
		b=y;
	}
	void Show()
	{
		cout<<"a:"<<a<<'\t'<<"b:"<<b<<endl;
	}
private:
	int a;
	int b;
};

void(A::*p)(int, int);//类的成员函数的声明

int main (void)
{
	int x=2,y=3;
	A a;
	p=&A::Set;//p保存了对象A的set函数的地址（p==&set）
	(a.*p)(x,y);//a.*P则表示对象a调用*p函数，即调用set函数（*p==set）
	a.Show();
	return 0;
}
