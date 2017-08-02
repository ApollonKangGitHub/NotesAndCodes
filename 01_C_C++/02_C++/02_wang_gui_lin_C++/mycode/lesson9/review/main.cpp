#include <iostream>
#include <typeinfo>

using namespace std;

class A
{
public:
    A(){
        cout<<"A.this:"<<this<<endl;//A类型的this，只能看到a
        this->a;
        //this->b;
        //this->c;
        cout<<"typeid(this).name():"<<typeid(this).name()<<endl;
    }
    int a;
};
class B:public A
{
public:
    B(){
        cout<<"B.this:"<<this<<endl;//B类型的this，可以看到a(继承过来的)和b
        this->a;
        this->b;
        //this->c;
        cout<<"typeid(this).name():"<<typeid(this).name()<<endl;
    }
    int b;
};
class C:public B
{
public:
    C(){
        cout<<"C.this:"<<this<<endl;//C类型放入this，可以看到ab(继承过来的)和c
        cout<<"&a:"<<&a<<endl;
        cout<<"&b:"<<&b<<endl;
        cout<<"&c:"<<&c<<endl;
        this->a;
        this->b;
        this->c;
        cout<<"typeid(this).name():"<<typeid(this).name()<<endl;
    }
    int c;
};
int main()
{
    C c;
    A *p = &c;

    return 0;
}

