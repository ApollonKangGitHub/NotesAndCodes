# include<iostream>
# include<string>
using namespace std;
int main (void)
{
	string str="455";
	if(str.empty())
		cout<<"���ַ���Ϊ�գ�"<<endl;
	else
		cout<<"���ַ�����Ϊ�գ��ַ���Ϊ��"<<str<<endl;

	/*
		C��swab(ch1,ch2,n)��ָ������(n/2)*2��ż�����븴�ƽ��
	*/
	char ch1[15]="ofru";
	char ch2[15]="ifev";
	cout<<"��ż����ǰ��"<<ch1<<"\t"<<ch2<<endl;
	swab(ch1,ch2,3);//��ch1��ǰ(3/2)*2=2���ַ���żλ�ý������Ƶ�ch2��ǰ(3/2)*2=2���ַ�λ�ô�����ch2ԭ��ǰ�����ַ����ǡ�ch1����
	cout<<"��ż������"<<ch1<<"\t"<<ch2<<endl;

	/*
		C++��str1.swap(str2);�����ַ�����ȫ����
	*/
	string str1="ofru";
	string str2="";
	cout<<"����ǰ��"<<str1<<"\t"<<str2<<endl;
	str1.swap(str2);
	cout<<"������"<<str1<<"\t"<<str2<<endl;

	/*
		��string���ַ���ת��Ϊchar���ַ���
	*/
	string str3="hello world!";
	const char*ch;
	ch=str3.c_str();
	cout<<ch<<endl;
	return 0;
}