# include <iostream>
using namespace std;
class A
{
public:
	void Set(int x, int y)
	{
		a=x;
		b=y;
	}
	void Show()
	{
		cout<<"a:"<<a<<'\t'<<"b:"<<b<<endl;
	}
private:
	int a;
	int b;
};

void(A::*p)(int, int);//��ĳ�Ա����������

int main (void)
{
	int x=2,y=3;
	A a;
	p=&A::Set;//p�����˶���A��set�����ĵ�ַ��p==&set��
	(a.*p)(x,y);//a.*P���ʾ����a����*p������������set������*p==set��
	a.Show();
	return 0;
}
