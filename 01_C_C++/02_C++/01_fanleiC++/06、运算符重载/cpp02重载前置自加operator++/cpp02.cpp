/*
	�µĹؼ��֣�operator���ز���������������������ò���һ��()����ʾһ������
	eg��operator++()����һ������

	C++���������ʹ��ʵ���Ǻ����ĵ��ã�
	�磺
	1+2;  =>  ���������operator+(int,int)����
	4.5+5.6;  =>  ���������operator+(double,double)����

	����������������ͬ�������б�ͬ����ʵ������������أ�Ҳ�����˺���������
*/
# include <iostream>
using namespace std;

class num
{
public:
	num(){n = 1; cout << "���캯��ִ����..." << endl;}//���캯����ʼ��
	~num(){cout << "��������ִ����..." << endl;}
	void set(int x){n = x;}
	int get(){return n;}
	void num_add(){++n;}
	void operator++(){++n;}
private:
	int n;
};
int main (void)
{
	num NUM;
	cout << "NUM:" << NUM.get() << endl;
	NUM.num_add();//���ú����Լ�
	cout << "NUM:" << NUM.get() << endl;
	++NUM;//����������Լӣ����Զ�����i.operator++()����
	cout << "NUM:" << NUM.get() << endl;

	return 0;
}