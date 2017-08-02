# include <iostream>
# include <string>
using namespace std;
int main (void)
{
	/*
		string型插入
	*/
	string str1 = "abcdefghijklmn";
	string str2 = "ABCDEFGHIJKLMN";
	cout<<str1<<'\t'<<str2<<endl;
	str1.insert(2,str2,1,4);
	//参数1为插入（str1中）的位置，参数2为提供插入字符的字符串（str2）
	//参数3为提供插入字符的字符串的起始位置(str2中)，参数4为提供的插入字符的个数(str2中)
	cout<<str1<<endl;

	/*
		string型删除
	*/
	string s("GIVE ME LOVE QUIKLY!");
	cout<<"原始字符串为："<<s<<endl;
	s.erase(2,2);//参数1为删除的起始位置，参数2为删除的字符个数
	cout<<"删除后字符串为："<<s<<endl;
	s.erase(5);//只有一个参数，表示从下标为5开始往后的字符完全删除
	cout<<"删除后字符串为："<<s<<endl;
	s.erase();//默认为0，表示从下标为0开始往后的字符完全删除，即清空
	cout<<"删除后字符串为："<<s<<endl;
	return 0;
}