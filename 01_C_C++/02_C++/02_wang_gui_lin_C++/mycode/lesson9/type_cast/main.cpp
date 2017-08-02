/*
 * static_cast
 * dynamic_cast
 * reinterpret_cast
*/
#include <iostream>
#include <typeinfo>
using namespace std;
class A{
public:
    virtual ~A(){}
    void func(){cout<<"AAAAAAAAAAA"<<endl;}
};
class B:public A{
public:
    void func(){cout<<"BBBBBBBBBBB"<<endl;}
};
class C:public A{
public:
    void func(){cout<<"CCCCCCCCCCC"<<endl;}
};
class D{
public:
    void func(){cout<<"DDDDDDDDDDD"<<endl;}
};
int main()
{
    B b;
    A * pa = &b;
    if(pa){
        cout<<pa<<endl;
        pa->func();
    }
#if 1
    //dynamic_cast只能用于含有虚函数的父子类对象之间
    B * pb = dynamic_cast<B*>(pa);//成功安全
    if(pb){cout<<pb<<endl;pb->func();}
    C * pc = dynamic_cast<C*>(pa);//成功返回0安全
    if(pc){cout<<pc<<endl;pc->func();}
    D * pd = dynamic_cast<D*>(pa);//成功返回0安全
    if(pd){cout<<pc<<endl;pd->func();}
#endif
#if 0
    B * pb = static_cast<B*>(pa);//成功安全
    if(pb){cout<<pb<<endl;pb->func();}
    C * pc = static_cast<C*>(pa);//成功不安全
    if(pc){cout<<pc<<endl;pc->func();}
    //D * pd = static_cast<D*>(pa);//不成功安全
    //if(pd){cout<<pd<<endl;pd->func();}
#endif
#if 0
    /*先转换成void *，再转换成目标类型，但是强制性的无节操：不安全*/
    B * pb = reinterpret_cast<B*>(pa);//成功不安全
    if(pb){cout<<pb<<endl;pb->func();}
    C * pc = reinterpret_cast<C*>(pa);//成功不安全
    if(pc){cout<<pc<<endl;pc->func();}
    D * pd = reinterpret_cast<D*>(pa);//成功不安全
    if(pd){cout<<pd<<endl;pd->func();}
#endif
    return 0;
}

