/*
 *const 对象的引用必须是 const 的， 将普通引用绑定到 const 对象是不合法的
 *const 引用可使用相关类型的对象(常量,非同类型的变量或表达式)初始化
 *尽可能使用 const，use const whatever possible 原因如下：
 *①使用 const 可以避免无意修改数据的编程错误。
 *②使用 const 可以处理 const 和非 const 实参。否则将只能接受非 const 数据。
 *③使用 const 引用，可使函数能够正确的生成并使用临时变量（如果实参与引用参数不匹配，就会生成临时变量）
*/
#include <iostream>

using namespace std;

int main()
{
    //int &x = 10;//常量本是不能引用的，因为引用是声明不是定义(多次强调)，不回为整数10开辟空间
    const int &x = 10;//const修饰常量引用，const为10开辟了新的未命名空间

    double a = 3.14;
    double &ra = a;
    //int &ra2 = a;//编译是通不过的

    /*ra2声明为常量(int)a=3的引用，该引用不是a的引用,a与ra2的地址不同
    *即为表达式的结果开辟了一个未命名的空间,并将该空间的引用声明为ra2
    */
    const int &ra2 = a;

    cout<<a<<" "<<ra<<" "<<ra2<<endl;

    a = 4.154;
    cout<<a<<" "<<ra<<" "<<ra2<<endl;

    return 0;
}

