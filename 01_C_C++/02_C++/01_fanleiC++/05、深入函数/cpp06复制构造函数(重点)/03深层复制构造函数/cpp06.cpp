/*
	���ǳ�㸴�ƴ���������ķ����ǣ���㸴��
	��Ϊ�¶��󴴽�һ���µ��ڴ档��һ������Ĳ�������Ӱ����һ��
*/
# include <iostream>
using namespace std;

class A
{
public:
	A(){x = new int; *x = 5;cout << "���캯��ִ����..." << endl;}
	~A(){delete x; x = NULL;cout << "��������ִ����..." << endl;}
	A(const A&a)
	{
		cout << "���ƹ��캯��ִ����..." << endl;
		x = new int;
		*x = *(a.x);//���*xΪ���ƹ��캯���������¶����x��Ա��ָ��Ŀռ䡣�ұ�Ϊ���յľɶ����x��Ա��ָ��Ŀռ䡣
		//����ռ䲻��һ���ռ�,�Ѿɵĸ��ƹ��������µĲ����Ͳ���Ӱ��ɵ���
	}
	void set(int i){*x = i;}
	int print()const{return *x;}//const��ʾprint���������޸�xָ���ֵ
private:
	int * x;
};
int main (void)
{
	A * a = new A();
	cout << "a:" << a->print() << endl;
	a->set(50);
	cout << "a:" << a->print() << endl;

	A b = (*a);//���ƹ�ȥʱb����ĳ�ԱֵΪ50
	a->set(20);//�޸�aָ��Ķ���ĳ�Աֵ����ı�b����ĳ�Աֵ
	cout << "a:" << a->print() << endl;
	cout << "b:" << b.print() << endl;

	b.set(80);//�޸�bָ��Ķ���ĳ�ԱֵҲ����ı�a����ĳ�Աֵ
	cout << "a:" << a->print() << endl;
	cout << "b:" << b.print() << endl;

	delete a;
	//cout << "a:" << a->print() << endl;//aָ��ռ��Ѿ��ͷţ��޷���ʹ��
	cout << "b:" << b.print() << endl;


	return 0;
}