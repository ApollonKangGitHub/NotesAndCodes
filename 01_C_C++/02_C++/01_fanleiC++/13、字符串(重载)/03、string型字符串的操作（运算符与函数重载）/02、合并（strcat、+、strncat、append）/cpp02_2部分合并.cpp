/*
	strcat(ch1,ch2)�����ı���strncat(ch1,ch2,n)
	C++��str1.append(str2,h,l)��������Ҫǿ����strncat(ch1,ch2,n)
*/
# include<iostream>
# include<string>
using namespace std;

int main (void)
{
	/*
		char�����ַ������ֺϲ�
	*/
	char ch1[38] = "--What's your name";
	char ch2[] = "--My name is Jack";
	cout<<ch1<<endl<<ch2<<endl;
	//strcat(ch1,ch2);
	strncat(ch1,ch2,10);//strncat(ch1,ch2,n);������ch2ǰn���ַ��������ӵ�ch1����,
	cout<<ch1<<endl<<endl;
	/*
		string�����ַ����ϲ�����ӣ�
	*/
	string str1 = "--How old are you?";
	string str2 = "--I'm thirteen years old!";
	cout<<str1<<endl<<str2<<endl;
	//str1 += str2;
	str1.append(str2,0,5);//append()������str2��,���±�Ϊ0��Ԫ�ؿ�ʼȡ5���ַ��������ӵ�str1�ַ������
	cout<<str1<<endl;

	return 0;
}