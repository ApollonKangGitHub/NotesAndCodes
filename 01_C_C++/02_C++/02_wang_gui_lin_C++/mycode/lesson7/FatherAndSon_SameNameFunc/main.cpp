/*
 * 2017年3月22日13:03:18
 * 在拷贝构造器重载与赋值运算符重载自定义实现的使用中
 * 只在深拷贝时会用都，否则一般都不用程序员去重载
*/
#include <iostream>

using namespace std;
class Father{
public:
    void dis()
    {
        cout<<"father"<<endl;
    }
};
class Son:public Father
{
public:
    //子类中会把父类中重名的dis()成员函数shadow（可解释为屏蔽）
    //shadow只与函数名有关，于参数和返回值无关，即函数名冲突就会shadow
    void dis()
    {
        cout<<"son"<<endl;
        //dis();
        //如果不注释，由于已经shadow了父类的dis()
        //就出现自己调用自己：死循环最后栈溢出崩溃
        //因而绝对不要使得子类与父类中的成员重名
        //如果非要用就必须加上命名空间

        Father::dis();
    }
};
int main()
{
    Son son;
    son.dis();
    return 0;
}
