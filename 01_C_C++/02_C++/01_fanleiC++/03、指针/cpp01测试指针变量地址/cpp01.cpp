/*
	2016��8��5��17:36:04
	����ָ������ĵ�ַ
*/
# include <iostream>
using namespace std;

int main (void)
{
	int i = 10;
	int j = 20;
	int k = 30;
	double m = 40.4;
	double n = 50.5;

	int * p = &i;
	int * q = &j;
	int * r = &k;
	double * s = &m;
	double * t = &n;

	cout << p << endl << q << endl << r << endl << s << endl << t << endl;
	cout << &p << endl << &q << endl << &r << endl << &s << endl << &t << endl;

	return 0;
}

/*
	�������Խ�����£�
		0018FF3C
		0018FF38
		0018FF34
		0018FF2C
		0018FF24
		0018FF20
		0018FF1C
		0018FF18
		0018FF14
		0018FF10
		Press any key to continue
	����ָ���������ͨ�����ĵ�ַ���ƣ���˳����ڴ���ֽڵ����ֽڷ��䣬�����ֽڵ����ֽ�ʹ�ã������ֽڵ����ֽڴ洢
	ֻ������ָ��������Σ�ָ�����ֻռ�ĸ��ֽڣ�32bit = 4Gb��������4GB�ڴ���˵����ı䡣��Ϊ�ڴ��ַ�ǰ�8bit����
	һ����ŵģ�����4���ֽڸպ��ܹ���ʾ4GB�ڴ��С�ó����е�ַ��
*/