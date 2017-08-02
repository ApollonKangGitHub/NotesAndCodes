/*
	string str[5];
	和cahr ch[5][];
	类似都是一个二维字符串数组。只不过str的五个字符串都可以自行调节长度，
	而ch的五个字符串长度一旦确定就不可以更改。
 */
# include <iostream>
# include <string>

using namespace std;
//string也是一个类，故而string与结构体和类都是基本相同的，可以作为参数和返回值类型
string show(const string p)
{
	cout<<p<<endl;
	return p;
}
/*
//和string show(const string p)效果是一样的
const string & show(const string & p)
{
	cout<<p<<endl;
	return p;
}
*/

void show_strch(const string str[],int n)
{
	system("cls");
	for(int i=0;i<n;++i)
	{
		cout<<"第"<<i+1<<"个字符串:"<<endl;
		cout<<str[i]<<endl;
	}
}
int main (void)
{
	const int LEN = 5;
	/*传递string对象，且返回string对象或引用*/
	string str = "hello world";
	string str1 = show(str);
	cout<<str<<endl;

	/*传递string对象数组*/
	string str2[LEN];
	for(int i=0;i<LEN;++i)
	{
		cout<<"第"<<i+1<<"个字符串:"<<endl;
		cin>>str2[i];
	}
	show_strch(str2,LEN);
	return 0;
}