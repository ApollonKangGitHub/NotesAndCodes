/*
	2016��8��6��12:15:35
	new�ؼ��ֵ��÷�������malloc�������÷���
	����malloc��freeΪ��������new��deleteΪ�ؼ���

	��C++�����ڹ��캯�������������Ĵ��ڣ�
	���ڷ��ڲ��������͵Ķ�����ԣ�����malloc/free�޷����㶯̬�����Ҫ��
	�����ڴ�����ͬʱҪ�Զ�ִ�й��캯��������������֮ǰҪ�Զ�ִ������������
	����malloc/free�ǿ⺯������������������ڱ���������Ȩ��֮�ڣ�
	���ܹ���ִ�й��캯������������������ǿ����malloc/free�� 
*/
# include <iostream>
# include <string>
# define length 10
using namespace std;

typedef struct Node
{
	short i;
	short j;
	int x;
	double z;
}NODE,PNODE;

int main (void)
{
	int i;
	int * p = new int(100);//()�п���ֱ�Ӽӳ�ʼ����ֵ
	double * q = new double(20.34);
	string * ps = new string(10,'p');//��ʼ���ַ���
	short * r = (short *)new NODE;
	int * s = new int[length];//�����˺���ʮ������Ԫ�ص�����
	cout << "ָ��s��ռ�ڴ棺" << sizeof(s) << endl << "ָ��s�洢��ַ*s��ռ�ڴ棺" <<sizeof(*s) << endl;
	
	cout << *p << ' ' << *q << endl;
	cout << *ps << endl;
	for(i = 0;i<(sizeof(NODE)/sizeof(short));i++)
		cin >> *(r+i);
	for(i = 0;i<(sizeof(NODE)/sizeof(short));i++)
		cout << *(r+i) << ' ';

	cout << endl;
	for(i = 0;i<length;i++)
		cin >> s[i];
	for(i = 0;i<length;i++)//ע��γ���������i<(sizeof(s)/sizeof(int))
		cout << s[i] << ' ';
	cout << endl;

	delete p;
	delete q;
	delete r;
	delete ps;
	delete []s;//�����ڴ��ͷ�ʹ����Ϊdelete []������

	return 0;
}