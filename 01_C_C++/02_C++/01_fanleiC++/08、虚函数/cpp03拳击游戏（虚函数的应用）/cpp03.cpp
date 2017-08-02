/*
注意：
	一个类中的函数被说明为虚函数，在派生类中若有同名函数覆盖了该虚函数
	那么派生类中的该同名函数也是个虚函数，不过我们可以直接声明该派生类中的同名函数为虚函数显得更清晰
*/
# include <iostream>
using namespace std;
class poser
{
public:
	virtual void beat()const{cout << "一般选手一拳的力量为260磅\n";}
protected:
	int age;
};
class Ali:public poser
{
	void beat()const{cout << "Ali选手一拳的力量为420磅\n";}//也为虚函数
	//virtual void beat()const{cout << "Ali选手一拳的力量为420磅\n";}两个函数是一样的
};
class Lewis:public poser
{
	void beat()const{cout << "Lewis选手一拳的力量为480磅\n";}//也为虚函数
};
class Tyson:public poser
{
	void beat()const{cout << "Tyson选手一拳的力量为500磅\n";}//也为虚函数
};
class Holy:public poser
{
	void beat()const{cout << "Holy选手一拳的力量为400磅\n";}//也为虚函数
};

int main (void)
{
	poser * p[5];//定义了指针数组，数组元素有五个，即五个指针。用指针数组来接收这五个指针
	poser * pi;
	int choice, i;
	for(i = 0; i < 5; ++i)
	{
		cout << "(1)阿里  (2)刘易斯  (3)泰森  (4)霍利菲尔德:\n";
		cin >> choice;
		switch(choice)
		{
		case 1:
			pi = new Ali;
			break;
		case 2:
			pi = new Lewis;
			break;
		case 3:
			pi = new Tyson;
			break;
		case 4:
			pi = new Holy;
			break;
		default:
			pi = new poser;
			break;
		}
		p[i] = pi;
		p[i]->beat();//通过指针调用指针的指向的beat()函数
		//不同的poser，相同的动作（调用相同的函数），产生不同的效果
	}
	return 0;
}