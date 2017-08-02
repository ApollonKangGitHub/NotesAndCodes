/*
	2016年8月4日12:41:13
	>>私有数据成员虽然赋值使用麻烦，但是安全性高，一般数据成员都设为私有成员
	>>如果类中没有提前说明成员是共有还是私有，默认为私有
*/
# include <iostream>
using namespace std;

class Human
{
public:
	void set_weight(int);
	int return_weight();
private:
	int weight;
};

void Human::set_weight(int x)
{
	if(x>40 && x<120)
	{
		weight = x;
	}
	else
	{
		cout<<"请输入的体重范围在40kg——120kg之间，否则默认为0。\n";
		weight = 0;
	}
}
int Human::return_weight()
{
	return weight;
}
int main (void)
{
	Human Tom;
	Human LiMing;

	Tom.set_weight(110);
	cout<<"汤姆的体重为（kg）："<<Tom.return_weight()<<endl;
	LiMing.set_weight(310);
	cout<<"李明的体重为（kg）："<<LiMing.return_weight()<<endl;

	return 0;
}