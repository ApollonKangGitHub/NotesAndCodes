/*
	2016��8��22��16:20:06
	�����ԣ�
	�����ؼ̳�ʱ��һ������Ĳ�ͬ�Ļ��ຬ�г�Ա����ͬ�ĳ�Ա��������������ʱ����û�м������֡�
	��������֪�õ����ĸ������еĳ�Ա�����³��������

	����취��
	�ڵ��û����Աʱ���ڳ�Ա��ǰ������������������������������� ����::��Ա����

	�ܽ᣺
	�������޷����ֵ�Ҫ����������������������������ֵ�û��Ҫ�������������
*/
# include <iostream>
using namespace std;
class ONE
{
public:
	void hello(){cout << "����ONE��hello����" << endl;}
	void print(){cout << "����ONE��hello����" << endl;}
};

class TWO
{
public:
	void hello(){cout << "����TWO��hello����" << endl;}
	void print(){cout << "����TWO��print����" << endl;}
};

class THREE:public ONE,public TWO
{
public:
	void print(){cout << "����THREE��hello����" << endl;}
};

int main (void)
{
	THREE Mike;
	//Mike.hello();���첻�壬��Ϊ���������ж���hello()����
	//Mike.THREE::hello();//���Ǵ����ΪMike::hello()�������������
	
	Mike.ONE::hello();
	Mike.TWO::hello();
	Mike.ONE::print();
	Mike.TWO::print();
	Mike.print();
	//����������������⣬��Ϊ��������print()������������ֱ�ӵ��������print()������������ʻ���Ҳ����ǣ�����������������

	ONE Danny;
	Danny.ONE::hello();//û�б�Ҫ��::
	Danny.hello();
	
	return 0;
}