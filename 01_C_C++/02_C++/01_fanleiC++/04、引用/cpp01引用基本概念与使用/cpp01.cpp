/*
	>>���þ��Ǳ�����&��Ϊȡ��ַ��ҲΪ���������
	>>Ӧ�ñ��������ʼ��,�ҵ�ĳһ�������ĵ�ַ�ϡ������ѹҺõĵ�ַ�����ٸı䡣
	>>�޸������ͱ�������ͨ�����е�����һ����ֵ����ı�����һ��
*/
# include <iostream>
using namespace std;

int main ()
{
	int i = 4;
	int j = 5;	
	int &ir = i;
	int &jr = j;

	cout << i << '\t' << ir <<endl;
	cout << j << '\t' << jr <<endl;

	ir = 40;
	jr = 50;
	cout << i << '\t' << ir <<endl;
	cout << j << '\t' << jr <<endl;

	cout << &i << '\t' << &ir << endl;
	cout << &j << '\t' << &jr << endl;

	ir = j;//ir��ֵ�ı�Ϊj��ֵ��i��֮�ı䡣����ir�ĵ�ַ������i�ĵ�ַ�����ᷢ���ı�
	cout << i << '\t' << ir <<endl;
	cout << j << '\t' << jr <<endl;
	cout << &i << '\t' << &ir << endl;
	cout << &j << '\t' << &jr << endl;

	return 0;

}