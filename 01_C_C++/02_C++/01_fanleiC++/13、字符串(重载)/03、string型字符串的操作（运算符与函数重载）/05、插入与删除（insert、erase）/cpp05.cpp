# include <iostream>
# include <string>
using namespace std;
int main (void)
{
	/*
		string�Ͳ���
	*/
	string str1 = "abcdefghijklmn";
	string str2 = "ABCDEFGHIJKLMN";
	cout<<str1<<'\t'<<str2<<endl;
	str1.insert(2,str2,1,4);
	//����1Ϊ���루str1�У���λ�ã�����2Ϊ�ṩ�����ַ����ַ�����str2��
	//����3Ϊ�ṩ�����ַ����ַ�������ʼλ��(str2��)������4Ϊ�ṩ�Ĳ����ַ��ĸ���(str2��)
	cout<<str1<<endl;

	/*
		string��ɾ��
	*/
	string s("GIVE ME LOVE QUIKLY!");
	cout<<"ԭʼ�ַ���Ϊ��"<<s<<endl;
	s.erase(2,2);//����1Ϊɾ������ʼλ�ã�����2Ϊɾ�����ַ�����
	cout<<"ɾ�����ַ���Ϊ��"<<s<<endl;
	s.erase(5);//ֻ��һ����������ʾ���±�Ϊ5��ʼ������ַ���ȫɾ��
	cout<<"ɾ�����ַ���Ϊ��"<<s<<endl;
	s.erase();//Ĭ��Ϊ0����ʾ���±�Ϊ0��ʼ������ַ���ȫɾ���������
	cout<<"ɾ�����ַ���Ϊ��"<<s<<endl;
	return 0;
}