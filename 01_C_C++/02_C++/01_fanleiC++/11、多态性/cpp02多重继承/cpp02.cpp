/*
	�۲칹��������ִ��˳�������ؼ̳�

	pf=new son��pfָ��ֻ�ܷ��������father�м̳еĳ�Ա�����ܷ��ʴ�mother�м̵ĳг�Ա
	pm=new son��pmָ��ֻ�ܷ��������mother�м̳еĳ�Ա�����ܷ��ʴ�father�м̳еĳ�Ա
	
	��Ȼ���ؼ̳бȵ�һ�̳�������ŵ㣬�������������Ķ���ܸ��ӣ�ʹ��Ҳ���ײ��������ԣ�
	���Ե���һ�̳����������£�������Ҫʹ�ö��ؼ̳С�
*/
#include<iostream>
using namespace std;
class father
{
public:
	father(){cout<<"����father"<<endl;}
	void smart(){cout << "���׺ܴ���\n";}
	//virtual void beautiful(){}//�ú����ڸ�����û���κ����ã����౾Ӧ��ĸ���м̳У�����û��ĸ�࣬����Ϊ�˸������ṩһ���ӿڣ��ͼ�����û���κ�ʵ�ʹ��ܵ��麯��
	virtual ~father(){cout << "����father"<<endl;}
};
class mother
{
public:
	mother(){cout<<"����mother"<<endl;}
	virtual void beautiful(){cout << "ĸ�׺�Ư��\n";}
	virtual ~mother(){cout<<"����mother"<<endl;}
};
class son:public father,public mother
{
public:
	son(){cout<<"����son"<<endl;}
	virtual void beautiful(){cout << "����Ҳ��˧\n";}
	~son(){cout << "����son"<<endl;}
};

int main (void)
{
	father * pf;
	mother * pm;
	int choice = 0;
	while(choice<99)
	{
		bool quit=false;
		cout<<"(0)�˳�\t(1)����\t(2)����:"<<endl;
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