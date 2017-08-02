/*
 * 派生类的析构器不重载
 * 构造器调用顺序（在存在子类、父类、其它类对象的情况下）：
 * 父类->其他类对象->子类
 * 析构器调用顺序：
 * 子类->其他类对象->父类
*/
#include <iostream>
using namespace std;
class A{
public:
    A(){cout<<"A()"<<endl;}
    ~A(){cout<<"~A()"<<endl;}
};

class B{
public:
    B(){cout<<"B()"<<endl;}
    ~B(){cout<<"~B()"<<endl;}
};
class C:public B{
public:
    C(){cout<<"C()"<<endl;}
    ~C(){cout<<"~C()"<<endl;}
private:
    A a;
};
using namespace std;

int main()
{
    C c;

    return 0;
}

