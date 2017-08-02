/*
	2016年8月4日16:46:37
	内联函数及其使用
*/
# include <iostream>
using namespace std;

/*
class Human
{
public:
	inline int show();//inline关键字标志着show函数为内联函数
};

int Human::show()
{
	cout << "Hello World!" << endl;
	return 1;
}
*/

class Human
{
public:
	int Human::show()
	{
		cout << "Hello World!" << endl;
		return 1;
	}//将函数体和声明全部合起来放在类里，这边是内联函数的另一种写法
	//如果函数体定义和函数声明中，函数体不在类里，且函数声明时没有加inline关键字，则该函数不是内联函数
};


int main(void)
{
	Human Print;
	int temp = Print.show();
	cout << temp << endl;
	return 0;
}
/*
	内联函数的特点与优缺点（以下所讲被调无特殊说明均为内联函数）：

	特点：
	主调函数调用被调函数时，不需要为被调函数分配内存空间，也无需产生中断并且在中断结束时返回中断处；
	而只需将被调函数的代码copy到主调处运行即可。

	优点：
	没有过多的中断产生于返回中断的中间过程，使得程序运行效率更快。

	缺点：
	当被调代码量过大时，若多次调用被调则要多次赋值代码到主调，使得程序代码量过大。变丢失了函数调用的部分优点
*/