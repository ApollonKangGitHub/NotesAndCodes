/*
	2016年7月29日12:46:41
	引用型变量
*/
# include <iostream>
using namespace std;

void swap(int * x, int * y);
void swap(int & x, int & y);//由于两个函数形类型不同，故可以函数重名，即支持函数重载

int main (void)
{
	cout << "请输入你要交换的数x和y:" << endl;
	int x, y;
	cin >> x >> y;
	cout << "交换之前: x = " << x << " y = " << y <<endl;
	cout << "交换之后: ";
	swap(&x,&y);

	cout << "x = " << x << " y = " << y << endl;
	cout << "交换之前: x = " << x << " y = " << y <<endl;
	cout << "交换之后: ";
	swap(x,y);

	cout << "x = " << x << " y = " << y << endl;
	return 0;
}

void swap(int * a,int * b)
{
	int temp = *a;
	*a = *b;
	*b = temp;

	return;
}
void swap(int &x, int &y)
{
	int temp = x;
	x = y;
	y = temp;

	return;
}

