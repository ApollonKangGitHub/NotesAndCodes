/*
	2016年8月22日12:50:56
	多重继承的使用与权限配置（设置接口函数）
*/
# include <iostream>
using namespace std;

class Father
{
public:
	void set_F(int a){high = a;}
	void print_F(){cout << "身高(CM)=" << high << endl;}
private:
	int high;
};

class Mother
{	
public:
	void set_M(int a){weight = a;}
	void print_M(){cout << "体重(KG)=" << weight << endl;}
private:
	int weight;
};

class Son:public Father,public Mother//都是公有继承
{
private:
	int age;
public:
	void set_S(int a){age = a;}
	void print_S(){print_F(),print_M(),cout<<"年龄(岁)="<< age << endl;}
};

class Daughter:private Father,public Mother//Father类私有继承，Mother类公有继承
{
private:
	int age;
public:
	void set_D(int a){age = a;}
	void print_D(){cout<<"年龄(岁)="<< age << endl;}
	void SET(int f,int m){set_F(f),set_M(m);}//接口函数
	void PRINT(){print_F(),print_M(),cout<<"年龄(岁)="<< age << endl;}//接口函数
};

int main (void)
{
	Son Mike;
	cout << "Mike:" << endl;
	Mike.set_F(175);
	Mike.set_M(60);
	Mike.set_S(20);
	Mike.print_F();
	Mike.print_M();
	cout << endl;
	Mike.print_S();

	cout << endl << "Jenny:" << endl;
	Daughter Jenny;

//	Jenny.set_F(165);//私有继承不可以调用
	Jenny.set_M(55);//公有继承可以调用
//	Jenny.print_F();//私有继承不可以调用
	Jenny.print_M();//公有继承可以调用

	cout << endl;
	Jenny.set_D(20);
	Jenny.print_D();
	cout << endl;
	Jenny.SET(165,57);
	Jenny.PRINT();

	return 0;
}