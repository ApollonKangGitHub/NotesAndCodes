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
private:
	int n;
};
int main (void)
{
	num NUM;
	cout << "NUM:" << NUM.get() << endl;
	//++NUM;//NUMΪ����Ҫ�����Աn�Լӣ�����ֱ�Ӷ������NUM�����ԼӲ���
	NUM.num_add();//���ó�Ա�����Գ�Ա���������Լӣ�Ȼ����ó�Ա�����ķ���������󲻿��Լӵ�����
	cout << "NUM:" << NUM.get() << endl;
	NUM.num_add();//�������ַ����������ȽϷ���
	NUM.num_add();
	cout << "NUM:" << NUM.get() << endl;

	return 0;
}