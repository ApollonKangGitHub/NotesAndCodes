/*
	//cin在遇到空格（32）和空字符（0）都会截止输入
	//而cout只会在遇到空字符时，才会截止输出

	字符串输入还有一个严重的问题：
	那就是当程序中有两个输入或者cin或者cin.get()，无所谓那个放前面，那个在后面
	都会出现当第一个的输入没有完全保存时（可能是超出长度限制，也可能是cin遇到空格）
	但无论是什么情况导致的字符串未被完全录入，第一个未被录入的的字符会直接占用下一个输入的空间
	直接结束掉第二个输入。
	eg：
	char a[4];
	char b[4];
	cin>>a;
	cin.get(b,6);
	cout<<a<<'\t'<<strlen(a)<<endl;
	cout<<b<<'\t'<<strlen(b)<<endl;
	若输入hel
	会输出：
	hel		3
	并且继续等待第二个字符串输入

	若输入hello
	会直接输出:
	hel		3
	lo		2
*/
#include<iostream>
#include<string>
using namespace std;
int main (void)
{
	char name[5]={'J','a','c','k','\0'};//这种初始化方式必须加'\0'以作为结束标志
	cout<<name<<endl;

	char women[16];
	cin.get(women,16);//输入时，自动截取前九个字符，第十个默认为'\0'。空格也算字符
	cout<<women<<endl;
	cout<<"strlen(women):"<<strlen(women)<<endl;//strlen 测的是可见字符串长度，从第一个字符到'\0'结束，不包括'\0'
	cout<<"sizeof(women):"<<sizeof(women)<<endl;//sizeof测的则是数组空间长度
	women[6]='\0';//替换为空字符后，strlen值会改变，而sizeof值不会改变
	cout<<women<<endl;
	cout<<"strlen(women):"<<strlen(women)<<endl;
	cout<<"sizeof(women):"<<sizeof(women)<<endl;

	char man[10];
	cin>>man;//空格不算字符，而为结束标志
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