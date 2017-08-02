/*
	C����:strchr(char���ַ���,�ַ�);//�ҵ������ַ����ַ����е�һ�εĳ���λ�õĵ�ַ��û�ҵ����ؿ�
	C++:
	find()����ֵΪ���ַ����ַ����е�λ�ã�û�ҵ�����string::npos,����string::npos�ڲ�ͬƽ̨��ֵ��ͬ�����Ƕ���������Ϊ�±�
	
	find_first_not_of(�ַ�x);		//���ҵ�һ�����ַ�x����ȵ��ַ�λ���±�
	find_first_of(�ַ�x);			//���ҵ�һ�����ַ�x��ȵ��ַ�λ���±�
	find_last_not_of(�ַ�x);		//�������һ�����ַ�x����ȵ��ַ�λ���±�
	find_last_of(�ַ�x);			//�������һ�����ַ�x��ȵ��ַ�λ���±�
	rfind(�ַ�x);					//rΪreverse����д����Ϊ��������rfind��Ϊ������ҵ�һ����ȵ��ַ������ظ��±�
	X_find_X����û�ҵ��ķ���ֵ���ǳ���string::npos
	

	��������find���������Լӵڶ�������n����ʾ�ڸù����£����±�Ϊn����n+1���ַ���ʼ���һ��߲��ҵ��±�Ϊn����n+1���ַ���ֹ

	����find()��rfind()��find_first_of()��find_last_of()�ڶ�������n����ʾ���ҵ���ʼλ��
	find_first_not_of()��find_last_not_of()�ڶ�������n����ʾ���ҵĽ�ֹλ��

	�磺str.rfind('a',6);��ʾ��str�ַ����У��ӵ��߸�Ԫ�ؿ�ʼ������ҵ�һ����a���ַ��������ظ�λ���±�
	���磺str.find_last_not_of('k',4);��ʾ��str�ַ����У����ҵ���5����ַ���ֹ�����һ�����ǡ�k�����ַ���������λ���±�
*/
# include<iostream>
# include<string>
using namespace std;
int main (void)
{
	/*
		char���ַ�����
	*/
	char ch[15];
	char *p,c='w';
	strcpy(ch,"hello world");
	p = strchr(ch,c);//�����ҵ����ַ���ַ
	if(p)
		cout<<"�ַ�"<<c<<"λ�ڵ�"<<p-ch+1<<endl;//p�����ch��ƫ����
	else
		cout<<"û���ҵ���"<<endl;

	/*
		string���ַ�����
	*/
	string str = "welcome C++ plus";
	int point = str.find('w',0);//0������ҵ���ʼλ���±�
	if(point-string::npos)
		cout<<"�ַ�"<<"w"<<"λ�ڵ�"<<point+1<<endl;
	else
		cout<<"û���ҵ���"<<endl;
	int pos = str.find_first_not_of('e');
	if(pos-string::npos)
		cout<<"���ַ�e��һ������ȵ��ַ�λ�ڵ�"<<pos+1<<endl;
	else
		cout<<"û���ҵ���"<<endl;

	pos = str.rfind('e',12);
	if(pos-string::npos)
		cout<<pos+1<<endl;
	else
		cout<<"û���ҵ���"<<endl;

	pos = str.find_last_of('e',4);
	if(pos-string::npos)
		cout<<pos+1<<endl;
	else
		cout<<"û���ҵ���"<<endl;

	return 0;
}