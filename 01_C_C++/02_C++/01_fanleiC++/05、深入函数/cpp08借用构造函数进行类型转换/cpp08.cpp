# include <iostream>
using namespace std;

class A
{
public:
	explicit A(int x){i = x; cout << "���캯��ִ����..." << i<< endl;}
	//explicit�����ر�ǿ��ת������ֹ���ַ���Ϊ������ת�����֣���ֻ�ܹر���ʽת������ʽת�����׷����������ܹر���ʽת��
	~A(){cout << "��������ִ����..." << i << endl;}
	void get(){cout << i << endl;}
private:
	int i;
};
int main (void)
{
	A a(99);
	a.get();
	//a.~A();
	//a = 1000;//�ȼ���a = A(1000);���ù��캯��������һ����ʱ����������Ҫ����
	a = A(1000);
	//������������ֹһ��ʱ������a = A()����ʽ
	//a = 1000;Ϊ��ʽת����a = A(1000);Ϊ��ʽת��


	return 0;
}