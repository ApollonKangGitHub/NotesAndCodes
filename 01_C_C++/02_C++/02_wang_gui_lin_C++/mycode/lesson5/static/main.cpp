/*
 * C的static:
 * 全局变量具有外延性（external link），而被static修饰以后，作用域仅限于本文件
 * 局部变量（默认auto），而被static修饰的局部变量生命周期、存储位置等发生改变
 * 生命周期与整个进程的生命周期相同，存储位置不再在栈上
 *
 * C++的static:
 * static，在类内部的变现，用来实现簇类对象间的数据共享。在生成对象时，普通成员才被分配空间。
 * 而static成员在类声明的时候就已经开辟了空间在data的rw段
 * static数据成员，既属于类、也属于对象，但终归属于类
 * ①初始化：类内定义，类外初始化
 * ②使用：(类本质也是一个命名空间),共享使用
 *
*/
#include <iostream>

using namespace std;

namespace Space{
    int share = 1001;//初始化在类以外，且不用加static
}

class A{
public:
    int x, y;

    void print(){
        cout<<share<<endl;
    }
    void change(int val){
        share = val;
    }

    static int share;//不占类的内存空间
};
int A::share = 100;
int main()
{
    A a,b,c;

    cout<<"sizeof(a):" <<sizeof(a)<<endl;
    cout<<"sizeof(b):" <<sizeof(b)<<endl;
    cout<<"sizeof(c):" <<sizeof(c)<<endl;
    cout<<"sizeof(A):" <<sizeof(A)<<endl;

    cout<<Space::share<<endl;

    a.change(0);
    cout<<a.share<<endl;

    b.change(200);
    b.print();

    c.change(300);
    b.print();

    return 0;
}

