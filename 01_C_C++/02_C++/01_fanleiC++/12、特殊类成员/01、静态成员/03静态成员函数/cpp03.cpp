# include <iostream>
using namespace std;

class A
{
public:
	void static show_n(){cout<<A::n;n++;}//nΪ��̬��Ա����������n�����ڷ��ʺ���ǰ��static
	void show_m(){cout<<m;m++;}//mΪ�Ǿ�̬��Ա��������������ʺ���ǰ���ܼ�static
	void set_m(int M){m=M;}
private:
	static int n;
	int m;
};
int A::n = 0;
int main (void)
{
	for(int i=0;i<5;i++)
	{
		A::show_n();//����ͨ���������ʾ�̬��Ա����
		cout<<'\t';
	}
	cout<<endl;
	A a;
	a.set_m(0);
	for(i=0;i<5;i++)
	{
		a.show_n();//Ҳ����ͨ�����������ʾ�̬��Ա����
		cout<<'\t';
	}
	cout<<endl;
	for(i=0;i<5;i++)
	{
		a.show_m();
		cout<<'\t';
	}
	cout<<endl;
	return 0;
}