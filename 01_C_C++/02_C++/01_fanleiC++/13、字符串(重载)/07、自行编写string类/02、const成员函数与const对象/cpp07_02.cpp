# include<iostream>
using namespace std;
class A
{
public:
	A(int i, int j){x=i;y=j;}
	void set(int s1,int s2){x=s1;y=s2;}
	void print(){cout<<x<<endl;}
	void print()const{cout<<y<<endl;}
private:
	int x;
	int y;
};
int main (void)
{
	/*
		const��Ա����ֻ�ܱ�const������ã�
		const���εĺ������ڣ����ܵ��÷�const��Ա����
		��const��Ա����ֻ�ܱ���const������ã�
		���ֹ�ϵ��һһ��Ӧ�ġ�
		��const�����Ա���������޸�

		const���εĻ����Ա�������ɷ�ֹ�����า�Ǻ�������۸����ݳ�Աֵ
	*/
	const A a(1,2);
	a.print();
	//a.set(3,4);
	A b(5,6);
	b.print();
	b.set(7,8);
	b.print();
	return 0;
}