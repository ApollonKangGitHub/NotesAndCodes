# include<iostream>
using namespace std;
class A
{
public:
	A(int x,int y){rx=x; ry=y;}
		//ostream�����,�����������������ǰ�λ�����������
		//����ֵ����Ϊostream&������Ϊ�˿�����������cout<<a<<b;
		//���������s������ֵ����Ҳ����Ϊostream&����Ϊvoid����ֻ��cout<<a;cout<<b;�ֿ����
		//ostream��û�й��еĸ��ƹ��캯��������ostream�Ķ���cout�޷����ø��ƹ��캯��
		//�ʶ����ܰ�ֵ���ݲ�������ֵ���λ���ø��ƹ��캯�����������������밴���ô���
	//friend��ʾ��Ԫ����������ostream��Ķ���s�޷����������޹ص����˽�г�Ա��ֻ�н��ú�������Ϊ��Ԫ�����ſ��Է���
	friend ostream & operator<<(ostream & s,const A&c)
	{
		s<<c.rx;//coutΪ����s,����a(b)Ϊ����c
		s<<c.ry;
		return s;
	}
private:
	int rx;
	int ry;
};

int main (void)
{
	A a(3,4),b(5,6);
	cout<<a<<b<<endl;//<<�������������ǰ���ܶԶ�����в���

	/*��λ���������*/
	int num = 52;
	int x = num<<2;//��λ�������ƣ�����2λ���������Ƶ��ұߣ���ߣ���������0���ٰ�ʮ�������
	cout<<x<<endl;
	return 0;
}