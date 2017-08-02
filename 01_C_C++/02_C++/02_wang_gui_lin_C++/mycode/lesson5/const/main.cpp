/*
 * 1、const修饰成员函数、数据成员、类对象
 * 2、修饰数据成员时，初始化位置必须选在形参列表中，被const修饰的数据成员不能被修改
 * 即使新版本可以在cosnst声明时直接初始化，但是不好
 * 3、修饰成员函数(引起参数列表相同也能重载)：
 * 位置：const修饰函数时，放在函数右括号之后，且声明与定义处均有（比较特殊）
 * （C++很多东西在声明时由，而定义时就不需要如：virtual修饰函数返回值、static修饰的成员变量等）
 * 意义：const函数承诺不会修改数据成员,且调用的函数且必须被const修饰
 * 4、修饰类对象：
 * const修饰函数是从函数的层面不允许修改数据
 * 而const修饰对象是从对象的层面不修改数据,
 *
 * 所以const修饰的对象只能调用const成员函数，
 * 而非const对象，默认调用非const成员函数，
 * 若无非const成员函数则调用const成员函数
 *
*/
#include <iostream>

using namespace std;

class A{
public:
    A(int v):val(v){}

    void dis()const{
        cout<<val<<endl;
        //x = 200;//const 修饰的函数不能（不会）修改成员变量
        //print1();//不可以“借刀杀人”
        print2();
        cout << "void dis()const" <<endl;
    }
    void dis(){
        cout<<val<<endl;
        x = 200;
        print1();
        print2();
        cout << "void dis()" <<endl;
    }
    void print1(){
        x = 100;
        y = 200;
    }
    void print2()const{
        //y = 200;
    }
private:
    const int val;
    int x, y;
};

int main()
{
    A a(5);
    a.dis();

    const A b(6);
    b.dis();
    //b.print1();
    b.print2();
    return 0;
}

