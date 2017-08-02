/*
 *STL Generality:STL标准模板的共性
 *2017/4/7 15:12:38
 *
 * */
#include<iostream>
#include<algorithm>
#include<deque>
using namespace std;

void traversal(string str){
	cout<<str<<'\t';
}
int main(void)
{
	deque<const char *> dcc;//deque<const char*>则是实例化后的类名
	deque<const char *>::iterator ite;
	/*插入*/
	dcc.insert(dcc.begin(), "Hello");
	dcc.insert(dcc.begin(), "CSD1212");
	dcc.insert(dcc.end(), "Welcome");
	dcc.insert(--dcc.end(), "tarena");

	/*用迭代器遍历*/
	ite = dcc.begin();
	while(ite != dcc.end())
		cout<<*ite++<<'\t';
	cout<<endl;
	/*用反向迭代器遍历*/
	deque<const char *>::reverse_iterator rite = dcc.rbegin();
	while(rite != dcc.rend())
		cout<<*rite++<<'\t';
	cout<<endl;
	/*用通用算法遍历*/
	for_each(dcc.begin(), dcc.end(), traversal);
	cout<<endl;

	/*删除*/
	cout<<"size:"<<dcc.size()<<"\tmax_size:"<<dcc.max_size()<<endl;
	while(!dcc.empty()){
		cout<<"delete:"<<*dcc.begin()<<endl;
		dcc.erase(dcc.begin());
	}

	return 0;
}
