/*
	2016年9月14日16:21:10
	公有的静态成员变量
*/
# include<iostream>
using namespace std;

class A
{
public:
	A (int num):it(num){++total;}//每构造一个对象total加1
	static int total;//声明静态成员变量
	~A(){--total;}//每析构一个对象total减1
	int get(){return it;}
	void set(int age){it = age;}
private:
	int it;
};
int A::total = 0;//定义静态成员变量
int main(void)
{
	int i;
	const int max = 5;
	A*a[max];
	for(i=0;i<max;++i,++A::total)//即使没有定义对象，类也可以直接调用静态成员变量
		cout<<A::total<<endl;
		
	for(i=0,A::total=0;i<max;++i)
		a[i] = new A(i);//定义对象
	for(i=0;i<max;++i)
	{
		cout<<"该类有"<<a[i]->total<<"个对象。"<<endl;//也可以通过类的对象来调用不属于对象的静态成员变量
		cout<<"正在删除第"<<a[i]->get()<<"个对象"<<endl;
		delete a[i];
	}

	A b(2),c(3),d(4);
	cout<<b.total<<'\t'<<c.total<<'\t'<<d.total<<endl;//total静态成员变量为全局的，不属于任何对象，且只有一个
	cout<<b.get()<<'\t'<<c.get()<<'\t'<<d.get()<<endl;//it成员变量不是全局的，每个对象都单独拥有一个
	return 0;
}