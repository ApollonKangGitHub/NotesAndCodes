# include <iostream>
using namespace std;

int main(void)
{
	unsigned int i = 0XFFFFFFFF;
	int j = 0XFFFFFFFF;
	cout << i << endl;
	cout << j << endl;

	unsigned int unsignedmin = 0X00000000;
	unsigned int unsignedmax = 0XFFFFFFFF;
	int signedmin = 0X80000000;
	int signedmax = 0X7FFFFFFF;

	cout << "无符号整型最小值为：" << unsignedmin << "\t\t\t无符号最大值为：" << unsignedmax << endl;
	cout << "有符号整型最小值为：" << signedmin << "\t\t有符号最大值为：" << signedmax << endl;

	return 0;
}