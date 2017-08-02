/*
	2016年8月9日16:18:35
	引用只能初始化不能赋值；
	引用不能为空，而指针可以为空。

	int * &b = new int;语句，当内存分配失败是会返回空指针，而引用又不能为空,所以会引发系统崩溃
	int &q = *p;语句，当返回空指针，p无指向变量，q也未被赋值，也会引发系统崩溃
	所以在将引用初值赋为指针或者指针的指向成员时，必须先判断指针是否为空
*/

# include <iostream>
using namespace std;

int main (void)
{
	//int &b = new int;//error，类型不匹配
	//int * &b = new int;//正确

	int a = 5;
	int * p =&a;
	cout << *p <<endl;

	if(p)//p不为空
	{
		int &q = *p;//q是p指向单元所属的变量的别名
		int * &r = p;//r是指针p的别名,p不为空才可以赋给引用
	
		q = 10;
		cout << *p << '\t' << q << '\t'  << *r <<endl;
		* r = 20;
		cout << *p << '\t' << q << '\t'  << *r <<endl;
		* p = 30;
		cout << *p << '\t' << q << '\t'  << *r <<endl;
		}
	return 0;
}
/*
		//r和q只在if(){}里起作用，所以后面赋值与输出语句若放到if(){}外，则会报错
		
		定义A;
		if(可以使用A)
		{
		可以使用A
		}
		可以使用A

		if()
		{
		定义B;
		可以使用B
		}
		不可以使用B

//即A定义在if之前，可以再if语句内使用，B定义在if语句内，则B不可以超出if范围使用
*/