# include <iostream>
using namespace std;

class Human
{
public:
	Human(){cout << "���캯��ִ����..." << endl;i = 99;}//���캯��
	~Human(){cout << "��������ִ����... "<< endl;}
	void get(int x){i = x;}
	int return_value()const{return i;}
private:
	int i;
};
int main (void)
{
	Human Mike;
	cout << Mike.return_value() << endl;
	Mike.get(120);
	cout << Mike.return_value() << endl;

	Human * p = new Human;//����ΪHuman��������ĸ��ֽڵ��ڴ棬��ʱ�����˹��캯�����������ֽڷ��ظ�ָ��p��ֻ��ͨ��ָ��p�Զ��ڴ���в���
	cout << p->return_value() << endl;//û�����ֵĶ���ֻ��ͨ��ָ����в���
	p->get(102);
	cout << p->return_value() << endl;

	delete p;//û���ͷ���Ķ��ڴ�ʱ������������ִ�У���delete p�Ժ�͵�������������
	p = 0;

	return 0;
}

/*
	�����
		���캯��ִ����...
		99
		120
		���캯��ִ����...
		99
		102
		��������ִ����...        //������������Զ�ִ��
		��������ִ����...        //����delete pʱ��ִ��
		Press any key to continue

*/

/*
	�ܽ᣺
	�����������������ͷ�Ϊ���������ڴ��
	�������ڶ��д�����ֻ��ִ��deleteʱ�Ż������������������Ա���п��ƣ�
	��������ջ�д���ʱ��ֻҪ����ִ�����ϵͳ�����Զ�ִ����������
	
*/