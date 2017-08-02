#include<iostream>
#include<list>
using namespace std;

template <typename T>
void print(T beg, T end){
	while(beg !=end)
		cout<<*beg++<<' ';
	cout<<endl;
}
bool isodd(int d){
	return d&1;//return d%2;
}
int main(void)
{
	int a[10] = {7,1,2,2,4,4,4,5,7,7};
	list<int> li(a,a+10);
	cout<<"li:";print(li.begin(), li.end());
	li.unique();//剔除连续的重复元素
	cout<<"li:";print(li.begin(), li.end());
	li.remove(7);//删除匹配元素
	cout<<"li:";print(li.begin(), li.end());
	li.sort();//排序
	cout<<"li:";print(li.begin(), li.end());
	li.reverse();//倒序，reserve()为设置大小，注意区分
	cout<<"li:";print(li.begin(), li.end());
	li.remove_if(isodd);//删除满足奇数的元素
	cout<<"li:";print(li.begin(), li.end());

	/*插入*/
	li.push_front(12);
	li.push_back(34);
	li.insert(++++li.begin(),56);
	cout<<"li:";print(li.begin(), li.end());

	/*转移*/
	int b[5] = {1,3,5,7,9};
	list<int> li2(b,b+5);
	cout<<"li2:";print(li2.begin(), li2.end());
	li.splice(--li.end(),li2,++li2.begin(),--li2.end());
	cout<<"li:";print(li.begin(), li.end());
	cout<<"li2:";print(li2.begin(), li2.end());
	
	/*合并*/
	li.sort();
	li2.sort();
	li.merge(li2);
	cout<<"li:";print(li.begin(), li.end());
	cout<<"li2:";print(li2.begin(), li2.end());
	
	return 0;
}
