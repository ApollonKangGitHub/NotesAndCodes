/*
	2016��9��14��16:21:10
	���еľ�̬��Ա����
*/
# include<iostream>
using namespace std;

class A
{
public:
	A (int num):it(num){++total;}//ÿ����һ������total��1
	static int total;//������̬��Ա����
	~A(){--total;}//ÿ����һ������total��1
	int get(){return it;}
	void set(int age){it = age;}
private:
	int it;
};
int A::total = 0;//���徲̬��Ա����
int main(void)
{
	int i;
	const int max = 5;
	A*a[max];
	for(i=0;i<max;++i,++A::total)//��ʹû�ж��������Ҳ����ֱ�ӵ��þ�̬��Ա����
		cout<<A::total<<endl;
		
	for(i=0,A::total=0;i<max;++i)
		a[i] = new A(i);//�������
	for(i=0;i<max;++i)
	{
		cout<<"������"<<a[i]->total<<"������"<<endl;//Ҳ����ͨ����Ķ��������ò����ڶ���ľ�̬��Ա����
		cout<<"����ɾ����"<<a[i]->get()<<"������"<<endl;
		delete a[i];
	}

	A b(2),c(3),d(4);
	cout<<b.total<<'\t'<<c.total<<'\t'<<d.total<<endl;//total��̬��Ա����Ϊȫ�ֵģ��������κζ�����ֻ��һ��
	cout<<b.get()<<'\t'<<c.get()<<'\t'<<d.get()<<endl;//it��Ա��������ȫ�ֵģ�ÿ�����󶼵���ӵ��һ��
	return 0;
}