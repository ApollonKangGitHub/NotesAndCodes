/*
 *STL Generality Section：STL 共性之区间操作
 *2017/4/8 15:42:30
 * */
#include<iostream>
#include<list>
#include<algorithm>
using namespace std;

int main(void)
{
	int a[10] = {10,101,21,13,44,52,36,71,48,49};

	list<int> la(a, a+6);//区间构造函数
	sort(a,a+10);//全局sort
	//la.sort();//类对象的sort
	list<int>::iterator ite = la.begin();
	for(int i = 0; i<10; i++)
		cout<<a[i]<<"\t";
	cout<<endl;

	for(ite; ite != la.end(); ite++)
		cout<<*ite<<"\t";
	cout<<endl;
	return 0;
}
