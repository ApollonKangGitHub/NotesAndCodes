# include <iostream>
# include <string>
using namespace std;
int main (void)
{
	/*char����char���ַ����ṩ�����ַ�*/
	char ch1[15] = "abcdefghijklmn";
	char ch2[] = "1234567890";
	cout<<"����ǰch1:"<<ch1<<"\tch2:"<<ch2<<endl;
	memmove(ch1,ch2,10);//ch2��ǰ10���ַ���������ch1��ǰʮ���ַ�
	cout<<"������ch1:"<<ch1<<endl;
	cout<<"����ǰch1:"<<ch1<<"\tch2:"<<ch2<<endl;
	strcpy(ch1,ch2);
	cout<<"������ch1:"<<ch1<<endl;

	/*string����char���ṩ�����ַ�������Ϊcopy*/
	string str = "abcdefghijklmn";
	cout<<"����ǰ:"<<"ch2:"<<ch2<<"str:"<<str<<endl;
	int n = str.copy(ch2,5,2);//����ֵΪ�����ĸ��������ڶ����������ڶ����������ܴ���ch2���ڴ淶Χ��
	//�ڶ�������Ϊstr�ṩ�����ĸ���������������Ϊstr��ch2�����ַ�����ʼ�±ꡣch2��ǰ����ַ���str�ĵ�3~8���ַ�����
	cout<<"������:"<<n<<"���ַ�"<<endl;
	cout<<"������:"<<"ch2:"<<ch2<<"str:"<<str<<endl;

	return 0;
}