# include<iostream>
using namespace std;
class A
{
public:
	A(int x){rx=x;}
	friend ostream & operator<<(ostream & s,const A&c)//������������
	{
		s<<c.rx;
		return s;
	}
	friend istream & operator>>(istream & s,A&c)//�������������
	{
		s>>c.rx;
		return s;
	}
	int operator++()//ǰ���Լ����������
	{
		cout<<"ִ��++i:\n";
		rx++;
		return rx;
	}
	int operator++(int)//�����Լ�������������أ�int�Ͳ�����������ǰ���Լ�����
	{
		cout<<"ִ��i++:\n";
		int i=rx;
		rx++;
		return i;
	}
private:
	int rx;
};

int main (void)
{
	A a(3),b(5);
	cout<<a<<b<<endl;

	cout<<++a<<a++<<endl;
	//VC++6.0�У��������ֵ��ѹջ�������ֵΪ���ҵ���
	//��ִ��a++����ִ��++a
	//(1)��a++���Ƚ�a=3ѹջ,��a=a+1=4;
	//(2)��++a����a=a+1=5;�ڽ�5ѹջ
	//(3)�����ʱΪ��ջ������5��ջ���������5�������3

	cout<<"������a��b��ֵ���س�һ�Σ������������룺"<<endl;
	cin>>a>>b;
	cout<<a<<b<<endl;
	return 0;
}