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
	void run(){cout<<"ĸ���ܰ�����Ҫ18��"<<endl;}
	void eat(){cout<<"ĸ��ϲ������ʳ"<<endl;}
};
class Father:public Human
{
public:
	void run(){cout<<"�����ܰ�����Ҫ10��"<<endl;}
	void eat(){cout<<"���ײ�ϲ������ʳ"<<endl;}
};
class Uncle:public Human
{
public:
	void run(){cout<<"�˾��ܰ�����Ҫ12��"<<endl;}
	void eat(){cout<<"�˾�ϲ��͵����ʳ"<<endl;}
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
		case '1':p=new Mother;//pָ��ָ�����
			break;
		case '2':p=new Father;//pָ��ָ�����
			break;
		case '3':p=new Uncle;//pָ��ָ�����
			break;
		default:choice1='q';
			break;
		}
		if(quit==true)
			break;
		else if(choice1=='q')
		{
			cout<<"������0��3֮�������"<<endl;
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
		(p->*pf)();//pָ��ָ�����pfָ��ָ���Ա����
		delete p;
	}
	return 0;
}
