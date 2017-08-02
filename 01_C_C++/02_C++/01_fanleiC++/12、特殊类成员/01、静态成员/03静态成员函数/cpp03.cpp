# include <iostream>
using namespace std;

class A
{
public:
	void static show_n(){cout<<A::n;n++;}//n为静态成员变量，访问n必须在访问函数前加static
	void show_m(){cout<<m;m++;}//m为非静态成员变量，所以其访问函数前不能加static
	void set_m(int M){m=M;}
private:
	static int n;
	int m;
};
int A::n = 0;
int main (void)
{
	for(int i=0;i<5;i++)
	{
		A::show_n();//可以通过类来访问静态成员函数
		cout<<'\t';
	}
	cout<<endl;
	A a;
	a.set_m(0);
	for(i=0;i<5;i++)
	{
		a.show_n();//也可以通过对象来访问静态成员函数
		cout<<'\t';
	}
	cout<<endl;
	for(i=0;i<5;i++)
	{
		a.show_m();
		cout<<'\t';
	}
	cout<<endl;
	return 0;
}