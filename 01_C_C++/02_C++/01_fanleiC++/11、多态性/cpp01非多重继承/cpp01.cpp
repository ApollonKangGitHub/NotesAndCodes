#include<iostream>
using namespace std;
class father
{
public:
	void smart()
	{
		cout << "���׺ܴ���\n";
	}
	//virtual void beautiful(){}//�ú����ڸ�����û���κ����ã����౾Ӧ��ĸ���м̳У�����û��ĸ�࣬����Ϊ�˸������ṩһ���ӿڣ��ͼ�����û���κ�ʵ�ʹ��ܵ��麯��
	virtual ~father(){cout << "����father"<<endl;}
};

class son:public father
{
public:
	virtual void beautiful()
	{
		cout << "����Ҳ��˧\n";
	}
	son(){cout << "����son"<<endl;}
};

int main (void)
{
	father * pf;
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
		//	pf->beautiful();
			pf->smart();
			break;
		case 2:pf=new son;
			dynamic_cast<son*>(pf)->beautiful();//dynamic_cast��pfǿ��ת��Ϊson*ָ�롣���Ǳ����ڡ�����--����--C/C++--C++���ԡ��й�ѡRTTI�ſ���
			//pf->beautiful();//pfΪ����ָ�룬���ڸ����beautiful�Ѿ�ע�ͣ����Բ���ͨ��pf���ø�����û�еĳ�Ա
			pf->smart();
			delete pf;
		default:cout<<"�������0��2֮�������:";
		}
		if(quit)
		{
			break;
		}
	}
	cout<<"���������"<<endl;
	return 0;
}