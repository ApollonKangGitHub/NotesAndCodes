/*
	观察构造与析构执行顺序，体会多重继承

	pf=new son，pf指针只能访问子类从father中继承的成员，不能访问从mother中继的承成员
	pm=new son，pm指针只能访问子类从mother中继承的成员，不能访问从father中继承的成员
	
	虽然多重继承比单一继承有许多优点，但是由于虚基类的定义很复杂，使用也容易产生多义性，
	所以当单一继承能做到的事，尽量不要使用多重继承。
*/
#include<iostream>
using namespace std;
class father
{
public:
	father(){cout<<"构造father"<<endl;}
	void smart(){cout << "父亲很聪明\n";}
	//virtual void beautiful(){}//该函数在父类中没有任何作用，子类本应从母类中继承，但是没有母类，父类为了给子类提供一个接口，就加上了没有任何实际功能的虚函数
	virtual ~father(){cout << "析构father"<<endl;}
};
class mother
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
	~son(){cout << "析构son"<<endl;}
};

int main (void)
{
	father * pf;
	mother * pm;
	int choice = 0;
	while(choice<99)
	{
		bool quit=false;
		cout<<"(0)退出\t(1)父亲\t(2)儿子:"<<endl;
		cin>>choice;
		switch(choice)
		{
		case 0:quit=true;
			break;
		case 1:pf=new father;
			pf->smart();
			delete pf;
			break;
		case 2:pm=new son;
			pm->beautiful();
			delete pm;
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