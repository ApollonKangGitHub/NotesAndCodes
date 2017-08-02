/*
**	两种方法的区别：
**  方法一为成员变量的赋值
**  方法二为成员变量的初始化
**  所以在成员变量定义为const时赋值不能进行（方法一错误是没初始化引发的，而不是赋值所引发。但是赋值依然是不能操作的），而初始化可以
*/
# include <iostream>
using namespace std;
class rectangle
{
public:
//	rectangle(int l, int w)
//	{
//		cout << "构造函数运行中..." << endl;
//		length = l; width = w; 
//		cout << "长方形的面积为：" << length * width << endl;
//	}//初始化的方法一(实质为赋值而没有初始化)

	//rectangle():length(5),width(12){cout << "构造函数运行中..." << endl << "长方形的面积为：" << length * width << endl;}//初始化的方法二
	rectangle(int x, int y, int z):length(x),width(y),higth(z){cout << "构造函数运行中..." << endl << "长方形的面积为：" << length * width << endl;}//也是初始化

	~rectangle(){cout << "析构函数运行中..." << endl;}
private:
	//int length;
	//int width;
	//int higth;
	const int length;
	int & width;//引用和const一样必须初始化，且初始化类型必须匹配
	const int higth;
};
int main (void)
{
	rectangle a(2,7,9);

	return 0;
}