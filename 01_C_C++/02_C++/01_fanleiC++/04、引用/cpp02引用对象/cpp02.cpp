/*
	���� &������2 = ������1;
	��Ϊ����һ�����ͣ����Ǳ�����û�о���ĵ�ַ�����Բ���Ϊ��ȡ������
*/
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
	/*	ջ�������ͱ���	*/
	Human Mike;
	Human &Miker = Mike;
	cout << &Mike << '\t' << &Miker << endl;
	
	cout << Mike.return_value() << '\t' << Miker.return_value() << endl;
	Mike.get(122);
	cout << Mike.return_value() << '\t' << Miker.return_value() << endl;
	Miker.get(124);
	cout << Mike.return_value() << '\t' << Miker.return_value() << endl;
	
	/*	���������ͱ���	*/
	Human * p = new Human;//����ΪHuman��������ĸ��ֽڵ��ڴ棬��ʱ�����˹��캯�����������ֽڷ��ظ�ָ��p��ֻ��ͨ��ָ��p�Զ��ڴ���в���
	Human * &pr = p;//pr��p��Ϊָ���������pr���ǹ���p��ַ�ϵ������ͱ���������pr��pָ��ͬһ������
	cout << pr << '\t' << p << endl;//���pr��p��ֵ����pr��p��ָ���ַ

	cout << p->return_value() << '\t' << pr->return_value() << endl;//ͨ������ָ�����
	p->get(102);
	cout << p->return_value() << '\t' << pr->return_value() << endl;
	pr->get(104);
	cout << p->return_value() << '\t' << pr->return_value() << endl;
	
	delete p;//û���ͷ���Ķ��ڴ�ʱ������������ִ�У���delete p�Ժ�͵�������������
	p = 0;
	//delete pr;//����Ҫ�þ䣬��Ϊp��prָ��ͬһ��ռ䣬�ͷ�һ�μ��ɣ�ֻ�轫prָ��0��ַ����
	//pr = 0;//�þ�Ҳ����Ҫ����ΪpΪ0ʱ;�����ͱ���prҲ��֮Ϊ0.

	return 0;
}
