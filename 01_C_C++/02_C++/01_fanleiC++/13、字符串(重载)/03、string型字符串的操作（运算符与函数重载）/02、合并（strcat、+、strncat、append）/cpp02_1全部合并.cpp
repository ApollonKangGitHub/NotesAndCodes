/*
	string������������������+��
	strcat()strlen()��size()��length()������ʹ��
*/
# include<iostream>
# include<string>
using namespace std;

int main (void)
{
	/*
		char�����ַ����ϲ�����ӣ�
	*/
	char ch1[38] = "--What's your name";//��������Ϊch1[38]һ����Ŀռ䣬ϵͳ����ݳ�ʼֵ�Զ�Ϊch1����sizeof(ch1)=17�ֽڳ��ȣ��ϲ�ʱ��ʹ�������
	cout<<"strlen(ch1):"<<strlen(ch1)<<'\t'<<"sizeof(ch1):"<<sizeof(ch1)<<endl;
	char ch2[] = "--My name is Jack";
	cout<<ch1<<endl<<ch2<<endl;
	strcat(ch1,ch2);
	cout<<ch1<<endl;
	cout<<"strlen(ch1):"<<strlen(ch1)<<'\t'<<"sizeof(ch1):"<<sizeof(ch1)<<endl<<endl;
	/*
		string�����ַ����ϲ�����ӣ�
	*/
	string str1 = "--How old are you?";//��Ȼû��ָ���ַ������ȣ�����string������Ը��ݶ��󳤶ȸı����иı�
	string str2 = "--I'm thirteen years old!";
	
	//size()��strlen()��length()���Ǽ���'\0'֮ǰ���ַ������ȣ�strlen()ΪC���Ժ�������strlen()��length()ΪC++����
	//��ôΪ��C++string���л�����������һ���ĺ���strlen()��length()��������length()Ϊ���ڵ�string��Ա����size�Ǻ���Ϊ�˼���STL�ӽ�ȥ�ĳ�Ա
	cout<<"strlen(str1):"<<strlen(str1.c_str())<<"\t\t";
	cout<<"str1.size():"<<str1.size()<<"\t\t";
	cout<<"str1.length():"<<str1.length()<<endl;

	cout<<str1<<endl<<str2<<endl;
	str1 += str2;
	cout<<str1<<endl;
	cout<<"strlen(str1):"<<strlen(str1.c_str())<<"\t\t";
	cout<<"str1.size():"<<str1.size()<<"\t\t";
	cout<<"str1.length():"<<str1.length()<<endl;

	return 0;
}