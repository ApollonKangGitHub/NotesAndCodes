# include<iostream>
using namespace std;

class A
{
public:
	void Func(){cout<<A::x;}//Ҫ����˽�еľ�̬��Ա������ֻ�������ж���ͨ�����ù��г�Ա���������á�
private:
	static int x;//˽�еľ�̬��Ա����
};
int A::x=1000;
int main(void)
{
	A a;
	a.Func();
	cout<<endl;
	return 0;
}