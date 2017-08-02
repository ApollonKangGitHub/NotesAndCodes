/*
 * 指向类数据成员的指针：
 * 定义：
 * <数据类型><类名>::*<指针名>
 * 赋值初始化：
 * <数据类型><类名>::*<指针名> = &<类名>::<非静态数据成员>
 *
 * 指向类成员函数的指针：
 * 定义：
 * <数据类型>(<类名>::*<指针名>)(<参数列表>)
 * 赋值初始化：
 * <数据类型>(<类名>::*<指针名>)(<参数列表>) = &<类名>::<非静态成员函数>
 *
*/
#include <iostream>

using namespace std;

class A{
public:
    A(int age, string name):
        name(name),age(age){}
    void print(){
        cout<<name<<"---"<<age<<endl;
    }

    string name;
    int age;
};

int main()
{
    A s1(20,"Mike");
    A *s2 = new A(21,"Danny");

    int A::*pa = &A::age;
    string A::*pn = &A::name;

    cout<<s1.age<<" "<<s2->age<<endl;
    cout<<s1.name<<" "<<s2->name<<endl;

    cout<<s1.*pa<<" "<<s2->*pa<<endl;
    cout<<s1.*pn<<" "<<s2->*pn<<endl;

    void (A::*p)() = &A::print;
    s1.print();
    s2->print();
    (s1.*p)();
    (s2->*p)();
    /*
     * 一种新的类型：".*"或者"->*"
     * 指向数成员的指针记录了偏移量，某个对象通过该新类型符号调用指针
     * 就可以找到相对偏移量的对象对应类型的值
     * 使用：
     * 对象.*数据成员指针               对象.*成员函数指针
     * 对象指针->*数据成员指针           对象指针->*成员函数指针
     *
    */

    return 0;
}

