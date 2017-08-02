#include<iostream>
using namespace std;
//构造一个抽象类human，其成员均为虚函数，而虚函数具有多态性，使得该抽象类的指针，根据其所指向的对象类型所属类，来判断该调用哪个函数。
//这个抽象类并非真正的抽象类，而是一个虚拟的抽象类。它的虚函数依然具有功能，那就是什么事都不做。而真正的抽象类至少有一个什么功能也不具备的成员函数
//它唯一的作用就是让子类来继承
class human
{
public:
	virtual void smart(){}
	virtual void beautiful(){}
	virtual ~human(){cout<<"析构human"<<endl;}
	human(){cout<<"构造human"<<endl;}
};
class father:virtual public human 
{
public:
	father(){cout<<"构造father"<<endl;}
	virtual void smart(){cout << "父亲很聪明\n";}
	virtual ~father(){cout << "析构father"<<endl;}
};
class mother:virtual public human
{
public:
	mother(){cout<<"构造mother"<<endl;}
	virtual void beautiful(){cout << "母亲很漂亮\n";}
	virtual ~mother(){cout<<"析构mother"<<endl;}
};
class son:public father,public mother
{
public:
	son(){cout<<"构造son"<<endl;}
	virtual void beautiful(){cout << "儿子也很帅\n";}
	virtual void smart(){cout << "儿子也很聪明\n";}
	virtual ~son(){cout << "析构son"<<endl;}
};

int main (void)
{
	human *p;
	int choice = 0;
	while(choice<99)
	{
		bool quit=false;
		cout<<"(0)退出\t(1)父亲\t(2)儿子\t(3)母亲:"<<endl;
		cin>>choice;
		switch(choice)
		{
		case 0:quit=true;
			break;
		case 1:p=new father;
			p->smart();//p指向fatherr故调用father类的成员smart
			delete p;
			break;
		case 2:p=new son;
			p->beautiful();//p指向son故调用son类的成员beautiful
			p->smart();//p指向son故调用son类的成员smart
			delete p;
			break;
		case 3:p=new mother;
			p->beautiful();//p指向mother故调用mother类的成员beautiful
			delete p;
			break;
		default:cout<<"请输入从0到2之间的数字:";
			break;
		}
		if(quit)
		{
			break;
		}
	}
	cout<<"程序结束！"<<endl;
	return 0;
}