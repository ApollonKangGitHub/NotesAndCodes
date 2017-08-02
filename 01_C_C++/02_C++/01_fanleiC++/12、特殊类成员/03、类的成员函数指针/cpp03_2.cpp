# include <iostream>
using namespace std;
class Human
{
public:
	virtual void run()=0;
	virtual void eat()=0;
};
class Mother:public Human
{
public:
	void run(){cout<<"母亲跑百米需要18秒"<<endl;}
	void eat(){cout<<"母亲喜欢吃零食"<<endl;}
};
class Father:public Human
{
public:
	void run(){cout<<"父亲跑百米需要10秒"<<endl;}
	void eat(){cout<<"父亲不喜欢吃零食"<<endl;}
};
class Uncle:public Human
{
public:
	void run(){cout<<"舅舅跑百米需要12秒"<<endl;}
	void eat(){cout<<"舅舅喜欢偷吃零食"<<endl;}
};

int main (void)
{
	void (Human::*pf)()=0;
	Human *p=0;
	char choice1,choice2;
	bool quit=false;
	while(!quit)
	{
		cout<<"(0)exit (1)Mother (2)Father (3)Uncle"<<endl;
		cin>>choice1;
		switch(choice1)
		{
		case '0':quit=true;
			break;
		case '1':p=new Mother;//p指针指向对象
			break;
		case '2':p=new Father;//p指针指向对象
			break;
		case '3':p=new Uncle;//p指针指向对象
			break;
		default:choice1='q';
			break;
		}
		if(quit==true)
			break;
		else if(choice1=='q')
		{
			cout<<"请输入0到3之间的数字"<<endl;
			continue;
		}
		cout<<"(1)run (2)eat"<<endl;
		cin>>choice2;
		switch(choice2)
		{
		case '1':pf=&Human::run;
			break;
		case '2':pf=&Human::eat;
			break;
		default:break;
		}
		(p->*pf)();//p指针指向对象，pf指针指向成员函数
		delete p;
	}
	return 0;
}
