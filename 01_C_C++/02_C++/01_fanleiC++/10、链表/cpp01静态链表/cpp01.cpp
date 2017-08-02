/*
	C++中类与结构体区别：
	class：类中的默认成员为私有成员
	struct：结构体中默认成员为公有成员
	类就是高级的结构体

	2016年9月10日13:11:11静态链表
*/
# include <iostream>
using namespace std;

class book
{
public:
	int num;
	float price;
	book * pNext;//class(或者struct)不用加
};

int main (void)
{
	book x, y, z, *pHead, *p;
	x.num = 10000;
	x.price = 14.5f;
	y.num = 20000;
	y.price = 23.4f;
	z.num = 30000;
	z.price = 45.6f;

	pHead = &x;
	x.pNext = &y;
	y.pNext = &z;
	z.pNext = NULL;

	for(p=pHead; p; p=p->pNext)
	{
		cout << "数量：" << p->num << "\t价格：" << p->price << endl;
	}

	return 0;
}