# include <iostream>
using namespace std;
class A
{
public:
	void print(){cout << "a" << endl;}
	//virtual void print(){cout << "a" << endl;}
	/*
		ʹ��virtualʱ��C++�Ըú���ʵ�ж�̬���࣬
		��ʹ��virtualʱ��C++�Ըú���ʵ�о�̬����
	*/
};
class B : public A
{
public:
	void print(){cout << "b" << endl;}
};
class C : public A
{
public:
	void print(){cout << "c" << endl;}
};

int main(void)
{
	A a;
	B b;
	C c;
	
	a.print();
	b.print();
	c.print();

	A * pa = &a;
	A * pb = &b;
	A * pc = &c;
	//��̬������ʹָ��pa��pb��pcһ��ʼ��ȷ����ָ��Ϊ���ࡣ��������Ϊ��������ʱ��������ַ����ָ��������ı䣬���Ǽ���ʹ��Ĭ�ϵĵ�ַ��ָ�����
	//����̬����ֻ���ڸ�pa��pb��pc�ֱ�ֵΪ&a��&b��&cʱ��ȷ���˸��Ե�ָ��Ϊ��ͬ����
	//�ɼ��̳���Ҫʵ�ֶ�̬�Ծͱ����ùؼ���virtual������Ҫ����ĺ���

	pa->print();
	pb->print();
	pc->print();

	return 0;
}