/*
	2016��8��9��15:20:20
	constָ�����ӳ���ȫ��
*/
# include <iostream>
using namespace std;

class A
{
public:
	A(){cout << "ִ�й��캯������һ������\n";}//���캯��
	A(A&){cout << "ִ�и��ƹ��캯���������ö����һ��������\n";}//���ƹ��캯��
	~A(){cout << "ִ����������,ɾ������...\n";}//��������
	void set(int x){i = x;}
	int get()const{return i;}
private:
	int i;
};
//��һ��constȷ�����ص�oneָ��ָ��Ķ��󣨶�������г�Ա�������޸�		
//�ڶ���constȷ�����ص�oneָ�벻���޸�
//������constȷ�������ָ��oneָ��Ķ��󣨶�������г�Ա�������޸�
//���ĸ�constȷ�������ָ��one�����޸�
const A * const func (const A * const one)									
{			
	one->get();
	//one->set(10);//oneָ��ָ��Ķ��󲻿��Ա��޸ģ����Իᱨ��
	//one++;//oneָ�뱻�����const�������Լӱ仯�ᱨ��
	return one;	
}
int main (void)
{
	A a;
	a.set(11);
	cout << a.get() << endl;
	//A * q = func(&a);	//����ֵ���ͺͽ������Ͳ�ƥ��
	const A * const p = func(&a);
	//p++;	//pָ�뱻�����const�������Լӱ仯Ҳ�ᱨ��
	cout << "p����ĵ�ַ��" << p << endl << "����a�ĵ�ַ��" << &a << endl;
	//p->set(100);//ͬ�������
	a.set(20);//ע��constֻ��������p��ͨ��p��ָ�򡣵���δ�ı�aԭ�����ԡ����ǲ���ͨ��p��ָ�����޸Ķ���ĳ�Ա��������ͨ��a�޸������Ա��
	cout << p->get() << endl;

	return 0;
					
}
