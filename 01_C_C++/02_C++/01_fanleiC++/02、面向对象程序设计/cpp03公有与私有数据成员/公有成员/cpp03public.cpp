/*
	2016年8月4日12:39:49
	共有数据成员可直接调用访问并赋值
*/
# include <iostream>
using namespace std;

class Human
{
public:
	int weight;
};
int main (void)
{
	Human Tom;
	Human LiMing;

	Tom.weight = 110;
	cout<<"汤姆的体重为（kg）："<<Tom.weight<<endl;
	LiMing.weight = 120;
	cout<<"李明的体重为（kg）："<<LiMing.weight<<endl;

	return 0;
}