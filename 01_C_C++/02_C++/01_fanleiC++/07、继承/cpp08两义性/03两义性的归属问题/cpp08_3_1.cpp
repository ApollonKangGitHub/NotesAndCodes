/*
	2016年8月22日17:09:07
	一个子类由多个基类派生而来，而这多个基类又是一个共同的基类派生而来
	那么子类访问这个共同的基类的成员时就会产生两义性
*/
# include <iostream>
using namespace std;
class ONE
{
public:
	int num (){return 1;}
};

class TWO:public ONE
{
public:
	int num (){return 2;}
};
class THREE:public ONE
{
public:
	int num (){return 3;}
};

class FOUR:public TWO,public THREE
{
public:
	int num (){return 4;}
	int M(){return THREE::num();}
};

int main (void)
{
	FOUR NUMBER;

	cout << NUMBER.THREE::num() << endl;
	cout << NUMBER.THREE::num() << endl;
	cout << NUMBER.THREE::num() << endl;
	cout << NUMBER.THREE::num() << endl;//我们可以直接调用THREE的num函数

	cout << NUMBER.M() << endl;
	cout << NUMBER.M() << endl;
	cout << NUMBER.M() << endl;
	cout << NUMBER.M() << endl;//也可以通过FOUR的public接口函数，间接调用THREE的num函数。在多次调用时，这种间接调用的方法会显得更为简练（起码代码量少了）
	return 0;
}