#include <iostream>
#include <typeinfo>

using namespace std;
typedef double(*PFUNC)(float);
class A
{
public:
    virtual ~A(){}
};
class B:virtual public A
{
};
int main()
{
    B b;
    A & rb = b;
    A * pb = &b;

#if 0
    cout<<typeid(rb).name()<<endl;
    cout<<typeid(*pb).name()<<endl;
    cout<<typeid(pb).name()<<endl;

    cout<<typeid(int).name()<<endl;
    cout<<typeid(long).name()<<endl;
    cout<<typeid(unsigned int).name()<<endl;
    cout<<typeid(PFUNC).name()<<endl;
#endif

    if(typeid(pb) == typeid(B))
        cout<<typeid(pb).name()<<endl;//1B中1为大小B为类名
    if(typeid(*pb) == typeid(B))
        cout<<typeid(*pb).name()<<endl;

    return 0;
}

