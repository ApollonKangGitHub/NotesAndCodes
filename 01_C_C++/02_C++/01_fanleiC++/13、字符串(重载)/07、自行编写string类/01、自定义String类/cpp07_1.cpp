# include<iostream>
using namespace std;
class String
{
public:
	String();//���������Ĺ��캯��
	String(const char * const ch);//���������캯��
	~String(){cout<<"��������ִ����..."<<endl;/*delete []str;*/len=0;}//�����ڴ�й©
	int get_len()const{return len;}//��ȡ�ַ�������
	const char * get_str()const{return str;}//�����ַ����׵�ַ���������֮��
	friend ostream & operator<<(ostream & o,const String & str)//������������
	{
		o<<str.str;
		return o;
	}
	friend istream & operator>>(istream & o,String & str)//�������������
	{
		o>>str.str;
		return o;
	}
	/*C++�涨��Ԫ��������غ�����Ϊ��Ա����ʱֻ�ܴ�һ������,���Խ��䶨��Ϊ���ǳ�Ա��������Ԫ��������*/
	friend bool operator<(const String & str1,const String & str2)//���ص�<�Ƚ����������
	{
		if(strcmp(str1.str,str2.str)<0)
			return true;
		return false;
	}
	friend bool operator==(const String & str1,const String & str2)//���ص�=�Ƚ����������
	{
		if(strcmp(str1.str,str2.str)==0)
			return true;
		return false;//
	}
	friend bool operator>(const String & str1,const String & str2)//���ص�>�Ƚ����������
	{
		if(strcmp(str1.str,str2.str)>0)
			return true;
		return false;
	}
	char & operator[](unsigned short int length);//�ɲ����ǳ������������[]���������
	char operator[](unsigned short int length)const;//�ɲ����������������[]���������
	String(const String & rs);//��д���ƹ��캯��
	String & operator=(const String &s);//���ظ�ֵ�����
	String operator+(const String & s);//���ص�������������
	void operator+=(const String & s);//���ص�+=���������
private:
	int len;
	char*str;
	String(unsigned short int);//�����Ͳ����Ĺ��캯����ֻ�����������������operatot+()����
};

String::String()//��C++�Դ�string��ӵ����ͬ���ܣ��ɶ���һ�����ַ���
{
	cout<<"���������Ĺ��캯��ִ����..."<<endl;
	len = 0;
	str = new char[1];
	str[0] = '\0';
}

String::String(const char * const ch)//����һ��String���ַ��������Զ���������ռ��С
{
	cout<<"��һ��char�����Ĺ��캯��ִ����..."<<endl;
	len = strlen(ch);
	str = new char[len+1];
	for(int i = 0; i<len; ++i)
	{
		str[i] = ch[i];
	}
	str[len] = '\0';
}
String::String(unsigned short int length)//����һ��String���ַ��������Զ���������ռ��С
{
	cout<<"��һ��int�����Ĺ��캯��ִ����..."<<endl;
	len = length;
	str = new char[len+1];
	for(int i = 0; i<len; ++i)
		str[i] = '\0';
}
char &String::operator[](unsigned short int length)//����[]���������
{
	cout<<"operator[]ִ����..."<<endl;
	if(length > len)
		return str[len-1];
	else
		return str[length];
}
char String::operator[](unsigned short int length)const//����[]���������
{
	cout<<"operator[]constִ����..."<<endl;
	if(length > len)
		return str[len-1];
	else
		return str[length];
}
String::String(const String&rs)//��д���ƹ��캯��
{
	cout<<"���ƹ��캯��ִ����..."<<endl;
	len = rs.get_len();
	str = new char[len+1];
	for(int i=0; i<len; ++i)
	{
		str[i] = rs[i];//strΪָ�룬��ֱ��ʹ��[];rsΪ���󣬵����±�������������ʹ��[]
	}
	str[len] = '\0';
}
String &String::operator=(const String &s)
{
	cout<<"operator=()����������...."<<endl;
	if(this == &s)
	{
		return *this;
	}
	delete []str;//ÿ�����¸�ֵ��Ҫɾ��ԭ�пռ䣬���·���ռ�
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
	cout<<"operator+()����������...."<<endl;
	int total = len+s.get_len();
	String temp(total);//���ô����޷��Ŷ����Ͳ����Ĺ��캯��
	int i;
	int j;
	for(i=0;i<len;++i)
		temp[i] = str[i];//һ����ʽ�������������غ�����operator=()��operator[]()��operator[]()const
	for(j=0;j<s.get_len();++j,++i)
		temp[i] = s[j];
	return temp;//�з���ֵ
}
void String::operator+=(const String & s)
{
	cout<<"operator+=()����������...."<<endl;
	int total = len+s.get_len();
	String temp(total);//���ô����޷��Ŷ����Ͳ����Ĺ��캯��
	int i;
	int j;
	for(i=0;i<len;++i)
		temp[i] = str[i];//һ����ʽ�������������غ�����operator=()��operator[]()��operator[]()const
	for(j=0;j<s.get_len();++j,++i)
		temp[i] = s[j];
	*this = temp;//���践��ֵ
}
int main (void)
{
	/*
	String s;
	cout<<"s:"<<s.get_str()<<"\tռ���ֽ���Ϊ��"<<s.get_len()<<endl;
	String s1("study");
	cout<<"s1:"<<s1.get_str()<<"\tռ���ֽ���Ϊ��"<<s1.get_len()<<endl;
	char * temp = "help me";
	String s3(temp);
	cout<<"s3:"<<s3.get_str()<<"\tռ���ֽ���Ϊ��"<<s3.get_len()<<endl;

	String s4;//���ø��ƹ��캯��
	String s2;
	s1 = s3 = s4 = s2;//�������صĸ�ֵ���������
	
	/*����get_str()�������*/
	/*
	cout<<"s1:"<<s1.get_str()<<"\tռ���ֽ���Ϊ��"<<s1.get_len()<<endl;
	cout<<"s3:"<<s3.get_str()<<"\tռ���ֽ���Ϊ��"<<s3.get_len()<<endl;
	cout<<"s4:"<<s4.get_str()<<"\tռ���ֽ���Ϊ��"<<s4.get_len()<<endl;
	*/
	/*�������ص�������������ֱ�����*/
	/*
	cout<<"s1:"<<s1<<"\tռ���ֽ���Ϊ��"<<s1.get_len()<<endl;
	cout<<"s3:"<<s3<<"\tռ���ֽ���Ϊ��"<<s3.get_len()<<endl;
	cout<<"s4:"<<s4<<"\tռ���ֽ���Ϊ��"<<s4.get_len()<<endl;
	*/
	String si;
	cin>>si;//�������ص��������������ֱ�����룬��ʱ����Bug(����������delete����)
	cout<<si<<endl;//�������ص�������������ֱ�����
	/*
	String s5 = "Jack",s6 = "Mike";
	String s7 = "Kate";
	bool check1 = s5=="Jack";
	//�ȵ��ô�һ�������Ĺ��캯������δ������char�ַ���ת��ΪString���ַ�����
	//�ٵ������صıȽ������operator==()����������String���ַ����Ƚ�
	cout<<"s5==��Jack��:"<<check1<<endl;
	
	s5+=s6;
	cout<<"s5+=s6:"<<s5<<endl;
	s5=s6+s7;
	cout<<"s5=s6+s7:"<<s5<<endl;
	*/
	return 0;
}






























