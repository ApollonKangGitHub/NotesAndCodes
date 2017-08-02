#include<iostream>
#include<string>
using namespace std;

void StrAttribute(void)
{
	/*
	 * 容量(capacity)
	 * 容量是当前已经申请的内存(即总的大小)
	 * 对于VS其申请的空间大小为：((str.size()/16) * 16 + 15)个，即最小15个，每溢出一次增加16个
	 * 对于VC++6.0其申请的空间大小为：((str.size()/32) * 32+ 31)个，即最小31个，每溢出一次增加32个
	*/

	string test(15,'a');
	cout << "capacity:" << test.capacity() << endl;
}

int main(void)
{
	StrAttribute();

	//system("pause");
	return 0;
}