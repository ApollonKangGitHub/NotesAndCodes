# include <iostream>
# include <string>
using namespace std;

//函数指针，可以为函数指针赋函数名（函数名也是一个指针）
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
	cout<<"长为(底)："<<x<<"\t宽(高)为："<<y<<endl;
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
	cout<<"请输入x的新值：";
	string str1;
	cin>>str1;
	while(!check(str1))
	{
		cout<<"输入的不是数字，请重新输入:"<<endl;
		cin>>str1;
	}
	x=atof(str1.c_str());
		
	cout<<"请输入y的新值：";
	string str2;
	cin>>str2;
	while(!check(str2))
	{
		cout<<"输入的不是数字，请重新输入:"<<endl;
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
		cout<<"(0)exit  (1)设定长和宽(底和高)  (2)triangle  (3)rectangle  (4)swap\n";
		cin>>choice;
		system("cls");
		switch(choice)
		{
		case 0:quit = true;
			break;
		case 1:cout<<"设定长和宽(底和高)之前："<<endl;	
			p=get;
			break;
		case 2:print(a,b);
			fp=triangle;
			break;
		case 3:print(a,b);
			fp=rectangle;
			break;
		case 4:cout<<"交换长和宽(底和高)之前"<<endl;
			p=SWAP;//C++ 标准命名空间中包含swap函数，故将swap改为SWAP
			break;
		default:quit = true;
			break;
		}
		if(choice==1 || choice==4)
		{
			print(a,b);
			p(a,b);
			cout<<"设定长和宽(底和高)之后："<<endl;
			print(a,b);
		}
		if(choice==2 || choice==3)
		{
			print(a,b);
			cout<<"面积为："<<endl;
			cout<<fp(a,b)<<endl;
		}
	}
	return 0;
}