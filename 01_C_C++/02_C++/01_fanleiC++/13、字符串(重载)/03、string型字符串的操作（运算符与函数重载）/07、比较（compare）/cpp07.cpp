/*
	compare()函数可以被重载，故有多种形式
	//字符串1==字符串2返回0，字符串1<字符串2返回-1，字符串1>字符串2返回1
	//其中的小于大于比较依据是：从第一个单个字符开始比较ASCII码值，当前字符不相等则可以比较出大小，以后的不必再比较，
	//相等则比较下一个，完全相等即为0
	//若字符串1比字符串2长，字符串2所有字符与字符串1的字符对应相等，由于字符串1更长，故比较值为字符串1大于字符串2
	
	C++string的compare函数的六种重载形式：
	str1.compare(str2);
	str1.compare(ch);
	str1.compare(a1,b1,str2);
	str1.compare(a1,b2,str2,a2,b2);
	str1.compare(a1,b2,ch,a2,b2);
	str1.compare(a1,b2,ch,b2);//a2默认为0
	//ai为起始位置下标，bi为取出的字符串个数
	//返回值为0或-1或1
*/
# include<iostream>
# include<string>
using namespace std;
int main (void)
{
	string s1="455";
	string s2="45";
	char c[]="151";
	int i,j,k,l,m,n;

	i=s1.compare(s2);//重载格式1,参数为string型
	cout<<s1<<":"<<s2<<"="<<i<<endl;

	j=s1.compare(c);//重载格式2，参数为char型
	cout<<s1<<":"<<c<<"="<<j<<endl;

	k=s1.compare(0,2,s2);//重载格式3,三个参数，表示：在s1中，从下标为0的字符开始取2个字符，与s2进行比较 
	cout<<s1[0]<<s1[1]<<":"<<s2<<"="<<k<<endl;
	
	l=s1.compare(1,1,s2,0,1);//重载格式4，五个参数，表示：在s1中从下表为1的字符开始取1个字符，与s2中下标为0的字符开始取1个字符。进行比较
	cout<<s1[1]<<":"<<s2[0]<<"="<<l<<endl;
	
	m=s1.compare(1,1,c,0,1);//重载格式5,与格式4唯一的不同就是string型换为char型
	cout<<s1[1]<<":"<<c[0]<<"="<<m<<endl;

	n=s1.compare(1,1,c,1);//重载格式6，与格式5唯一的区别就是将第四个参数默认为0，第五个参数成为了第四个参数
	cout<<s1[1]<<":"<<c[0]<<"="<<n<<endl;

	return 0;
}