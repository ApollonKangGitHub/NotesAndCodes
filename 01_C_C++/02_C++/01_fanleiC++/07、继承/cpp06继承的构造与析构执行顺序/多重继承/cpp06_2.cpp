/*
	2016��8��22��13:14:52
	���н����
		����e...
		����b...
		����c...
		����d...
		����a...
		����f...
		����f...
		����a...
		����d...
		����c...
		����b...
		����e...
		Press any key to continue

	���ؼ̳еĹ��캯������������ִ��˳��
	>>����Ĺ��캯��ִ��˳���ǰ��ռ̳�ʱ�������и�����˳��ִ�е�
	>>��������ִ��˳�����ǰ��ȹ����������������������˳��ִ�е�
	>>����Ĺ��캯���ڻ��๹�캯��ִ�����Ժ�ִ�У������๹�캯�����ִ�У�������������ִ��


*/
# include <iostream>
using namespace std;

class a
{
public:
	a(){cout << "����a..." << endl;}
	~a(){cout << "����a..." << endl;}
};
class b
{
public:
	b(){cout << "����b..." << endl;}
	~b(){cout << "����b..." << endl;}
};
class c
{
public:
	c(){cout << "����c..." << endl;}
	~c(){cout << "����c..." << endl;}
};
class d
{
public:
	d(){cout << "����d..." << endl;}
	~d(){cout << "����d..." << endl;}
};
class e
{
public:
	e(){cout << "����e..." << endl;}
	~e(){cout << "����e..." << endl;}
};

class f:public e, public b, public c, public d, public a
{
public:
	f(){cout << "����f..." << endl;}
	~f(){cout << "����f..." << endl;}
};
int main (void)
{
	f five;

	return 0;
}