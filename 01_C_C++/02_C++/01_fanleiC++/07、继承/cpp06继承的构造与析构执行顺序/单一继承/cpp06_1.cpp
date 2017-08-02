/*
	2016年8月22日13:07:55
	运行结果：
		grandfather类构造函数执行中...
		构造基类a的构造函数正在执行中...        2
		构造子类b的构造函数正在执行中...        7
		析构子类b的析构函数正在执行中...        7
		析构基类a的析构函数正在执行中...        2
		grandfather类析构函数执行中...
		Press any key to continue

	构造顺序与析构顺序：
	构造：从最高的基类（父类）开始构造
	析构：从最低的子类开始析构

	如：A为基类，B为A的子类，C为B的子类
	那么构造函数与析构函数执行顺序为：
		构造函数A->构造函数B->构造函数C->析构函数C->析构函数B->析构函数A
*/
# include <iostream>
using namespace std;

class grandfather
{
public:
	grandfather(){cout<< "grandfather类构造函数执行中..." << endl;}
	~grandfather(){cout<< "grandfather类析构函数执行中..." << endl;}
};

class father:public grandfather
{
private:
	int a;
public:
	father(int i){a = i;cout << "构造基类a的构造函数正在执行中...\t" << a << endl;}
	~father(){cout << "析构基类a的析构函数正在执行中...\t" << a << endl;}
};
class son:public father
{
private:
	int b;
public:
	son(int i, int j);
	~son(){cout << "析构子类b的析构函数正在执行中...\t" << b << endl;}
};

//由于子类将基类成员继承过来，调用子类构造函数son()函数，会先访问基类构造函数，所以基类构造函数father()要进行初始化:father(参数)
son::son(int i, int j):father(i)
{
	b = j;
	cout << "构造子类b的构造函数正在执行中...\t" << b << endl;
}

int main (void)
{
	son Mike(2,7);//2用来初始化father类的数据成员a的值，7用来初始化son类数据成员b
	
	return 0;
}