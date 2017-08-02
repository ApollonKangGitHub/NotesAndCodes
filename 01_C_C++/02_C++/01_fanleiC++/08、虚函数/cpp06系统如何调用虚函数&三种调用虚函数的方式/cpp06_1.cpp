# include<iostream>
using namespace std;

class father 
{
public:
	virtual void run()const{cout << "父亲可以跑万米" << endl;}
};

class son:public father
{
	virtual void run()const{cout << "儿子可以跑十万米" << endl;}
};
class daughter:public father
{
	virtual void run()const{cout << "女儿可以跑十万米" << endl;}
};
void one (father);
void two (father*);
void two (father&);

void one(father one)
{
	one.run();//对象直接调用
}
void two (father * two)
{
	two->run();//指针调用
}
void three (father & three)
{
	three.run();//引用调用
}
int main(void)
{
	father * p = NULL;
	int choice = 0;
	while(1)
	{
		bool quit = false;
		cout << "(0)quit    (1)son    (2)daughter    (3)father    " << endl;
		cin >> choice;
	
		switch(choice)
		{
		case 0:quit = true;
			break;
		case 1:p = new son;
			one(*p);//p为father *型指针，*p则为子类继承父类的所有成员，无子类的成员。且按值传参调用虚函数为静态联编
			break;
		case 2:p = new daughter;
			two(p);//按指针传参，调用虚函数，虚函数具有运行时的多态作用
			break;
		case 3:p = new father;
			three(*p);//采用引用的方式传参，调用虚函数
			break;
		default:cout<< "请输入有效选项0或1或2或3：" << endl;
			break;
		}	
		if(true == quit)	break;
	}
	return 0;
}