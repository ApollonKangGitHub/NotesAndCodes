/*
	C语言:strchr(char型字符串,字符);//找到的是字符在字符串中第一次的出现位置的地址，没找到返回空
	C++:
	find()返回值为该字符在字符串中的位置，没找到返回string::npos,常量string::npos在不同平台中值不同，但是都不可以作为下标
	
	find_first_not_of(字符x);		//查找第一个与字符x不相等的字符位置下标
	find_first_of(字符x);			//查找第一个与字符x相等的字符位置下标
	find_last_not_of(字符x);		//查找最后一个与字符x不相等的字符位置下标
	find_last_of(字符x);			//查找最后一个与字符x相等的字符位置下标
	rfind(字符x);					//r为reverse的缩写，意为反向逆向，rfind则为逆向查找第一个相等的字符，返回该下标
	X_find_X函数没找到的返回值都是常量string::npos
	

	上面六个find函数都可以加第二个参数n，表示在该规则下，从下标为n即第n+1个字符开始查找或者查找到下标为n即第n+1个字符截止

	其中find()、rfind()、find_first_of()、find_last_of()第二个参数n都表示查找的起始位置
	find_first_not_of()、find_last_not_of()第二个参数n都表示查找的截止位置

	如：str.rfind('a',6);表示在str字符串中，从第七个元素开始反向查找第一个‘a’字符，并返回该位置下标
	又如：str.find_last_not_of('k',4);表示在str字符串中，查找到第5五个字符截止，最后一个不是‘k’的字符，返回其位置下标
*/
# include<iostream>
# include<string>
using namespace std;
int main (void)
{
	/*
		char型字符查找
	*/
	char ch[15];
	char *p,c='w';
	strcpy(ch,"hello world");
	p = strchr(ch,c);//返回找到的字符地址
	if(p)
		cout<<"字符"<<c<<"位于第"<<p-ch+1<<endl;//p相对于ch的偏移量
	else
		cout<<"没有找到！"<<endl;

	/*
		string型字符查找
	*/
	string str = "welcome C++ plus";
	int point = str.find('w',0);//0代表查找的起始位置下标
	if(point-string::npos)
		cout<<"字符"<<"w"<<"位于第"<<point+1<<endl;
	else
		cout<<"没有找到！"<<endl;
	int pos = str.find_first_not_of('e');
	if(pos-string::npos)
		cout<<"与字符e第一个不相等的字符位于第"<<pos+1<<endl;
	else
		cout<<"没有找到！"<<endl;

	pos = str.rfind('e',12);
	if(pos-string::npos)
		cout<<pos+1<<endl;
	else
		cout<<"没有找到！"<<endl;

	pos = str.find_last_of('e',4);
	if(pos-string::npos)
		cout<<pos+1<<endl;
	else
		cout<<"没有找到！"<<endl;

	return 0;
}