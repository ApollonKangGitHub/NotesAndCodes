/*
	2016年8月22日17:09:07
	一个子类由多个基类派生而来，而这多个基类又是一个共同的基类派生而来
	那么子类访问这个共同的基类的成员时就会产生两义性
*/
# include <iostream>
using namespace std;
class Human
{
public:
	void stand(){cout << "人类能够直立行走" << endl;}
};

class Father:public Human
{
};
class Mother:public Human
{
};

class Son:public Father,public Mother
{
};

int main (void)
{
	Son Tom;
	//Tom.stand();
	//因为子类继承了父类和母类的特性，而父类和母类都继承了人类的stand特性，通俗点即Father类与Mother类中都有stand
	//Son类的对象在调用stand时，不知道是调用父类继承的人类stand特性，还是母类继承的人类stand特性从而产生两义性
	Tom.Mother::stand();
	Tom.Father::stand();//加上作用域操作符即可解决

	return 0;
}