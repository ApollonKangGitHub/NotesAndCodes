#include <iostream>

using namespace std;

class A{
public:
    A(){
        cout<<a<<endl;
    };
private:
    //const修饰放在参数列表中初始化
    //static修饰放在类以外初始化
    //const与static同时修饰，直接初始化
    static const int a = 10;
};

int main()
{
    A a;
    return 0;
}

