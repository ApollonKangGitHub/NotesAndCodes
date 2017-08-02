/*
	cC++中的构造函数与析构函数
*/
# include <iostream>
using namespace std;

class Space
{
public:
	Space(int x,int y){length = x; wedth = y;}//构造函数1
	int return_area(){return length * wedth;}
	Space(){cout << "构造函数执行中..." << endl;}//构造函数2，构造函数可以有多个

	~Space(){cout << "析构函数成功..." << endl;}//析构函数只能有一个
private:
	int length;
	int wedth;
};

int main (void)
{
	Space a(3,4);//类名定义对象a时通过构造函数初始化
	cout << "长方形面积为：" << a.return_area() << endl;
	Space b;

	return 0;

}

/*
	构造函数特点：
	>>构造函数名和类名相同，构造函数无返回值，即函数名之前无返回值类型（void也不行）
	>>构造函函数有形参时，main中定义对象时，直接在对象名之后加上参数即为初始化
	>>一个类中构造函数可以有多个
	>>若没有定义构造函数，则系统为类默认一个构造函数，若定义了，系统默认的自动屏蔽

	析构函数特点
	>>析构函数与构造函数功能相反，为释放构造函数为类分配的一系列内存
	>>析构函数名和类名相同，只需在函数名之前加一个~，表示构造函数的对立，析构函数无返回值且无参数列表
	>>析构函数在一个类中只能有一个
*/



