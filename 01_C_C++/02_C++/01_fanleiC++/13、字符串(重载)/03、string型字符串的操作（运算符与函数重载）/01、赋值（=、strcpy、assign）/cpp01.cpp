/*
	string�������˸�ֵ�������=��
	�����������÷���
	strcpy(ch1,ch2);
	str1.assign(str2,h,l);
*/
# include<iostream>
# include<string>
using namespace std;

int main (void)
{
	/*
		C���Ե��ַ�����ֵ
	*/
	char ch1[] = "give me";
	char ch2[] = "a cup";
	cout<<ch1<<endl;
	//ch1 = ch2;//����ĸ�ֵд����ch2������ֱ�Ӹ���ch1
	*ch1 = *ch2;//�൱��ch1[0]=ch2[0]��ֻ�ı����ַ�������ĵ�һ���ַ�
	cout<<ch1<<endl;
	strcpy(ch1,"hello!");//�������ַ������Ȳ��ܴ���ch1���ڴ泤��
	cout<<ch1<<endl;
	strcpy(ch1,ch2);
	cout<<ch1<<endl<<endl;

	/*
		C++�ַ�����ֵ
	*/
	string str1 = "GIVE ME";
	string str2 = "A CUP";
	cout<<str1<<endl;
	cout<<str2<<endl;
	str1=str2;//str2����ֱ�Ӹ���str1
	cout<<str1<<endl;
	//*str1=*str2;//����������д
	cout<<str1<<endl;

	str1.assign(str2,0,3);//assign()������str2��,���±�Ϊ0��Ԫ��ȡ3���ַ�����str1
	cout<<str1<<endl;


	return 0;
}