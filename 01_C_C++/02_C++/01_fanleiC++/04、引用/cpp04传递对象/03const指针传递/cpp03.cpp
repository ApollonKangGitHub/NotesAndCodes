/*
	2016年8月9日15:20:20
	const指针增加程序安全性
*/
# include <iostream>
using namespace std;

class A
{
public:
	A(){cout << "执行构造函数构造一个对象。\n";}//构造函数
	A(A&){cout << "执行复制构造函数，创建该对象的一个副本。\n";}//复制构造函数
	~A(){cout << "执行析构函数,删除对象...\n";}//析构函数
	void set(int x){i = x;}
	int get()const{return i;}
private:
	int i;
};
//第一个const确保返回的one指针指向的对象（对象的所有成员）不被修改		
//第二个const确保返回的one指针不被修改
//第三个const确保传入的指针one指向的对象（对象的所有成员）不被修改
//第四个const确保传入的指针one不被修改
const A * const func (const A * const one)									
{			
	one->get();
	//one->set(10);//one指针指向的对象不可以被修改，所以会报错
	//one++;//one指针被定义成const，所以自加变化会报错
	return one;	
}
int main (void)
{
	A a;
	a.set(11);
	cout << a.get() << endl;
	//A * q = func(&a);	//返回值类型和接收类型不匹配
	const A * const p = func(&a);
	//p++;	//p指针被定义成const，所以自加变化也会报错
	cout << "p保存的地址：" << p << endl << "对象a的地址：" << &a << endl;
	//p->set(100);//同样会出错
	a.set(20);//注意const只是限制了p及通过p的指向。但并未改变a原本属性。我们不能通过p的指向来修改对象的成员，但可以通过a修改自身成员。
	cout << p->get() << endl;

	return 0;
					
}
