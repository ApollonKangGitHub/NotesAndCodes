#include <iostream>
using namespace std;

//throw(int, float, double)表示可能会抛出的异常类型，
//throw()表示该函数不会抛出异常，但是如果抛出异常，
//而且调用者没异常处理，就会崩溃
//不写表示可能抛出任何类型的异常
void g()throw(int, float, double)
{
    double a;
#if 0
    float a;
    int a;
    char a;
#endif
    try{
     throw a;
    }catch(double){
        cout<<"catch g()"<<endl; //throw, 自己抛，自己处理
        //如果底层未处理，则向上抛，到顶层还未处理时，系统崩溃提示
    }
    cout<<"end g()"<<endl;
    return ;
}
void h()
{
    try{
        g();
    }catch(int){
        cout<<"catch h()"<<endl;
    }
    cout<<"end h()"<<endl;
}
void f()
{
    try{
        h();
    }catch(char){
        cout<<"catch f()"<<endl;
    }
    cout<<"end f()"<<endl;
}
int main()
{
    try{
        f();
    }catch(double){
        cout<<"catch main"<<endl;
    }
    cout<<"end main"<<endl;
    return 0;
}
