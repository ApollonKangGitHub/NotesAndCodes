/*
	string类重载了相加运算符（+）
	strcat()strlen()、size()、length()函数的使用
*/
# include<iostream>
# include<string>
using namespace std;

int main (void)
{
	/*
		char类型字符串合并（相加）
	*/
	char ch1[38] = "--What's your name";//若不定义为ch1[38]一个大的空间，系统会根据初始值自动为ch1分配sizeof(ch1)=17字节长度，合并时会使程序崩溃
	cout<<"strlen(ch1):"<<strlen(ch1)<<'\t'<<"sizeof(ch1):"<<sizeof(ch1)<<endl;
	char ch2[] = "--My name is Jack";
	cout<<ch1<<endl<<ch2<<endl;
	strcat(ch1,ch2);
	cout<<ch1<<endl;
	cout<<"strlen(ch1):"<<strlen(ch1)<<'\t'<<"sizeof(ch1):"<<sizeof(ch1)<<endl<<endl;
	/*
		string类型字符串合并（相加）
	*/
	string str1 = "--How old are you?";//虽然没有指定字符串长度，但是string对象可以根据对象长度改变自行改变
	string str2 = "--I'm thirteen years old!";
	
	//size()和strlen()、length()都是计算'\0'之前的字符串长度，strlen()为C语言函数，而strlen()、length()为C++函数
	//那么为何C++string类中会有两个功能一样的函数strlen()和length()，是由于length()为早期的string成员，而size是后期为了兼容STL加进去的成员
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