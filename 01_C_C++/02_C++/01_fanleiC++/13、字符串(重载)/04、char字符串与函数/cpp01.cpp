# include<iostream>
using namespace std;
int get(const char *p);
char * get_ch(char * str);
int main(void)
{
	/*�ַ���������*/
	char ch[15]="hello world!";//�ַ������飬�ɶ���д�ɸ�
	char *p="Mike";//δ�����ַ���������ָ��洢��ַ���ɶ����ɸ�
	"study";//δ�����ַ�������������ֳ�����

	int length_ch = get(ch);
	int length_p = get(p);
	cout<<"ch�ַ������ȣ�"<<length_ch<<endl<<"pָ���ַ������ȣ�"<<length_p<<endl;

	ch[5] = 50;//�ɸ�,2��ASCII��Ϊ50
	cout<<ch<<endl;//�ɶ�
	cout<<*(p+5)<<endl;//ֻ�ɶ�

	/*�ַ����ķ���*/
	char c[10];
	char * ch1;
	cout<<"�������������֣�"<<endl;
	cin>>c;
	ch1 = get_ch(c);//delete []ch1����delete p�����������ţ�ɾ����ֻ�������һ���ַ��Ŀռ�
	cout<<"���������ǣ�"<<ch1<<endl;
	delete []ch1;
	ch1 = get_ch(p);//���ݵ���δ�������ַ������׵�ַp
	cout<<"���������ǣ�"<<ch1<<endl;
	delete []ch1;
	ch1 = get_ch("Jack");//���ݵ���δ�������ַ���
	cout<<"���������ǣ�"<<ch1<<endl;
	delete []ch1;

	return 0;
}

/*�����ַ�������*/
int get(const char *p)
{
	int count = 0;
	while(*p)
	{
		++count;
		++p;
	}
	return count;
}
/*û��ʵ�����壬����˵���˺�����η���char�ַ���:����char���ַ��������ַ���ַ����*/
char * get_ch(char * str)
{
	char *p = new char[strlen(str)+1];
	strcpy(p,str);
	cout<<p;
	return p;
}