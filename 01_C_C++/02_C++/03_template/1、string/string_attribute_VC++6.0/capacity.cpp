#include<iostream>
#include<string>
using namespace std;

void StrAttribute(void)
{
	/*
	 * ����(capacity)
	 * �����ǵ�ǰ�Ѿ�������ڴ�(���ܵĴ�С)
	 * ����VS������Ŀռ��СΪ��((str.size()/16) * 16 + 15)��������С15����ÿ���һ������16��
	 * ����VC++6.0������Ŀռ��СΪ��((str.size()/32) * 32+ 31)��������С31����ÿ���һ������32��
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