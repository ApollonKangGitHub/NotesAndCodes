/*
	C++������ṹ������
	class�����е�Ĭ�ϳ�ԱΪ˽�г�Ա
	struct���ṹ����Ĭ�ϳ�ԱΪ���г�Ա
	����Ǹ߼��Ľṹ��

	2016��9��10��13:11:11��̬����
*/
# include <iostream>
using namespace std;

class book
{
public:
	int num;
	float price;
	book * pNext;//class(����struct)���ü�
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
		cout << "������" << p->num << "\t�۸�" << p->price << endl;
	}

	return 0;
}