#include<iostream>
using namespace std;

class human
{
public:
	//virtual void smart(){}
	virtual void smart()=0;//令虚函数等于0就成为了纯虚函数
	virtual void beautiful()=0;//纯虚函数
	//纯虚函数，不能进行任何操作，其子类继承该函数就必须中必须为该函数赋予新功能。若任何一个子类中没有该函数或者不为该函数赋予新的功能，就会报错。
	//因为继承了该纯虚函数，若不赋予新的功能，就不具有其子类的新的特征。便成为了一个抽象的对象
	virtual ~human(){cout<<"析构human"<<endl;}
	human(){cout<<"构造human"<<endl;}
};

/*
	human类仅仅起到了为派生类提供一个接口的作用，这个借口类的纯虚函数没有任何作用
	派生类将这些纯虚函数继承过来，然后为它们赋予新的不同的功能。
	注意抽象类不能创建对象，虽然不能定义抽象类的对象，但是可以定义抽象类的指针。该指针在编译时可以动态的指向子类的对象
*/
class father:virtual public human 
{
public:
	father(){cout<<"构造father"<<endl;}
	virtual void smart(){cout << "父亲很聪明\n";}
	virtual void beautiful(){cout << "父亲并不帅\n";}
	virtual ~father(){cout << "析构father"<<endl;}
};
class mother:virtual public human
{
public:
	mother(){cout<<"构造mother"<<endl;}
	virtual void beautiful(){cout << "母亲很漂亮\n";}
	virtual void smart(){cout << "母亲并不聪明\n";}
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
			p->beautiful();
			delete p;
			break;
		case 2:p=new son;
			p->beautiful();//p指向son故调用son类的成员beautiful
			p->smart();//p指向son故调用son类的成员smart
			delete p;
			break;
		case 3:p=new mother;
			p->beautiful();//p指向mother故调用mother类的成员beautiful
			p->smart();
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