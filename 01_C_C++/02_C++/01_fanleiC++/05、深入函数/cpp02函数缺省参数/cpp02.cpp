/*
	������ȱʡ�����������б�ĳ�ʼ����
	��ʼ��֮������Բ����д��Σ���ʱ��ʼ����ֵ����Ĭ�ϵĲ�������ʹ�ã�
	����ʼ������д��Σ���ô���ݵ��²����͸��ǳ�ʼ���Ĳ���������ʹ��

*/
# include <iostream>
using namespace std;

class A
{
public:
	void set (int = 30, int = 50);
	//��������ʱ����Ҫ��������������ȱʡ�������������б��ʼ����ʱֱ�Ӹ�ֵ����
	//void set (int width = 30, int height = 50);
	//Ҳ���Դ��������������Ժ��ʹ��ֻ�����Ѿ������Ĳ������ˡ�
	void count(bool = false);
	//void count(bool val = false);
private:
	int w;
	int h;
};

void A::set (int width, int height)
{
	w = width;
	h = height;
}

void A::count(bool val)
{
	if(val == true)
		cout << "val��ֵΪ��ʱ��"  << w*h << endl;
	else
		cout << "val��ֵΪ��ʱ��"  << w*h/2 << endl;
}

void func(int n = 1, int m = 2)
{
	cout << "n:" << n << "\t" << "m:" << m <<endl;
}

int main (void)
{
	func();
	func(7,12);
	
	A a;
	a.set();
	a.count();
	a.count(true);
	//ȱʡ����������Ĭ��ֵ���ĺ�����Ҳʵ���˺������ء�һ�����ò���������һ�����ô�����
	//����Ĭ�ϲ����ĺ������ص��ǲ�������ֵ�������غ������ص��ǲ���������
	//����Ĭ�ϲ����ĺ������ӱ�ע���ױ����ԣ��������ױ����в�����ͬ����������

	a.set(25,30);
	a.count();
	a.count(true);

	return 0;
}