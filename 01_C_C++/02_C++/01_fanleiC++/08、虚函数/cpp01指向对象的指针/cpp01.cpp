/*
	2016年8月25日12:28:59

	father *p = new son;//right
	son *q = new son;//right
	son *r = new father;//error

	注意第三条语句无法实现，因为子类继承父类的所有特点，所以可以通过父类指针操作子类对象内存空间
	（即父类指针操作的成员父类中都有，子类中继承后自然也都有（子类的对象能够包含父类指针的操作权限））
	而子类中的成员父类中不一定有，那么子类的指针操作权限超出父类的对象的包含量。父类对象不能包容子类指针，所以不能实现
*/
# include <iostream>
using namespace std;

class father
{
public:
	father():age(54){cout << "调用父类的构造函数，并初始化age的值为：" << age << endl;}
	~father(){cout << "调用父类的析构函数..." << endl;}
	void jump() const{cout<< "父亲可以跳五个台阶!" << endl;}
	void run()const{cout<< "父亲可以跑万米!" << endl;}
protected:
	int age;
};

class son : public father
{
public:
	son(){cout << "调用子类的构造函数..." << endl;}
	~son(){cout << "调用子类的析构函数..." << endl;}
	void jump() const{cout<< "儿子可以跳十个个台阶!" << endl;}
	void run()const{cout<< "儿子可以跑十万米!" << endl;}
	void math(){cout << "儿子是数学老师!" << endl;}
};

int main (void)
{
	father *p = new son;
	//创建一个子类的对象（所拥有的空间），先调用父类的构造函数，再调用子类的构造函数。
	//指针p类型为father *，所以对指针p的操作是对子类继承的父类成员的操作，其特征属性均是父类的
//	son *q = new son;
//	son *r = new father;
	p->jump();
	p->run();

	delete p;//p是父类指针，释放的自然是父类内存（虽然分配是按子类分的，但是那仅仅是内存大小，不代表使用权限。谁有操作权限，该内存就属于谁）
	return 0;
}