# include <iostream>
using namespace std;
class A
{
public:
	virtual int get(){return 1;}
	//int get(){return 1;}
};
class B:public A
{
public:
	int get (){return 2;}
};
int main (void)
{
	while(1)
	{
		cout << "(1)父类(2)子类(3)退出：";
		int choice;
		bool quit = false;
		A * p;//只有当指针和virtual同时满足才能实现动态联编
		A p1;//只满足virtual而用普通对象调用无法实现动态联编
		cin >> choice;
		
		switch(choice)
		{
		case 1:p = new A;
			p1 = A();
			break;
		case 2:p = new B;
			p1 = B();
			break;
		case 3:quit = true;
			break;
		default:cout<<"请输入1、2或者3：";
			break;
		}
		if(quit == true)
		{
			break;
		}
		cout << p->get() << "\t" << p1.get() << endl;
	}
	return 0;
}