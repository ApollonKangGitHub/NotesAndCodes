#include <iostream>

using namespace std;
typedef void(*PFUNC)(void);

class Base{
public:
    virtual void f(){cout<<"Base::f()"<<endl;}
    virtual void g(){cout<<"Base::g()"<<endl;}
    virtual void h(){cout<<"Base::h()"<<endl;}
private:
    int a;
    int b;
};
class Derive:public Base
{
public:
    virtual void f(){cout<<"Derive::f1()"<<endl;}
    virtual void g(){cout<<"Derive::g1()"<<endl;}
    virtual void h(){cout<<"Derive::h1()"<<endl;}
private:
    int a;
    int b;
};
int main()
{
    Derive b;

    cout<<"Object start address:"<<&b<<endl;//对象起始地址
    cout<<"Virtual function table start address:";//V-Table起始地址
    cout<<(int **)(*(int *)(&b))<<endl;//int **：二级指针，表示虚表指针为函数指针数组

    cout<<"Function address in virtual function table:"<<endl;
    for(int i=0;i<6;i++){
        cout<<((int **)(*(int *)(&b)))[i]<<endl;
    }

    PFUNC pfunc;
    for(int i=0;i<3;i++){
        pfunc = ((PFUNC*)(int **)(*(int *)(&b)))[i];
        pfunc();
    }

    return 0;
}

