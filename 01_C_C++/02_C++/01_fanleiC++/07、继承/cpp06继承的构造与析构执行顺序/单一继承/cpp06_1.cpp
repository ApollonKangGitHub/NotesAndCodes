/*
	2016��8��22��13:07:55
	���н����
		grandfather�๹�캯��ִ����...
		�������a�Ĺ��캯������ִ����...        2
		��������b�Ĺ��캯������ִ����...        7
		��������b��������������ִ����...        7
		��������a��������������ִ����...        2
		grandfather����������ִ����...
		Press any key to continue

	����˳��������˳��
	���죺����ߵĻ��ࣨ���ࣩ��ʼ����
	����������͵����࿪ʼ����

	�磺AΪ���࣬BΪA�����࣬CΪB������
	��ô���캯������������ִ��˳��Ϊ��
		���캯��A->���캯��B->���캯��C->��������C->��������B->��������A
*/
# include <iostream>
using namespace std;

class grandfather
{
public:
	grandfather(){cout<< "grandfather�๹�캯��ִ����..." << endl;}
	~grandfather(){cout<< "grandfather����������ִ����..." << endl;}
};

class father:public grandfather
{
private:
	int a;
public:
	father(int i){a = i;cout << "�������a�Ĺ��캯������ִ����...\t" << a << endl;}
	~father(){cout << "��������a��������������ִ����...\t" << a << endl;}
};
class son:public father
{
private:
	int b;
public:
	son(int i, int j);
	~son(){cout << "��������b��������������ִ����...\t" << b << endl;}
};

//�������ཫ�����Ա�̳й������������๹�캯��son()���������ȷ��ʻ��๹�캯�������Ի��๹�캯��father()Ҫ���г�ʼ��:father(����)
son::son(int i, int j):father(i)
{
	b = j;
	cout << "��������b�Ĺ��캯������ִ����...\t" << b << endl;
}

int main (void)
{
	son Mike(2,7);//2������ʼ��father������ݳ�Աa��ֵ��7������ʼ��son�����ݳ�Աb
	
	return 0;
}