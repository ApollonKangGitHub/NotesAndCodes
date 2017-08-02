/*
	strcat(ch1,ch2)函数的变形strncat(ch1,ch2,n)
	C++的str1.append(str2,h,l)函数功能要强大于strncat(ch1,ch2,n)
*/
# include<iostream>
# include<string>
using namespace std;

int main (void)
{
	/*
		char类型字符串部分合并
	*/
	char ch1[38] = "--What's your name";
	char ch2[] = "--My name is Jack";
	cout<<ch1<<endl<<ch2<<endl;
	//strcat(ch1,ch2);
	strncat(ch1,ch2,10);//strncat(ch1,ch2,n);函数将ch2前n个字符复制链接到ch1后面,
	cout<<ch1<<endl<<endl;
	/*
		string类型字符串合并（相加）
	*/
	string str1 = "--How old are you?";
	string str2 = "--I'm thirteen years old!";
	cout<<str1<<endl<<str2<<endl;
	//str1 += str2;
	str1.append(str2,0,5);//append()函数将str2中,从下标为0的元素开始取5个字符复制连接到str1字符串后边
	cout<<str1<<endl;

	return 0;
}