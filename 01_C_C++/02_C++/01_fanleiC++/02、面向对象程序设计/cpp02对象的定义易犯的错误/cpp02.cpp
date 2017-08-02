/*
2016年8月4日12:31:27
*/
# include <iostream>
using namespace std;

class Human
{
public:
	int weight;
	void set_age(int x){age = x;}
	int return_age(){return age;}
private:
	int age;
};
int main (void)
{
	//Human.weight = 60;//error
	Human Tom;
	Tom.weight = 60;
	cout<<"Tom的体重为："<<Tom.weight<<endl;

	//Tom.age = 18;//error
	//cout<<"Tom的年龄为："<<Tom.age<<endl;//error
	Tom.set_age(18);
	cout<<"Tom的年龄为："<<Tom.return_age()<<endl;

	return 0;
}

/*
1、要使用关键字class声明类；
2、要使用类名来定义对象；
3、不要讲定义与声明混淆，声明是说明该类是什么；而定义则是为对象分配了一个内存；
4、访问类的成员（public公有成员）要使用.运算符；
5、使用对象名.成员名访问成员，并给数据成员（public公有成员）赋值；
6、不要混淆类和对象，不要给类赋值。
*/