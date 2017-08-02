#include<iostream>
using namespace std;

class human
{
public:
	//virtual void smart(){}
	virtual void smart()=0;//���麯������0�ͳ�Ϊ�˴��麯��
	virtual void beautiful()=0;//���麯��
	//���麯�������ܽ����κβ�����������̳иú����ͱ����б���Ϊ�ú��������¹��ܡ����κ�һ��������û�иú������߲�Ϊ�ú��������µĹ��ܣ��ͻᱨ��
	//��Ϊ�̳��˸ô��麯�������������µĹ��ܣ��Ͳ�������������µ����������Ϊ��һ������Ķ���
	virtual ~human(){cout<<"����human"<<endl;}
	human(){cout<<"����human"<<endl;}
};

/*
	human���������Ϊ�������ṩһ���ӿڵ����ã���������Ĵ��麯��û���κ�����
	�����ཫ��Щ���麯���̳й�����Ȼ��Ϊ���Ǹ����µĲ�ͬ�Ĺ��ܡ�
	ע������಻�ܴ���������Ȼ���ܶ��������Ķ��󣬵��ǿ��Զ���������ָ�롣��ָ���ڱ���ʱ���Զ�̬��ָ������Ķ���
*/
class father:virtual public human 
{
public:
	father(){cout<<"����father"<<endl;}
	virtual void smart(){cout << "���׺ܴ���\n";}
	virtual void beautiful(){cout << "���ײ���˧\n";}
	virtual ~father(){cout << "����father"<<endl;}
};
class mother:virtual public human
{
public:
	mother(){cout<<"����mother"<<endl;}
	virtual void beautiful(){cout << "ĸ�׺�Ư��\n";}
	virtual void smart(){cout << "ĸ�ײ�������\n";}
	virtual ~mother(){cout<<"����mother"<<endl;}
};
class son:public father,public mother
{
public:
	son(){cout<<"����son"<<endl;}
	virtual void beautiful(){cout << "����Ҳ��˧\n";}
	virtual void smart(){cout << "����Ҳ�ܴ���\n";}
	virtual ~son(){cout << "����son"<<endl;}
};

int main (void)
{
	human *p;
	int choice = 0;
	while(choice<99)
	{
		bool quit=false;
		cout<<"(0)�˳�\t(1)����\t(2)����\t(3)ĸ��:"<<endl;
		cin>>choice;
		switch(choice)
		{
		case 0:quit=true;
			break;
		case 1:p=new father;
			p->smart();//pָ��fatherr�ʵ���father��ĳ�Աsmart
			p->beautiful();
			delete p;
			break;
		case 2:p=new son;
			p->beautiful();//pָ��son�ʵ���son��ĳ�Աbeautiful
			p->smart();//pָ��son�ʵ���son��ĳ�Աsmart
			delete p;
			break;
		case 3:p=new mother;
			p->beautiful();//pָ��mother�ʵ���mother��ĳ�Աbeautiful
			p->smart();
			delete p;
			break;
		default:cout<<"�������0��2֮�������:";
			break;
		}
		if(quit)
		{
			break;
		}
	}
	cout<<"���������"<<endl;
	return 0;
}