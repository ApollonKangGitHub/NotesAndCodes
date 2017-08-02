/*
	2016年8月22日11:22:39
	所有结果测试都是在公有派生的前提下即class SON:public FATHER
*/
# include <iostream>
using namespace std;

class FATHER
{
protected:		
	void money(){cout << "父亲的钱财" << endl;}//父亲的钱财
public:
	void room(){cout << "父亲的房子" << endl;}//父亲的房子
private:
	void secret(){cout << "父亲的秘密" << endl;}//父亲的秘密
};

class SON:public FATHER//公有派生
{
private:

public:
	void mother(){money();}
	//void mother_grand(){secret();}

};

int main (void)
{
	SON Mike;
	cout<<"儿子Mike可以享用：" << endl;
	Mike.room();
	//Mike.money();
	Mike.mother();//父类的保护成员（钱财）不可以直接访问，必须通过子类中的公有接口（母亲）来访问
	//Mike.mother_grand();//父亲的私有成员（秘密），儿子不可以访问。即使通过子类中的公有接口（母亲或祖母祖父）也不可以。
	return 0;
}