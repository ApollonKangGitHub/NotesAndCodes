/*
	>>引用就是别名，&虽为取地址符也为引用运算符
	>>应用变量必须初始化,挂到某一个变量的地址上。而且已挂好的地址不能再改变。
	>>修改引用型变量与普通变量中的任意一个的值都会改变另外一个
*/
# include <iostream>
using namespace std;

int main ()
{
	int i = 4;
	int j = 5;	
	int &ir = i;
	int &jr = j;

	cout << i << '\t' << ir <<endl;
	cout << j << '\t' << jr <<endl;

	ir = 40;
	jr = 50;
	cout << i << '\t' << ir <<endl;
	cout << j << '\t' << jr <<endl;

	cout << &i << '\t' << &ir << endl;
	cout << &j << '\t' << &jr << endl;

	ir = j;//ir的值改变为j的值，i随之改变。但是ir的地址依旧是i的地址，不会发生改变
	cout << i << '\t' << ir <<endl;
	cout << j << '\t' << jr <<endl;
	cout << &i << '\t' << &ir << endl;
	cout << &j << '\t' << &jr << endl;

	return 0;

}