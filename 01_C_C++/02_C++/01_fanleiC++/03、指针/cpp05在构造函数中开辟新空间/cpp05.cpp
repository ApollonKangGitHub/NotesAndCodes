/*
	2016��8��6��14:39:48
*/
# include <iostream>
using namespace std;

class Human
{
public:
	Human(){cout << "���캯��ִ����..." << endl;i = new int(99);}//���캯���п����µĿռ�
	~Human(){cout << "��������ִ����... "<< endl;delete i;}
	//��Ϊdelete pʱ��ɾ���洢ָ��i�Ŀռ䣬��������������ָ��iָ��Ŀռ�Ҳ�����ͷ�
	//����i������ռ��ͷź�ᵼ���ڴ�й©
	void get(int x){*i = x;}
	int return_value()const{return *i;}
private:
	int * i;
};
int main (void)
{
	Human Mike;
	cout << Mike.return_value() << endl;
	Mike.get(120);
	cout << Mike.return_value() << endl;

	Human * p = new Human;
	cout << p->return_value() << endl;
	p->get(102);
	cout << p->return_value() << endl;

	delete p;
	return 0;
}
