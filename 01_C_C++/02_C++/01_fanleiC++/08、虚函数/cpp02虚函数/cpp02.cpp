/*
	����ռ���ڴ棬ָ��ָ�����ָ��ӵ���ڴ棻�����Ƕ���ָ�뻹��ָ�룬�ڴ滹���ڴ档���߶������໥����
	���ߵ�������ϵ������ô��΢����΢����֮����������֮�š�
	�ؼ���virtual��ĳ����֮ǰ���֣���ʾ�ú����ж�����̬�����ú����ڶ����ͬ���ж��У����ҹ��ܲ�һ��
	��ôϵͳ��ִ�е��йؼ���virtual�ĺ���ʱ���ͻ��Զ��ж����ĸ��������������Ȼ����øö����������ͬ��������
	����������ָ��������ϵȥ���ã����Ǹ����ڴ�ռ�й�ϵȥ����
*/
# include <iostream>
using namespace std;

class father
{
public:
	father(){cout << "���ø���Ĺ��캯��..." << endl;}
	~father(){cout << "���ø������������..." << endl;}
	void jump()const{cout<< "���׿��������̨��!" << endl;}
	virtual void run()const{cout<< "���׿���������!" << endl;}
};

class son : public father
{
public:
	son(){cout << "��������Ĺ��캯��..." << endl;}
	~son(){cout << "�����������������..." << endl;}
	void jump()const{cout<< "���ӿ�����ʮ����̨��!" << endl;}
	void run()const{cout<< "���ӿ�����ʮ����!" << endl;}
};

int main (void)
{
	father *p = new son;
	p->jump();
	p->run();

	delete p;

	return 0;
}