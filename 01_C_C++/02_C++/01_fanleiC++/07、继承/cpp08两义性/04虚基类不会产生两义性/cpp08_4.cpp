# include <iostream>
using namespace std;
class Human
{
public:
	void stand(){cout << "人类能够直立行走" << endl;}
};

class Father:virtual public Human//关键字virtual说明为虚基类，stand并不直接属于Father，唯一直属Human
{
};
class Mother:virtual public Human//关键字virtual说明为虚基类，stand并不直接属于Mother，唯一直属Human
{
};

class Son : public Father, public Mother
{
};

int main (void)
{
	Son Tom;
	Tom.stand();//直接调用唯一直属Human的stand
	Tom.Mother::stand();

	return 0;
}