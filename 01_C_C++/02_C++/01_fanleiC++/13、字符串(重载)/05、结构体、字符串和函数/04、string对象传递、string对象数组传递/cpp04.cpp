/*
	string str[5];
	��cahr ch[5][];
	���ƶ���һ����ά�ַ������顣ֻ����str������ַ������������е��ڳ��ȣ�
	��ch������ַ�������һ��ȷ���Ͳ����Ը��ġ�
 */
# include <iostream>
# include <string>

using namespace std;
//stringҲ��һ���࣬�ʶ�string��ṹ����඼�ǻ�����ͬ�ģ�������Ϊ�����ͷ���ֵ����
string show(const string p)
{
	cout<<p<<endl;
	return p;
}
/*
//��string show(const string p)Ч����һ����
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
		cout<<"��"<<i+1<<"���ַ���:"<<endl;
		cout<<str[i]<<endl;
	}
}
int main (void)
{
	const int LEN = 5;
	/*����string�����ҷ���string���������*/
	string str = "hello world";
	string str1 = show(str);
	cout<<str<<endl;

	/*����string��������*/
	string str2[LEN];
	for(int i=0;i<LEN;++i)
	{
		cout<<"��"<<i+1<<"���ַ���:"<<endl;
		cin>>str2[i];
	}
	show_strch(str2,LEN);
	return 0;
}