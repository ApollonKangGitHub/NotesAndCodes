# include <iostream>
//using namespace std;//该句将std空间内所有函数都释放出来
using std::cout;
using std::cin;
using std::endl;
//上面三行只将cout，sin，endl释放出来
namespace kangruojin
{
	float i = 3.8f;//f是将c++下默认的浮点类型double型显式声明为float型
	float j = 9.6f;//若果不加f，会出现警告warning C4305: 'initializing' : truncation from 'const double' to 'float'，但不影响结果
	int k = 10;
};

int main (void)
{
	cout << "Hello everyone!,Please input i j k:" <<endl;
	int i, j;
	float k;
	cin >> i >> j >> k;
	cout << "i = " << i << endl << "j = " << j << endl << "k = " << k << endl ;
	cout << "i = " << kangruojin::i << endl << "j = " << kangruojin::j << endl << "k = " << kangruojin::k << endl ;

	return 0;
}