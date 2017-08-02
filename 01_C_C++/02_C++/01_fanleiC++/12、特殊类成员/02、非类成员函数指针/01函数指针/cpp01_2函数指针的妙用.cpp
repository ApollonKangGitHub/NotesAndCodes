# include <iostream>
# include <string>
using namespace std;

//����ָ�룬����Ϊ����ָ�븳��������������Ҳ��һ��ָ�룩
float (*fp)(float&,float&);
void (*p)(float&,float&);

float triangle(float &x,float &y)
{
	return x*y*0.5;
}
float rectangle(float &x,float &y)
{
	return x*y;
}
void SWAP(float &x,float &y)
{
	float temp;
	temp = x;
	x = y;
	y = temp;
}
void print(float &x,float &y)
{
	cout<<"��Ϊ(��)��"<<x<<"\t��(��)Ϊ��"<<y<<endl;
}
bool check(string str)
{
	for(int i = 0;i<str.length();i++)
		if(str[i]>'9' || str[i]<'0' &&(str[i]!='.'))
			return false;
	return true;
}
void get(float &x,float &y)
{
	cout<<"������x����ֵ��";
	string str1;
	cin>>str1;
	while(!check(str1))
	{
		cout<<"����Ĳ������֣�����������:"<<endl;
		cin>>str1;
	}
	x=atof(str1.c_str());
		
	cout<<"������y����ֵ��";
	string str2;
	cin>>str2;
	while(!check(str2))
	{
		cout<<"����Ĳ������֣�����������:"<<endl;
		cin>>str2;
	}
	y=atof(str2.c_str());
}
int main (void)
{
	bool quit = false;
	float a = 0;
	float b = 0;
	int choice;
	while(!quit)
	{
		cout<<"(0)exit  (1)�趨���Ϳ�(�׺͸�)  (2)triangle  (3)rectangle  (4)swap\n";
		cin>>choice;
		system("cls");
		switch(choice)
		{
		case 0:quit = true;
			break;
		case 1:cout<<"�趨���Ϳ�(�׺͸�)֮ǰ��"<<endl;	
			p=get;
			break;
		case 2:print(a,b);
			fp=triangle;
			break;
		case 3:print(a,b);
			fp=rectangle;
			break;
		case 4:cout<<"�������Ϳ�(�׺͸�)֮ǰ"<<endl;
			p=SWAP;//C++ ��׼�����ռ��а���swap�������ʽ�swap��ΪSWAP
			break;
		default:quit = true;
			break;
		}
		if(choice==1 || choice==4)
		{
			print(a,b);
			p(a,b);
			cout<<"�趨���Ϳ�(�׺͸�)֮��"<<endl;
			print(a,b);
		}
		if(choice==2 || choice==3)
		{
			print(a,b);
			cout<<"���Ϊ��"<<endl;
			cout<<fp(a,b)<<endl;
		}
	}
	return 0;
}