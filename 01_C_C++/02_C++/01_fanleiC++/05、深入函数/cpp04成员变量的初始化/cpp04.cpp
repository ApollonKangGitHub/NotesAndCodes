/*
**	���ַ���������
**  ����һΪ��Ա�����ĸ�ֵ
**  ������Ϊ��Ա�����ĳ�ʼ��
**  �����ڳ�Ա��������Ϊconstʱ��ֵ���ܽ��У�����һ������û��ʼ�������ģ������Ǹ�ֵ�����������Ǹ�ֵ��Ȼ�ǲ��ܲ����ģ�������ʼ������
*/
# include <iostream>
using namespace std;
class rectangle
{
public:
//	rectangle(int l, int w)
//	{
//		cout << "���캯��������..." << endl;
//		length = l; width = w; 
//		cout << "�����ε����Ϊ��" << length * width << endl;
//	}//��ʼ���ķ���һ(ʵ��Ϊ��ֵ��û�г�ʼ��)

	//rectangle():length(5),width(12){cout << "���캯��������..." << endl << "�����ε����Ϊ��" << length * width << endl;}//��ʼ���ķ�����
	rectangle(int x, int y, int z):length(x),width(y),higth(z){cout << "���캯��������..." << endl << "�����ε����Ϊ��" << length * width << endl;}//Ҳ�ǳ�ʼ��

	~rectangle(){cout << "��������������..." << endl;}
private:
	//int length;
	//int width;
	//int higth;
	const int length;
	int & width;//���ú�constһ�������ʼ�����ҳ�ʼ�����ͱ���ƥ��
	const int higth;
};
int main (void)
{
	rectangle a(2,7,9);

	return 0;
}