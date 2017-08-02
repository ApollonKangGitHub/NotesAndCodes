# include<iostream>
using namespace std;
class String
{
public:
	String();//不带参数的构造函数
	String(const char * const ch);//带参数构造函数
	~String(){cout<<"析构函数执行中..."<<endl;/*delete []str;*/len=0;}//避免内存泄漏
	int get_len()const{return len;}//获取字符串长度
	const char * get_str()const{return str;}//返回字符串首地址，以作输出之用
	friend ostream & operator<<(ostream & o,const String & str)//重载输出运算符
	{
		o<<str.str;
		return o;
	}
	friend istream & operator>>(istream & o,String & str)//重载输入运算符
	{
		o>>str.str;
		return o;
	}
	/*C++规定二元运算符重载函数作为成员函数时只能带一个参数,所以将其定义为不是成员函数的友元函数即可*/
	friend bool operator<(const String & str1,const String & str2)//重载的<比较运算符函数
	{
		if(strcmp(str1.str,str2.str)<0)
			return true;
		return false;
	}
	friend bool operator==(const String & str1,const String & str2)//重载的=比较运算符函数
	{
		if(strcmp(str1.str,str2.str)==0)
			return true;
		return false;//
	}
	friend bool operator>(const String & str1,const String & str2)//重载的>比较运算符函数
	{
		if(strcmp(str1.str,str2.str)>0)
			return true;
		return false;
	}
	char & operator[](unsigned short int length);//可操作非常量对象的重载[]运算符函数
	char operator[](unsigned short int length)const;//可操作常量对象的重载[]运算符函数
	String(const String & rs);//重写复制构造函数
	String & operator=(const String &s);//重载赋值运算符
	String operator+(const String & s);//重载的相加运算符函数
	void operator+=(const String & s);//重载的+=运算符函数
private:
	int len;
	char*str;
	String(unsigned short int);//带整型参数的构造函数，只能由重载运算符函数operatot+()调用
};

String::String()//与C++自带string类拥有相同功能：可定义一个空字符串
{
	cout<<"不带参数的构造函数执行中..."<<endl;
	len = 0;
	str = new char[1];
	str[0] = '\0';
}

String::String(const char * const ch)//构造一个String型字符串，可自动分配所需空间大小
{
	cout<<"带一个char参数的构造函数执行中..."<<endl;
	len = strlen(ch);
	str = new char[len+1];
	for(int i = 0; i<len; ++i)
	{
		str[i] = ch[i];
	}
	str[len] = '\0';
}
String::String(unsigned short int length)//构造一个String型字符串，可自动分配所需空间大小
{
	cout<<"带一个int参数的构造函数执行中..."<<endl;
	len = length;
	str = new char[len+1];
	for(int i = 0; i<len; ++i)
		str[i] = '\0';
}
char &String::operator[](unsigned short int length)//重载[]运算符函数
{
	cout<<"operator[]执行中..."<<endl;
	if(length > len)
		return str[len-1];
	else
		return str[length];
}
char String::operator[](unsigned short int length)const//重载[]运算符函数
{
	cout<<"operator[]const执行中..."<<endl;
	if(length > len)
		return str[len-1];
	else
		return str[length];
}
String::String(const String&rs)//重写复制构造函数
{
	cout<<"复制构造函数执行中..."<<endl;
	len = rs.get_len();
	str = new char[len+1];
	for(int i=0; i<len; ++i)
	{
		str[i] = rs[i];//str为指针，可直接使用[];rs为对象，调用下标运算符函数后可使用[]
	}
	str[len] = '\0';
}
String &String::operator=(const String &s)
{
	cout<<"operator=()函数运行中...."<<endl;
	if(this == &s)
	{
		return *this;
	}
	delete []str;//每次重新赋值都要删除原有空间，重新分配空间
	len = s.get_len();
	str = new char[len+1];
	for(int i=0; i<len; ++i)
	{
		str[i] = s[i];
	}
	str[len] = '\0';
	return *this;
}

String String::operator+(const String & s)
{
	cout<<"operator+()函数运行中...."<<endl;
	int total = len+s.get_len();
	String temp(total);//调用带有无符号短整型参数的构造函数
	int i;
	int j;
	for(i=0;i<len;++i)
		temp[i] = str[i];//一个等式调用了三个重载函数：operator=()、operator[]()、operator[]()const
	for(j=0;j<s.get_len();++j,++i)
		temp[i] = s[j];
	return temp;//有返回值
}
void String::operator+=(const String & s)
{
	cout<<"operator+=()函数运行中...."<<endl;
	int total = len+s.get_len();
	String temp(total);//调用带有无符号短整型参数的构造函数
	int i;
	int j;
	for(i=0;i<len;++i)
		temp[i] = str[i];//一个等式调用了三个重载函数：operator=()、operator[]()、operator[]()const
	for(j=0;j<s.get_len();++j,++i)
		temp[i] = s[j];
	*this = temp;//不需返回值
}
int main (void)
{
	/*
	String s;
	cout<<"s:"<<s.get_str()<<"\t占有字节数为："<<s.get_len()<<endl;
	String s1("study");
	cout<<"s1:"<<s1.get_str()<<"\t占有字节数为："<<s1.get_len()<<endl;
	char * temp = "help me";
	String s3(temp);
	cout<<"s3:"<<s3.get_str()<<"\t占有字节数为："<<s3.get_len()<<endl;

	String s4;//调用复制构造函数
	String s2;
	s1 = s3 = s4 = s2;//调用重载的赋值运算符函数
	
	/*调用get_str()函数输出*/
	/*
	cout<<"s1:"<<s1.get_str()<<"\t占有字节数为："<<s1.get_len()<<endl;
	cout<<"s3:"<<s3.get_str()<<"\t占有字节数为："<<s3.get_len()<<endl;
	cout<<"s4:"<<s4.get_str()<<"\t占有字节数为："<<s4.get_len()<<endl;
	*/
	/*调用重载的输出运算符函数直接输出*/
	/*
	cout<<"s1:"<<s1<<"\t占有字节数为："<<s1.get_len()<<endl;
	cout<<"s3:"<<s3<<"\t占有字节数为："<<s3.get_len()<<endl;
	cout<<"s4:"<<s4<<"\t占有字节数为："<<s4.get_len()<<endl;
	*/
	String si;
	cin>>si;//调用重载的输入运算符函数直接输入，暂时存在Bug(析构函数的delete倒置)
	cout<<si<<endl;//调用重载的输出运算符函数直接输出
	/*
	String s5 = "Jack",s6 = "Mike";
	String s7 = "Kate";
	bool check1 = s5=="Jack";
	//先调用带一个参数的构造函数，将未命名的char字符串转化为String型字符串。
	//再调用重载的比较运算符operator==()函数对两个String型字符串比较
	cout<<"s5==“Jack”:"<<check1<<endl;
	
	s5+=s6;
	cout<<"s5+=s6:"<<s5<<endl;
	s5=s6+s7;
	cout<<"s5=s6+s7:"<<s5<<endl;
	*/
	return 0;
}






























