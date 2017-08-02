/*
	2016年8月6日12:15:35
	new关键字的用法类似于malloc函数的用法，
	但是malloc和free为函数，而new和delete为关键字

	在C++中由于构造函数和析构函数的存在：
	对于非内部数据类型的对象而言，光用malloc/free无法满足动态对象的要求。
	对象在创建的同时要自动执行构造函数，对象在消亡之前要自动执行析构函数。
	由于malloc/free是库函数而不是运算符，不在编译器控制权限之内，
	不能够把执行构造函数和析构函数的任务强加于malloc/free。 
*/
# include <iostream>
# include <string>
# define length 10
using namespace std;

typedef struct Node
{
	short i;
	short j;
	int x;
	double z;
}NODE,PNODE;

int main (void)
{
	int i;
	int * p = new int(100);//()中可以直接加初始化的值
	double * q = new double(20.34);
	string * ps = new string(10,'p');//初始化字符串
	short * r = (short *)new NODE;
	int * s = new int[length];//创建了含有十个整型元素的数组
	cout << "指针s所占内存：" << sizeof(s) << endl << "指针s存储地址*s所占内存：" <<sizeof(*s) << endl;
	
	cout << *p << ' ' << *q << endl;
	cout << *ps << endl;
	for(i = 0;i<(sizeof(NODE)/sizeof(short));i++)
		cin >> *(r+i);
	for(i = 0;i<(sizeof(NODE)/sizeof(short));i++)
		cout << *(r+i) << ' ';

	cout << endl;
	for(i = 0;i<length;i++)
		cin >> s[i];
	for(i = 0;i<length;i++)//注意次出不可以用i<(sizeof(s)/sizeof(int))
		cout << s[i] << ' ';
	cout << endl;

	delete p;
	delete q;
	delete r;
	delete ps;
	delete []s;//数组内存释放使必须为delete []数组名

	return 0;
}