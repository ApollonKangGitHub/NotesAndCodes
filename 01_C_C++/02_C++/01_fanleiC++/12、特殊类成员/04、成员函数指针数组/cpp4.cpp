/*
	���ó�Ա����ָ�룬����ͨ����Ķ���������
	��Ա����ָ����ڸ��ӣ��ܲ��þ�������
*/
# include <iostream>
using namespace std;
class Paper
{
public:
	void read(){cout<<"ֽ������ֿ��Զ�"<<endl;}
	void write(){cout<<"ֽ��������д��"<<endl;}
	void burn(){cout<<"ֽ������������"<<endl;}
};

typedef void (Paper::*p)();
int main (void)
{
	p func[3]={&Paper::read,&Paper::write,&Paper::burn};
	Paper *pp = 0;
	char choice[1];
	bool quit=false;
	while(!quit)
	{
		cout<<"(0)exit (1)read (2)write (3)burn"<<endl;
		cin>>choice[0];
		if(choice[0]>'3' || choice[0]<'0')
			cout<<"Please input number between zero to three:"<<endl;
		else if(choice[0]=='0')	quit=true;
		else
		{
			int n;
			pp =new Paper;//������Ķ���
			n=atoi(choice);//���ַ�ת��Ϊ�������±�
			(pp->*func[n-1])();
			delete pp;
		}
	}
	return 0;
}
