/*
	2016年8月22日12:12:18
	私有派生与公有派生的异同点：
	
	同：
		无论是公有派生还是私有派生都不可以访问父类的私有成员，而父类的保护成员与公有成员都可以访问
	异：
		公有派生只有访问父类保护成员时才需要子类中添加公有接口
		私有派生访问父类保护成员与公有成员都得在子类中添加公有接口
*/
# include <iostream>
using namespace std;

class FATHER
{
protected:
	void money(){cout << "父亲的钱财我可以使用!" << endl;}
public:
	void room(){cout << "父亲大房子我可以使用!" << endl;}
};
class SON:private FATHER//私有派生，很少用到
{
public:
	void mother_room(){room();}
	void nother_money(){money();}
};
int main (void)
{
	SON Huni;
	//Huni.room();//不可以直接访问
	Huni.mother_room();//Huni是私有派生（私生子），要想访问父亲的成员必须通过自己的公有接口（自己的“母亲”）
	//Huni.money();
	Huni.nother_money();
	
	return 0;
}