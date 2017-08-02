/*func.c*/
#include<iostream>
using namespace std;

extern "C"
{
    void func(int a)
    {
        cout<<"a = "<<a<<endl;
    }
}
