#include <iostream>

using namespace std;


class Base{
public:
    virtual void f(){cout<<"Base::f()"<<endl;}
    virtual void g(){cout<<"Base::g()"<<endl;}
    virtual void h(){cout<<"Base::h()"<<endl;}
private:
    int a;
    int b;
};
class Base_Two{
public:
    void f(){cout<<"Base::f()"<<endl;}
    void g(){cout<<"Base::g()"<<endl;}
    void h(){cout<<"Base::h()"<<endl;}
private:
    int a;
    int b;
};
int main()
{
    Base b;
    Base_Two b2;
#if 0

    cout<<sizeof(Base)<<endl;
    cout<<sizeof(b)<<endl;


    cout<<sizeof(Base_Two)<<endl;
    cout<<sizeof(b2)<<endl;
#endif
    cout<<"Object start address:"<<&b<<endl;//对象起始地址
    cout<<"Virtual function table start address:";//V-Table起始地址
    cout<<(int **)(*(int *)(&b))<<endl;
    //int **：二级指针，表示虚表指针为函数指针数组

    cout<<"Function address in virtual function table:"<<endl;
    cout<<((int **)(*(int *)&b))[0]<<endl;
    cout<<((int **)(*(int *)&b))[1]<<endl;
    cout<<((int **)(*(int *)&b))[2]<<endl;
    cout<<((int **)(*(int *)&b))[3]<<endl;

    typedef void(*PFUNC)(void);

    PFUNC pf = ((PFUNC*)(int **)(*(int *)(&b)))[0];
    pf();
    PFUNC pg = ((PFUNC*)(int **)(*(int *)(&b)))[1];
    pg();
    PFUNC ph = ((PFUNC*)(int **)(*(int *)(&b)))[2];
    ph();

    return 0;
}
























