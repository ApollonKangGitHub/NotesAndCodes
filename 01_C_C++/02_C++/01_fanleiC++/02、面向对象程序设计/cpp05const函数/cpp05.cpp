/*
	l-value specifies const object
	l��Ϊleft����������Ϊ��ֵΪ��������

	һ��Ҫ�ǲ���Ҫ�ı�ֵ�����ں�����ǰ�����const����ǿ����İ�ȫ��
*/
# include <iostream>
using namespace std;

class Human
{
public:
	void accept_data(int x,int y)/*const*/{i = x; j = y;}//���ں�����ǰ�����const����i��j��ֵ��Ϊ�������޷���ɸ�ֵ����ᱨ��
	int return_data()const{return i*j;}//�ú����ں�����ǰ����const��i��j��ֵ��û�иı����Բ��ᱨ��
private:
	int i ;
	int j ;
};

int main(void)
{
	Human Message;
	
	Message.accept_data(2,3);
	cout << "������˽��Ϊ��" << Message.return_data() << endl;
	Message.accept_data(4,7);
	cout << "������˽��Ϊ��" << Message.return_data() << endl;

	return 0;
}