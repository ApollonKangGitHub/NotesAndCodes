/*
	2016��8��25��12:28:59

	father *p = new son;//right
	son *q = new son;//right
	son *r = new father;//error

	ע�����������޷�ʵ�֣���Ϊ����̳и���������ص㣬���Կ���ͨ������ָ�������������ڴ�ռ�
	��������ָ������ĳ�Ա�����ж��У������м̳к���ȻҲ���У�����Ķ����ܹ���������ָ��Ĳ���Ȩ�ޣ���
	�������еĳ�Ա�����в�һ���У���ô�����ָ�����Ȩ�޳�������Ķ���İ���������������ܰ�������ָ�룬���Բ���ʵ��
*/
# include <iostream>
using namespace std;

class father
{
public:
	father():age(54){cout << "���ø���Ĺ��캯��������ʼ��age��ֵΪ��" << age << endl;}
	~father(){cout << "���ø������������..." << endl;}
	void jump() const{cout<< "���׿��������̨��!" << endl;}
	void run()const{cout<< "���׿���������!" << endl;}
protected:
	int age;
};

class son : public father
{
public:
	son(){cout << "��������Ĺ��캯��..." << endl;}
	~son(){cout << "�����������������..." << endl;}
	void jump() const{cout<< "���ӿ�����ʮ����̨��!" << endl;}
	void run()const{cout<< "���ӿ�����ʮ����!" << endl;}
	void math(){cout << "��������ѧ��ʦ!" << endl;}
};

int main (void)
{
	father *p = new son;
	//����һ������Ķ�����ӵ�еĿռ䣩���ȵ��ø���Ĺ��캯�����ٵ�������Ĺ��캯����
	//ָ��p����Ϊfather *�����Զ�ָ��p�Ĳ����Ƕ�����̳еĸ����Ա�Ĳ��������������Ծ��Ǹ����
//	son *q = new son;
//	son *r = new father;
	p->jump();
	p->run();

	delete p;//p�Ǹ���ָ�룬�ͷŵ���Ȼ�Ǹ����ڴ棨��Ȼ�����ǰ�����ֵģ������ǽ������ڴ��С��������ʹ��Ȩ�ޡ�˭�в���Ȩ�ޣ����ڴ������˭��
	return 0;
}