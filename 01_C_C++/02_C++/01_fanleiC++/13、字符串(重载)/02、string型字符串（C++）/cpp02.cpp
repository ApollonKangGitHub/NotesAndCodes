/*
	string是一个类，用string定义变量，就是定义类的对象。由于string类中将许多运算符重载。
	所以在str=="字符串";中，==被重载，可以比较；
	而ch=="字符串;中，==两端类型不同，不能比较。
	即使使用strcmp(ch,"字符串")也比较方便，但是与str=="字符串"相比起来，还是不够直白明了
	运算符的重载使得string类的对象可以像普通的数据类型那样直接运算、比较等。
*/
# include<iostream>
# include<string>
using namespace std;
int main (void)
{
	string str="string型字符串";
	char ch[]="char型字符串";
	cout<<str<<endl;
	cout<<ch<<endl;
	cout<<"请输入“狗”得英文单词："<<endl;
	cin>>str;
	if(str == "dog")
		cout<<"狗："<<str<<endl<<str<<"的第一个字符是"<<str[0]<<endl;
	else
		cout<<"输入错误"<<endl;

	cout<<"请输入“猪”得英文单词："<<endl;
	cin>>ch;
	//if(ch == "pig")//ch为一个地址，地址不可能和字符串相等，故永远不会执行
	for(int i=0; i<strlen(ch); ++i)
	{
		char ch1[4]="pig";
		if(ch[i]!=ch1[i])
			break;
	}//这种方法就可以测试输入的是不是正确的单词,if(!(strcmp(ch,"pig")))中strcmp函数也有相同功能
	
	if(i==3)
		cout<<"猪："<<ch<<endl<<ch<<"的第一个字符是"<<ch[0]<<endl;
	else
		cout<<"输入错误"<<endl;

	return 0;
}