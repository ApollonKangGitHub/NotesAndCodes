#include<iostream>

using namespace std;

template <typename T>
void print(T &a){
	cout<<a<<" ";
}
template <typename T>
void print(const T *p){//模板的重载
	print(*p);
}
template <typename T, int N>
/*用于数组的模板特殊化：偏特化*/
void print(T (&a)[N]){//一维数组调用一次，多维数组就会调用多次(因为多维数组的元素也是数组)
	for(int i = 0; i<N; i++)
		print(a[i]);
	cout<<endl;
}
template <>
void print(const char * s){//用于C风格字符串的特殊化:全特化
	cout<<s<<endl;
}
int main(void)
{
	int x = 123;
	int a[5] = {1,2,3,4,5};
	int b[3][2] = {11,22,33,44,55,66};

	print(x);
	print(&x);
	cout<<endl;
	print(a);
	cout<<endl;
	print(b);
	//不加最后一个模板时，默认会调用第二个模板，打印H，但是加了最后一个就调用最后一个
	print("Hello");//引号引起来的是const char*类型字符串数组

	return 0;
}
