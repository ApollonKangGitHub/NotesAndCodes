# include <iostream>
# include <string>
using namespace std;
int main (void)
{
	/*char型向char型字符串提供拷贝字符*/
	char ch1[15] = "abcdefghijklmn";
	char ch2[] = "1234567890";
	cout<<"拷贝前ch1:"<<ch1<<"\tch2:"<<ch2<<endl;
	memmove(ch1,ch2,10);//ch2的前10个字符拷贝覆盖ch1的前十个字符
	cout<<"拷贝后ch1:"<<ch1<<endl;
	cout<<"拷贝前ch1:"<<ch1<<"\tch2:"<<ch2<<endl;
	strcpy(ch1,ch2);
	cout<<"拷贝后ch1:"<<ch1<<endl;

	/*string型向char型提供拷贝字符，函数为copy*/
	string str = "abcdefghijklmn";
	cout<<"拷贝前:"<<"ch2:"<<ch2<<"str:"<<str<<endl;
	int n = str.copy(ch2,5,2);//返回值为拷贝的个数，即第二个参数（第二个参数不能大于ch2的内存范围）
	//第二个参数为str提供拷贝的个数，第三个参数为str向ch2拷贝字符的起始下标。ch2的前五个字符被str的第3~8个字符覆盖
	cout<<"拷贝了:"<<n<<"个字符"<<endl;
	cout<<"拷贝后:"<<"ch2:"<<ch2<<"str:"<<str<<endl;

	return 0;
}