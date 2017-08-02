/*
	2016年8月22日15:04:48
	这种方法，直接在子类构造函数中给基类初始化，只调用了默认的（不带参数的）基类构造函数没有进入带参数的基类构造函数。
	显得基类带参构造函数的多余
	和子类构造函数的冗余
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

son::son(string a,int i,int j)
{
	cout<<"进入子类的构造函数"<<endl;
	name = a;
	tall = i;
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