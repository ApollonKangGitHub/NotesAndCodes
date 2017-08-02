/*
	2016年8月5日17:36:04
	测试指针变量的地址
*/
# include <iostream>
using namespace std;

int main (void)
{
	int i = 10;
	int j = 20;
	int k = 30;
	double m = 40.4;
	double n = 50.5;

	int * p = &i;
	int * q = &j;
	int * r = &k;
	double * s = &m;
	double * t = &n;

	cout << p << endl << q << endl << r << endl << s << endl << t << endl;
	cout << &p << endl << &q << endl << &r << endl << &s << endl << &t << endl;

	return 0;
}

/*
	经常测试结果如下：
		0018FF3C
		0018FF38
		0018FF34
		0018FF2C
		0018FF24
		0018FF20
		0018FF1C
		0018FF18
		0018FF14
		0018FF10
		Press any key to continue
	发现指针变量和普通变量的地址类似，按顺序从内存高字节到底字节分配，按低字节到高字节使用，按高字节到底字节存储
	只是无论指针类型如何，指针变量只占四个字节（32bit = 4Gb），对于4GB内存来说不会改变。因为内存地址是按8bit划分
	一个标号的，所以4个字节刚好能够表示4GB内存大小得出所有地址。
*/