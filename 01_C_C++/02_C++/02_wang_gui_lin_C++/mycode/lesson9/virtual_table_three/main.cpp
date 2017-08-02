/*
 * 虚表的有效时间
*/
#include <iostream>

using namespace std;
class A
{
public:
    A(){
        this->func();//此时虚表还未建立，必定调用A::func()
    }
    virtual void func(){
        cout<<"AAAAAAAAAA"<<endl;
    }
    void foo(){
        this->func();//虚表已建立，B的对象也没有销毁，则调用B::func()
    }
    ~A(){
        this->func();//此时B类对象已经销毁，必定调用A::func()
    }
};
class B:public A
{
public:
    void func()
    {
        cout<<"BBBBBBBBBB"<<endl;//虚继承，覆写原有func()
    }
};
int main()
{
    B b;
    b.foo();
    return 0;
}

