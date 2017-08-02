# include<iostream>
# include<string>
using namespace std;
int main (void)
{
	string str="455";
	if(str.empty())
		cout<<"该字符串为空！"<<endl;
	else
		cout<<"该字符串不为空！字符串为："<<str<<endl;

	/*
		C中swab(ch1,ch2,n)的指定长度(n/2)*2奇偶交换与复制结合
	*/
	char ch1[15]="ofru";
	char ch2[15]="ifev";
	cout<<"奇偶交换前："<<ch1<<"\t"<<ch2<<endl;
	swab(ch1,ch2,3);//将ch1中前(3/2)*2=2个字符奇偶位置交换后复制到ch2的前(3/2)*2=2个字符位置处，将ch2原有前两个字符覆盖。ch1不变
	cout<<"奇偶交换后："<<ch1<<"\t"<<ch2<<endl;

	/*
		C++中str1.swap(str2);函数字符串完全交换
	*/
	string str1="ofru";
	string str2="";
	cout<<"交换前："<<str1<<"\t"<<str2<<endl;
	str1.swap(str2);
	cout<<"交换后："<<str1<<"\t"<<str2<<endl;

	/*
		将string型字符串转换为char型字符串
	*/
	string str3="hello world!";
	const char*ch;
	ch=str3.c_str();
	cout<<ch<<endl;
	return 0;
}