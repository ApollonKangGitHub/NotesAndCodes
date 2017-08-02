#include <iostream>
//using namespace std;//这样做不好，将std的用得到的用不到的都释放

int val = 10;
/*
 *::为作用域运算符，一般前面要加命名空间，
 *如果不加，则命名空间为全局(即全局命名空间是无命名空间)
 *其实namespace是对全局命名空间的再次划分
*/

namespace space_one{
    int val = 1;
    int x;
    int y;
}
namespace space_two{
    int val = 2;
    int x;
    int y;
}

int main()
{
    using std::cin;
    using std::cout;
    using std::endl;

    int * q = &val;//下一个val还未定义，取的是全局的val的地址
    int val = 5;
    int * p = &val;//第二个val已经定义，取的是局部的val的地址

    cout<<"*q="<<*q<<endl;
    cout<<"val="<<::val<<endl;//输出全局的val
    cout<<"*p="<<*p<<endl;
    cout<<"val="<<val<<endl;


    cout<<"val="<<space_one::val<<endl;//输出命名空间space_one的val
    cout<<"val="<<space_two::val<<endl;

    using namespace space_two;//如果在main之前释放命名空间，会有val冲突

    space_one::x=30;
    space_one::y=40;
    x=10;//默认是释放了的space_one
    y=20;

    #if 0
    {/*只在本代码块内生效的方法*/
        using namespace space_two;
        x = 50;
        y = 60;
    }
    #endif

    cout<<"x="<<x<<endl;
    cout<<"y="<<y<<endl;

    cout<<"x="<<space_one::x<<endl;
    cout<<"y="<<space_one::y<<endl;
    return 0;
}

