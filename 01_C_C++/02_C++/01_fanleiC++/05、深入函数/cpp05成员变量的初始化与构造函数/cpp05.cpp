//����˳��������˳��
# include <iostream>
using namespace std;

class demo
{
public:
	demo () {x= 0; cout << "demoĬ�ϵĹ��캯��������..." << x << endl;}
	demo (int i) {x = i; cout << "demo�Ĵ�һ�������Ĺ��캯��������..." << x << endl;}
	~demo(){cout << "demo��Ĭ����������������..." << x << endl;}
	int get(){return x;}
	void set(int i){x =i;}
private:
	int x;
};
class rectangle
{
public:

	rectangle(){x = 1000; cout << "rectangle��Ĭ�Ϲ��캯��������..." << x << endl;}
	rectangle(int i, int j, int k):x(i),width(j),length(k)//��ʼ��,���ճ�Ա�б��˳���죬�����ȹ����������ԭ������
	{
		cout << "rectangle�Ĵ����������Ĺ��캯��������..." << "�����ε����Ϊ��"  << length.get() * width.get() << endl;
	}
	~rectangle(){cout << "rectangle��Ĭ����������������..." << x << endl;}
	int area(){return length.get() * width.get();}
private:
	int x;
	demo length;
	demo width;//һ�����д�����һ����Ķ��󣬽С����ݡ�
	
};
int main (void)
{
	rectangle a(100,200,300);
	return 0;
}