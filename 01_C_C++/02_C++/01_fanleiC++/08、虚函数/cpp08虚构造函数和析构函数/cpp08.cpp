# include <iostream>
using namespace std;

class A
{
public:
	A(){cout << "����A" << endl;}
	virtual void func(){cout << "��A" << endl;}
	//~A(){cout << "����A" << endl;}
	virtual ~A(){cout << "����A" << endl;}//��������ж������麯������ô��������ҲӦ�ö�����麯���������ڴ�Ļ��ջ��׼ȷЩ
};
class B : public A
{
public:
	B(){cout << "����B" << endl;}
	virtual void func(){cout << "��B" << endl;}
	~B(){cout << "����B" << endl;}
};
int main (void)
{
	A * p = new B;
	p->func();
	delete p;
	return 0;
}