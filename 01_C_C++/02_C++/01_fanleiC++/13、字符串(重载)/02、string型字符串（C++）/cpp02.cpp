/*
	string��һ���࣬��string������������Ƕ�����Ķ�������string���н������������ء�
	������str=="�ַ���";�У�==�����أ����ԱȽϣ�
	��ch=="�ַ���;�У�==�������Ͳ�ͬ�����ܱȽϡ�
	��ʹʹ��strcmp(ch,"�ַ���")Ҳ�ȽϷ��㣬������str=="�ַ���"������������ǲ���ֱ������
	�����������ʹ��string��Ķ����������ͨ��������������ֱ�����㡢�Ƚϵȡ�
*/
# include<iostream>
# include<string>
using namespace std;
int main (void)
{
	string str="string���ַ���";
	char ch[]="char���ַ���";
	cout<<str<<endl;
	cout<<ch<<endl;
	cout<<"�����롰������Ӣ�ĵ��ʣ�"<<endl;
	cin>>str;
	if(str == "dog")
		cout<<"����"<<str<<endl<<str<<"�ĵ�һ���ַ���"<<str[0]<<endl;
	else
		cout<<"�������"<<endl;

	cout<<"�����롰����Ӣ�ĵ��ʣ�"<<endl;
	cin>>ch;
	//if(ch == "pig")//chΪһ����ַ����ַ�����ܺ��ַ�����ȣ�����Զ����ִ��
	for(int i=0; i<strlen(ch); ++i)
	{
		char ch1[4]="pig";
		if(ch[i]!=ch1[i])
			break;
	}//���ַ����Ϳ��Բ���������ǲ�����ȷ�ĵ���,if(!(strcmp(ch,"pig")))��strcmp����Ҳ����ͬ����
	
	if(i==3)
		cout<<"��"<<ch<<endl<<ch<<"�ĵ�һ���ַ���"<<ch[0]<<endl;
	else
		cout<<"�������"<<endl;

	return 0;
}