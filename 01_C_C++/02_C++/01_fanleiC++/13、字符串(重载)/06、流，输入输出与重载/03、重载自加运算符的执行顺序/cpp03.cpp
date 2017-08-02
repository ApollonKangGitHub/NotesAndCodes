# include<iostream>
using namespace std;
class A
{
public:
	A(int x){rx=x;}
	friend ostream & operator<<(ostream & s,const A&c)//输出运算符重载
	{
		s<<c.rx;
		return s;
	}
	friend istream & operator>>(istream & s,A&c)//输入运算符重载
	{
		s>>c.rx;
		return s;
	}
	int operator++()//前置自加运算符重载
	{
		cout<<"执行++i:\n";
		rx++;
		return rx;
	}
	int operator++(int)//后置自加运算符函数重载，int型参数予以区别前置自加重载
	{
		cout<<"执行i++:\n";
		int i=rx;
		rx++;
		return i;
	}
private:
	int rx;
};

int main (void)
{
	A a(3),b(5);
	cout<<a<<b<<endl;

	cout<<++a<<a++<<endl;
	//VC++6.0中：先求参数值再压栈，求参数值为从右到左
	//先执行a++，再执行++a
	//(1)、a++：先将a=3压栈,再a=a+1=4;
	//(2)、++a：先a=a+1=5;在将5压栈
	//(3)、输出时为出栈，由于5在栈顶故先输出5，再输出3

	cout<<"请输入a和b的值，回车一次，结束依次输入："<<endl;
	cin>>a>>b;
	cout<<a<<b<<endl;
	return 0;
}