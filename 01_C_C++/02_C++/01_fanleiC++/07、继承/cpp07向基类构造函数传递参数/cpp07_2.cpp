/*
	2016年8月22日15:39:21
	这种参数传递方法与上一中方法的唯一区别是：
	数据在子类构造函数参数列表后面直接对基类构造函数初始化，删除子类构造函数中对基类初始化的代码
	如此便不会调用基类的不带参数的构造函数，而是调用带参数的基类构造函数直接初始化基类成员
*/
# include <iostream>
# include <string>
using namespace std;

class father
{
protected:
	string name;
	int tall;
public:
	father(string a,int i);
	father(){cout << "构造基类,构造函数执行中..." << endl;}
	void print_father(){cout << name << "身高为：" << tall << endl;}
	~father(){cout << "释放基类对象,析构函数执行中..." << endl;}
};

father::father(string a,int i)
{
	cout << "进入基类构造函数" << endl;
	name = a;
	tall = i;
	print_father();
	cout << "离开基类构造函数" << endl;
}

class son:public father
{
private:
	int weight;
public:
	son(string a,int i,int j);
	void print_son();
	~son(){cout << "释放子类对象,析构函数执行中..." << endl;}
};

son::son(string a,int i,int j):father(a,i)//直接传参给基类构造函数
{
	cout<<"进入子类的构造函数"<<endl;
	//name = a;
	//tall = i;
	weight = j;
	cout << "离开子类构造函数" << endl;
}
void son::print_son()
{
	father::print_father();
	cout << "体重:" << weight << endl;
}
int main (void)
{
	son Mike("Mike",175,65);
	Mike.print_son();
	cout << "程序结束" << endl;
	return 0;
}