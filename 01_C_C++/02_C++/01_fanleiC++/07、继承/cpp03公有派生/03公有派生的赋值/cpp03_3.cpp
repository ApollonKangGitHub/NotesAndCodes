/*
	2016��8��22��11:27:14
*/
# include <iostream>
using namespace std;

class FATHER
{
public:
	int x;
};

class SON:public FATHER//��������
{
public:
	int y;
};

int main (void)
{
	FATHER Mike;
	SON Jack;

	Jack.x = 20;
	Jack.y = 30;//�����Ա����ʼ�����о��棬���಻��ʼ�������о���
	cout << "Jack.x:" << Jack.x << '\t' << "Jack.y:" << Jack.y << endl << "Mike.x:" << Mike.x << endl<< endl;//����û�г�ʼ��ʱ�����������

	//Jack = Mike;
	Mike = Jack;//����Ķ�����Ը������࣬���Ǹ���Ķ����ܸ�������
	cout << "Jack.x:" << Jack.x << '\t' << "Jack.y:" << Jack.y << endl << "Mike.x:" << Mike.x << endl<< endl;

	Mike.x = 40;
	cout << "Jack.x:" << Jack.x << '\t' << "Jack.y:" << Jack.y << endl << "Mike.x:" << Mike.x << endl<< endl;

	FATHER * p;
	p = &Jack;
	p->x = 45;
	cout << "ͨ������ָ��p�޸��������Jack�ĳ�Աx��Jack.x=" << Jack.x << endl;//ָ��pΪFATHER *���ͣ����Բ�����ֻ����Jack�����SON��̳е�FATHER��ĳ�Աx�����ܲ���y
	
	FATHER &Tom = Jack;//��������ÿ�����Ϊ�������ı���
	Tom.x = 55;
	cout << "ͨ���������Tom�޸��������Jack�ĳ�Աx��Jack.x=" << Jack.x << endl;//ͬ����TomΪFATHER &���ͣ����Բ�����ֻ����Jack�����SON��̳е�FATHER��ĳ�Աx�����ܲ���y

	SON & Danny = Jack;
	Danny.x = 77;
	Danny.y = 88;
	cout << "Danny.x == Jack.x = " << Jack.x << endl << "Danny.y == Jack.y = " << Danny.y << endl;

	return 0;
}