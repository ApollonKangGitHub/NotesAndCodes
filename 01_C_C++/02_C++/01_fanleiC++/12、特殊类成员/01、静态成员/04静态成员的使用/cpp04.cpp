/*
	��̬��Ա�������ڼ�¼��˾ƥ�ֿ�������ܼ۸�
*/
# include<iostream>
using namespace std;

class aspl
{
public:
	aspl(float p){price=p;TotalPrice+=p;}
	~aspl(){TotalPrice=TotalPrice-price;}
	static float get(){return TotalPrice;}
private:
	float price;
	static float TotalPrice;
};
float aspl::TotalPrice=0;
int main (void)
{
	float f;
	cout<<"��˾ƥ�ֵĿ�����ܼ�ֵΪ��";
	cout<<aspl::get()<<endl;
	int i = 0;
	aspl*p[5];
	for(i=0;i<5;i++)
	{
		cout<<"�������"<<i+1<<"�ι�����˾ƥ�ֵĵ���۸�";
		cin>>f;
		p[i]=new aspl(f);
		cout<<"��˾ƥ�ֵĿ�����ܼ�ֵΪ��";
		cout<<aspl::get()<<endl;
	}

	cout<<"�����������İ�˾ƥ�ֵı�ţ���ż��ڼ��ι�����";
	cin>>i;
	delete p[i-1];
	cout<<"��˾ƥ�ֵĿ�����ܼ�ֵΪ��";
	cout<<aspl::get()<<endl;

	return 0;
}
