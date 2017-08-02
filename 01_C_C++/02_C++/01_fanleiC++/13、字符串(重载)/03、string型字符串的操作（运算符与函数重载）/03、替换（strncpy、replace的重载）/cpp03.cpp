/*
	strncpy(ch1,ch2,n);的使用:用ch2的前n个字符替换ch1的前三个字符
	

	replace()函数的替换过程其实是删除与插入的过程，先按起始位置和个数删除主字符串字符
	再按次字符串的起始位置和个数向猪字符串中插入字符

	replace()重载函数的第三种形式（五个参数）：
	basic_string&replace(size_type index1,size_type num1,const basic_string&str,size_type index2,size_type num2)
	调用如下：
	str1(0,2,str2,1,3);
	//参数1：主符串的起始位置下标
	//参数2：起始位置开始的替换个数
	//参数3：提供替换字符的字符串
	//参数4：提供替换字符的字符串取字符的起始位置
	//参数5：提供的字符个数
	
	replace()重载函数的第五种形式（四个参数）：
	basic_string&replace(size_type index,size_type num1,size_type num2，char ch)
	//参数1：主符串的起始位置下标
	//参数2：起始位置开始的替换个数
	//参数3：提供的字符个数（由于提供的是一个字符，当参数大于1时，将该字符复制多次即可）
	//参数4：提供替换字符的char型字符变量名
	//若参数2大于参数3，在替换范围内但未被替换的自动删除，被替换字符串不需替换的字符向前移
	//若参数2小于参数3，就超出覆盖位置，被替换字符串不需替换的字符向后错位。
*/
# include <iostream>
# include <string>
using namespace std;
int main (void)
{
	char ch1[] = "abcdef";
	char ch2[] = "ABCDEF";
	strncpy(ch1,ch2,3);
	cout<<ch1<<endl;

	string str1 = "QWERT";
	string str2 = "ZXCVB";
	cout<<str1<<"\t"<<str2<<endl;
	str1.replace(0,2,str2,2,3);
	//str2的从下标为2开始的三个字符替换str1，str1的从下标为0的字符开始的两个字符被覆盖，所以str1原有的第三个字符成为了第四个
	cout<<str1<<endl;

	cout<<str1<<"\t"<<ch2<<endl;
	str1.replace(1,4,ch2,1,3);//replace()重载函数也支持cahr类型的字符串,但是char类型字符串无法作为被替换字符串
	cout<<str1<<endl;

	char ch='P';
	cout<<str1<<"\t"<<ch<<endl;
	str1.replace(1,4,8,ch);
	cout<<str1<<endl;
	return 0;
}