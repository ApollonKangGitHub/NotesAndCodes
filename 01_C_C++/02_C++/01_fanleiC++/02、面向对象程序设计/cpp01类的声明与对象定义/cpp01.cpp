# include <iostream>
using namespace std;

/*
***  class为类关键字，类似于struct
***  public为公有成员
***  private为私有成员
***  私有成员不能通过对象名直接访问，必须通过对象名调用公有成员->公有成员调用私有成员来实现
*/
class Human
{
public:
	void get_stature(){cout<<stature<<endl;}//直接定义
	void get_weight(){cout<<weight<<endl;}
	void set_stature(int x);//接口函数
	void set_weight(int x);//接口函数
private:
	int weight;
	int stature;
};
/*
***类中成员函数的定义可以直接在类成员函数后直接定义，
***也可在类中声明，而在类外通过类名提取函数名全局定义
*/
void Human::set_stature(int x)//通过类名提取成员函数名而后定义
{
	stature = x;
}

void Human::set_weight(int x)
{
	weight = x;
}

int main (void)
{
	Human Mike;
	int weight;
	int stature;

	cout<<"请输入Mike身高体重：\n";
	cin>>stature>>weight;

	cout<<"Mike的身高为（cm）：";
	Mike.set_stature(stature);//对象名调用公有成员（主函数中）->公有成员调用私有成员（类中自行完成）
	Mike.get_stature();//对象名直接调用公有成员
	cout<<"Mike的体重为（kg）：";
	Mike.set_weight(weight);
	Mike.get_weight();

	return 0;
}
/*
	类是某类事物的数据和方法的集合：
	类是由若干个变量和相关函数所组成，而对象可以拥有这些函数。对象通过类名来定义，类通过关键字class来声明。
	类的共同数据叫做成员变量（数据成员），类的共同方法叫做成员函数（方法成员），成员函数和成员变量统称为该类的成员
	对象拥有类的公有成员直接调用权限，并且可以封装这些成员
*/