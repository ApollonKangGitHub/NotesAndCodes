/*
	2016��8��19��18:01:30
	����ռ�ֽ�����ṹ�����ѭ������ͬ���ڴ�������ڴ油�루��ջ�кͶ���һ����
*/
# include <iostream>
using namespace std;
class A
{
public:
	int get(){return i+j+(int)m;}
	A(int x = 0, int y = 0, char c = ' ', double n = 0.0):i(x),j(y),ch(c),m(n){cout << "���ù��캯��" << endl;}
	~A(){cout << "����A����������..." << endl;}
private:
	const int i;
	const int j;
	const char ch;
	const double m;
};

class B
{
public:
	int get(){return i + j + (int)m;}
	B(int x = 0, int y = 0, char c = ' ', double n = 0.0):i(x),j(y),ch(c),m(n){cout << "���ù��캯��" << endl;}
	~B(){cout << "����B����������..." << endl;}
private:
	int i;
	int j;
	char ch;
	double m;
};
int main (void)
{
	A a(5,7,'2',2.225);
	B * b = new B(5,2,'p',3.665);

	cout << "��A��ռ�ڴ�Ϊ��" << sizeof(A) << "�ֽ�" << endl;
	cout << a.get() << endl;

	cout << "��B��ռ�ڴ�Ϊ��" << sizeof(B) << "�ֽ�" << endl;
	cout << b->get() << endl;

	delete b;
	b = 0;
	return 0;
}