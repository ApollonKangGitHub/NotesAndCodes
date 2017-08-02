/*
	string类重载了赋值运算符（=）
	两个函数的用法：
	strcpy(ch1,ch2);
	str1.assign(str2,h,l);
*/
# include<iostream>
# include<string>
using namespace std;

int main (void)
{
	/*
		C语言的字符串赋值
	*/
	char ch1[] = "give me";
	char ch2[] = "a cup";
	cout<<ch1<<endl;
	//ch1 = ch2;//错误的赋值写法，ch2不可以直接赋给ch1
	*ch1 = *ch2;//相当于ch1[0]=ch2[0]，只改变了字符串数组的第一个字符
	cout<<ch1<<endl;
	strcpy(ch1,"hello!");//拷贝的字符串长度不能大于ch1的内存长度
	cout<<ch1<<endl;
	strcpy(ch1,ch2);
	cout<<ch1<<endl<<endl;

	/*
		C++字符串赋值
	*/
	string str1 = "GIVE ME";
	string str2 = "A CUP";
	cout<<str1<<endl;
	cout<<str2<<endl;
	str1=str2;//str2可以直接赋给str1
	cout<<str1<<endl;
	//*str1=*str2;//不可以这样写
	cout<<str1<<endl;

	str1.assign(str2,0,3);//assign()函数将str2中,从下标为0的元素取3个字符赋给str1
	cout<<str1<<endl;


	return 0;
}