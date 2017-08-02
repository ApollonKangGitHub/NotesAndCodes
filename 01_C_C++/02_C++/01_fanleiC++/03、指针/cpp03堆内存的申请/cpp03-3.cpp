/*
	2016年8月6日13:39:17
*/
# include <iostream>
using namespace std;

int main (void)
{
	int * p;
	p = new int ;
	delete p;//注意当你不想再用p指向的那一块比内存（或许因为那块内存过小），而想让p指向另一块内存时。
			//就必须先释放p以前指向的内存空间再申请新的内存。否则会造成第一块内存泄露。
	p = (int *)new double;

	return 0;
}