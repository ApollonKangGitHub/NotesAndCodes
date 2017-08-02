/*
	对象占有内存，指针指向对象，指针拥有内存；对象还是对象，指针还是指针，内存还是内存。三者独立又相互依存
	三者的所属关系就是那么的微乎其微，玄之又玄，众妙之门。
	关键字virtual在某函数之前出现，表示该函数有多种形态，即该函数在多个不同类中都有，而且功能不一，
	那么系统在执行到有关键字virtual的函数时，就会自动判断是哪个对象调用了它，然后调用该对象所属类的同名函数，
	不再是依据指针所属关系去调用，而是根据内存占有关系去调用
*/
# include <iostream>
using namespace std;

class father
{
public:
	father(){cout << "调用父类的构造函数..." << endl;}
	~father(){cout << "调用父类的析构函数..." << endl;}
	void jump()const{cout<< "父亲可以跳五个台阶!" << endl;}
	virtual void run()const{cout<< "父亲可以跑万米!" << endl;}
};

class son : public father
{
public:
	son(){cout << "调用子类的构造函数..." << endl;}
	~son(){cout << "调用子类的析构函数..." << endl;}
	void jump()const{cout<< "儿子可以跳十个个台阶!" << endl;}
	void run()const{cout<< "儿子可以跑十万米!" << endl;}
};

int main (void)
{
	father *p = new son;
	p->jump();
	p->run();

	delete p;

	return 0;
}