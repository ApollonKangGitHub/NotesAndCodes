# include <iostream>
using namespace std;

class A
{
public:
	A(int x){i = x; cout<< "���캯��������..." << endl;}
	~A(){cout << "��������ִ����..." << endl;}
	int get(){return i;}

	operator int(){return i;}//�˴����ܼӷ���ֵ���ͣ�û�з���ֵ���Ͳ��������Է���ֵ
	//������˷���ֵ���ͻᱨ��user-defined conversion cannot specify a return type
	//���û������ת������ָ����������
	//����return iע�͵���main������x���������һ�����ֵ

private:
	int i;
};
int main (void)
{
	A a(36);
	cout << a.get() << endl;
	a = 1000;//������ʽת������̨��������
	cout << a.get() << endl; 
	a = A(20);
	cout << a.get() << endl; 
	
	int x = 999;//������ʽת������̨��������
	a = x;//���ǿ��Խ�������������
	cout << a.get() << endl; 

	x = a;//������a�ĳ�Աi��ͨ������operator int�������ظ�����x
	//��������A�ж�����operaator int�����ſ��Խ���A����Ķ���a�ĳ�Աת��Ϊint���Ͳ�����x
	//�������a��Ӧ�������Ҳ���operaator int�����Լ��书����������x=a�ĸ�ֵ���ܳɹ�
	cout << "x:" << x << endl;
	return 0;
}