/*
	//cin�������ո�32���Ϳ��ַ���0�������ֹ����
	//��coutֻ�����������ַ�ʱ���Ż��ֹ���

	�ַ������뻹��һ�����ص����⣺
	�Ǿ��ǵ��������������������cin����cin.get()������ν�Ǹ���ǰ�棬�Ǹ��ں���
	������ֵ���һ��������û����ȫ����ʱ�������ǳ����������ƣ�Ҳ������cin�����ո�
	��������ʲô������µ��ַ���δ����ȫ¼�룬��һ��δ��¼��ĵ��ַ���ֱ��ռ����һ������Ŀռ�
	ֱ�ӽ������ڶ������롣
	eg��
	char a[4];
	char b[4];
	cin>>a;
	cin.get(b,6);
	cout<<a<<'\t'<<strlen(a)<<endl;
	cout<<b<<'\t'<<strlen(b)<<endl;
	������hel
	�������
	hel		3
	���Ҽ����ȴ��ڶ����ַ�������

	������hello
	��ֱ�����:
	hel		3
	lo		2
*/
#include<iostream>
#include<string>
using namespace std;
int main (void)
{
	char name[5]={'J','a','c','k','\0'};//���ֳ�ʼ����ʽ�����'\0'����Ϊ������־
	cout<<name<<endl;

	char women[16];
	cin.get(women,16);//����ʱ���Զ���ȡǰ�Ÿ��ַ�����ʮ��Ĭ��Ϊ'\0'���ո�Ҳ���ַ�
	cout<<women<<endl;
	cout<<"strlen(women):"<<strlen(women)<<endl;//strlen ����ǿɼ��ַ������ȣ��ӵ�һ���ַ���'\0'������������'\0'
	cout<<"sizeof(women):"<<sizeof(women)<<endl;//sizeof�����������ռ䳤��
	women[6]='\0';//�滻Ϊ���ַ���strlenֵ��ı䣬��sizeofֵ����ı�
	cout<<women<<endl;
	cout<<"strlen(women):"<<strlen(women)<<endl;
	cout<<"sizeof(women):"<<sizeof(women)<<endl;

	char man[10];
	cin>>man;//�ո����ַ�����Ϊ������־
	cout<<man<<endl;
	cout<<strlen(man)<<endl;
	
	char ch_1[]={'I',32,'l','o','v','e',32,'y','o','u','\0'};
	cout<<ch_1<<endl;
	char ch_2[]={'I',32,'l','o','v','e',0,'y','o','u','\0'};
	cout<<ch_2<<endl;

	char *point_1="hello everyone";
	cout<<point_1<<endl;
	char point_2[15]="hello everyone";
	cout<<point_2<<endl;
	
	return 0;
}