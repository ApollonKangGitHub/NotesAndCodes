/*
	2016��8��9��18:09:57
*/
# include <iostream>
using namespace std;

class Hello
{
public:
	Hello(int x){i = x;cout << "���ù��캯��,������һ������...\n";}
	Hello(Hello&a){i = a.i;cout << "ִ�и��ƹ��캯���������ö����һ��������\n";}
	~Hello(){cout << "��������������...\n";}
	int get()const{return i;}
private:
	int i;
};

Hello & func()//����ֵ����Ϊ������
{
	cout << "��ת��func()������!\n" << endl;
	Hello * p = new Hello(99);
	cout << "���ж���a�ĵ�ַ��" << p << endl;
	return *p;

}
int main (void)
{
	Hello & r = func();//r����ж����ַ��ͬ
	cout << "���ж���ĸ����ĵ�ַΪ:" << &r << endl;
	cout << r.get() << endl;

	Hello * p = &r;
	delete p;//delete���ܶ�����ֱ�Ӳ�����������ָ��������õĵ�ַȻ���ͷ�

	cout << r.get() << endl;
	//�������ַ���������ڴ�й©�����⣬�����ͷŶ��ж���֮��r����һ����ſն�������ã���������һ���ش�����������������
	//����������ǰע��֪���������Ĵ��ڣ���û�б���û�о����������Ǻ��Ѳ����
	return 0;
}
/*
	���н����
		��ת��func()������!

		���ù��캯��,������һ������...
		���ж���a�ĵ�ַ��00386CA0
		���ж���ĸ����ĵ�ַΪ:00386CA0
		99
		��������������...
		-572662307
		Press any key to continue



*/