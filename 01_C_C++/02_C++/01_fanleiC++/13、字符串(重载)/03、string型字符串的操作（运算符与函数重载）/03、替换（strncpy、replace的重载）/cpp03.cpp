/*
	strncpy(ch1,ch2,n);��ʹ��:��ch2��ǰn���ַ��滻ch1��ǰ�����ַ�
	

	replace()�������滻������ʵ��ɾ�������Ĺ��̣��Ȱ���ʼλ�ú͸���ɾ�����ַ����ַ�
	�ٰ����ַ�������ʼλ�ú͸��������ַ����в����ַ�

	replace()���غ����ĵ�������ʽ�������������
	basic_string&replace(size_type index1,size_type num1,const basic_string&str,size_type index2,size_type num2)
	�������£�
	str1(0,2,str2,1,3);
	//����1������������ʼλ���±�
	//����2����ʼλ�ÿ�ʼ���滻����
	//����3���ṩ�滻�ַ����ַ���
	//����4���ṩ�滻�ַ����ַ���ȡ�ַ�����ʼλ��
	//����5���ṩ���ַ�����
	
	replace()���غ����ĵ�������ʽ���ĸ���������
	basic_string&replace(size_type index,size_type num1,size_type num2��char ch)
	//����1������������ʼλ���±�
	//����2����ʼλ�ÿ�ʼ���滻����
	//����3���ṩ���ַ������������ṩ����һ���ַ�������������1ʱ�������ַ����ƶ�μ��ɣ�
	//����4���ṩ�滻�ַ���char���ַ�������
	//������2���ڲ���3�����滻��Χ�ڵ�δ���滻���Զ�ɾ�������滻�ַ��������滻���ַ���ǰ��
	//������2С�ڲ���3���ͳ�������λ�ã����滻�ַ��������滻���ַ�����λ��
*/
# include <iostream>
# include <string>
using namespace std;
int main (void)
{
	char ch1[] = "abcdef";
	char ch2[] = "ABCDEF";
	strncpy(ch1,ch2,3);
	cout<<ch1<<endl;

	string str1 = "QWERT";
	string str2 = "ZXCVB";
	cout<<str1<<"\t"<<str2<<endl;
	str1.replace(0,2,str2,2,3);
	//str2�Ĵ��±�Ϊ2��ʼ�������ַ��滻str1��str1�Ĵ��±�Ϊ0���ַ���ʼ�������ַ������ǣ�����str1ԭ�еĵ������ַ���Ϊ�˵��ĸ�
	cout<<str1<<endl;

	cout<<str1<<"\t"<<ch2<<endl;
	str1.replace(1,4,ch2,1,3);//replace()���غ���Ҳ֧��cahr���͵��ַ���,����char�����ַ����޷���Ϊ���滻�ַ���
	cout<<str1<<endl;

	char ch='P';
	cout<<str1<<"\t"<<ch<<endl;
	str1.replace(1,4,8,ch);
	cout<<str1<<endl;
	return 0;
}