/*
	2016��8��19��19:14:41
*/
# include <iostream>
using namespace std;

class A
{
public:
	A(){x = new int; *x = 5;cout << "���캯��ִ����..." << endl;}
	~A(){delete x; x = NULL;cout << "��������ִ����..." << endl;}
	A(const A&a)//����Ϊconst�ͣ����ñ������յ����ݽ�ֻ��ʹ�ã����ɸı䡣����ͨ��ָ����Խ���ֱ���޸�
	{
		cout << "���ƹ��캯��ִ����..." << endl;
		x = a.x;//ǳ�㸴�ƣ���������ռ��һ����ڴ�����
	}//�ø��ƹ��캯����ϵͳĬ�ϵĸ��ƹ��캯��������ͬ
	void set(int i){*x = i;}
	int print()const{return *x;}//ֻ���*x,�����Ըı�*x
private:
	int * x;
};
int main (void)
{
	A * a = new A();
	cout << "a:" << a->print() << endl;
	a->set(50);
	cout << "a:" << a->print() << endl;

	A b = (*a);
	a->set(20);
	cout << "b:" << b.print() << endl;
	b.set(50);
	cout << "b:" << a->print() << endl;
	//��*a���ݸ����ƹ��캯����aָ���ƹ��캯�����ٵĶ��пռ䣬b��ָ����xҲָ��öѿռ䡣ʵ����*a����b��Ŀ��

	//delete a;
	//���ڸ��ƹ��캯��������b�����xָ��ָ��Ķ��пռ����ͷţ��ͷ�֮��������aָ��Ķ��󡣶�aָ��������bָ��Ķ���
	//�Ѿ��ͷŵĿռ��޷��ҵ���ط������������ֱ���������ԭ�����ǳ�㸴��
	return 0;
}