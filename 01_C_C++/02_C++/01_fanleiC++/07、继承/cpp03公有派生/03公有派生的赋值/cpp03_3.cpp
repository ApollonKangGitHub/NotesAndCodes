/*
	2016年8月22日11:27:14
*/
# include <iostream>
using namespace std;

class FATHER
{
public:
	int x;
};

class SON:public FATHER//公有派生
{
public:
	int y;
};

int main (void)
{
	FATHER Mike;
	SON Jack;

	Jack.x = 20;
	Jack.y = 30;//子类成员不初始化会有警告，父类不初始化不会有警告
	cout << "Jack.x:" << Jack.x << '\t' << "Jack.y:" << Jack.y << endl << "Mike.x:" << Mike.x << endl<< endl;//父类没有初始化时，输出乱码结果

	//Jack = Mike;
	Mike = Jack;//子类的对象可以赋给父类，但是父类的对象不能赋给子类
	cout << "Jack.x:" << Jack.x << '\t' << "Jack.y:" << Jack.y << endl << "Mike.x:" << Mike.x << endl<< endl;

	Mike.x = 40;
	cout << "Jack.x:" << Jack.x << '\t' << "Jack.y:" << Jack.y << endl << "Mike.x:" << Mike.x << endl<< endl;

	FATHER * p;
	p = &Jack;
	p->x = 45;
	cout << "通过父类指针p修改子类对象Jack的成员x，Jack.x=" << Jack.x << endl;//指针p为FATHER *类型，所以操作的只能是Jack对象的SON类继承的FATHER类的成员x，不能操作y
	
	FATHER &Tom = Jack;//父类的引用可以作为子类对象的别名
	Tom.x = 55;
	cout << "通过父类别名Tom修改子类对象Jack的成员x，Jack.x=" << Jack.x << endl;//同样，Tom为FATHER &类型，所以操作的只能是Jack对象的SON类继承的FATHER类的成员x，不能操作y

	SON & Danny = Jack;
	Danny.x = 77;
	Danny.y = 88;
	cout << "Danny.x == Jack.x = " << Jack.x << endl << "Danny.y == Jack.y = " << Danny.y << endl;

	return 0;
}