# include <iostream>
using namespace std;
class A
{
public:
	A(){cout << "���캯��������..." << endl;}
	~A(){cout << "��������������..." << endl;}
	A(A&one){cout << "���ƹ��캯��������..." << endl;this->n = one.n; this->m = one.m;}
	A(int i, int j){cout << "���캯��������..." << endl; n = i; m = j;}//�������Ĺ��캯��
	void print(){cout << n <<  "\t" << m << endl;}
private:
	int n;
	int m;
};
int main (void)
{
	A a(2,4);
	a.print();
	A b(a);//������A�и��ƹ��캯��,��a�ĳ�Աȫ�����ƿ�����b
	b.print();
	
	return 0;
}