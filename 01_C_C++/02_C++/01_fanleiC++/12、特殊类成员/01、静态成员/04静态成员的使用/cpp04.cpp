/*
	静态成员变量用于记录阿司匹林库存量的总价格
*/
# include<iostream>
using namespace std;

class aspl
{
public:
	aspl(float p){price=p;TotalPrice+=p;}
	~aspl(){TotalPrice=TotalPrice-price;}
	static float get(){return TotalPrice;}
private:
	float price;
	static float TotalPrice;
};
float aspl::TotalPrice=0;
int main (void)
{
	float f;
	cout<<"阿司匹林的库存量总价值为：";
	cout<<aspl::get()<<endl;
	int i = 0;
	aspl*p[5];
	for(i=0;i<5;i++)
	{
		cout<<"请输入第"<<i+1<<"次购进阿司匹林的单箱价格：";
		cin>>f;
		p[i]=new aspl(f);
		cout<<"阿司匹林的库存量总价值为：";
		cout<<aspl::get()<<endl;
	}

	cout<<"请输入卖出的阿司匹林的编号，编号即第几次购进：";
	cin>>i;
	delete p[i-1];
	cout<<"阿司匹林的库存量总价值为：";
	cout<<aspl::get()<<endl;

	return 0;
}
