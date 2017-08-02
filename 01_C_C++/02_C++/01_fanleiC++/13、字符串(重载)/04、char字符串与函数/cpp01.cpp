# include<iostream>
using namespace std;
int get(const char *p);
char * get_ch(char * str);
int main(void)
{
	/*字符串与数组*/
	char ch[15]="hello world!";//字符串数组，可读可写可改
	char *p="Mike";//未命名字符串，但有指针存储地址，可读不可改
	"study";//未命名字符串，存放在文字常量区

	int length_ch = get(ch);
	int length_p = get(p);
	cout<<"ch字符串长度："<<length_ch<<endl<<"p指向字符串长度："<<length_p<<endl;

	ch[5] = 50;//可改,2的ASCII码为50
	cout<<ch<<endl;//可读
	cout<<*(p+5)<<endl;//只可读

	/*字符串的返回*/
	char c[10];
	char * ch1;
	cout<<"请输入您的名字："<<endl;
	cin>>c;
	ch1 = get_ch(c);//delete []ch1就是delete p，若不加括号，删除的只是数组第一个字符的空间
	cout<<"您的名字是："<<ch1<<endl;
	delete []ch1;
	ch1 = get_ch(p);//传递的是未命名的字符串的首地址p
	cout<<"您的名字是："<<ch1<<endl;
	delete []ch1;
	ch1 = get_ch("Jack");//传递的是未命名的字符串
	cout<<"您的名字是："<<ch1<<endl;
	delete []ch1;

	return 0;
}

/*计算字符串长度*/
int get(const char *p)
{
	int count = 0;
	while(*p)
	{
		++count;
		++p;
	}
	return count;
}
/*没有实际意义，但是说明了函数如何返回char字符串:返回char型字符串的首字符地址即可*/
char * get_ch(char * str)
{
	char *p = new char[strlen(str)+1];
	strcpy(p,str);
	cout<<p;
	return p;
}