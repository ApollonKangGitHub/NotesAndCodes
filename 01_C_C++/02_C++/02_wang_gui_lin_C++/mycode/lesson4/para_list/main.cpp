#include <iostream>
#include <string.h>
using namespace std;
/*
 *构造器的目的不是创建空间，而是初始化空间
 *析构器的目的也不是回收空间，而是做销毁对象前相关的内存清理工作
*/
class A{
public:
    A(int i=0,int j=0,int k=0)
        :x(i),y(j),z(k)//参数列表，逼格高效率更高
        //在函数声明之后，实现体之前，以":"开头，用括号内的值为括号外的赋值
    {
        cout<<"gouzao"<<":z="<<z<<endl;
        name = new char[100];
    }
    ~A(){
        delete name;
        cout<<"xigou"<<":z="<<z<<endl;
    }
private:
    int x;
    int y;
    int z;
    char * name;
};
/*参数列表与其初始化*/
class Stu{
public:
    #if 0
    Stu(string str)
            :name(str),len(strlen(name.c_str()))
            //要想name.c_str()可行，必须将name的声明放到len的声明之前
            //参数列表初始化顺序：与变量声明顺序有关，与初始化表中顺序无关
    #endif
    Stu(string str)
        :len(strlen(str.c_str())),name(str)
        //strlen(void *);测试的是C的字符串，无法直接测试string类的对象;
        //c_str()返回的是string类对象转化成的指向C字符串的指针
    {

    }
    void dis(){
        cout<<len<<endl;
    }
private:
    int len;
    string name;
};
int main()
{
    A a(1,2,3);// 系统自行调用析构器
    A * pa = new A(1,2);

    delete pa;//析构器负责清理pa->name等内存空间，而销毁对象的整个任务确实也是参与的
    //但是其本质功能还是做销毁对象前相关的内存清理工作，若果无相关清理工作，析构函数便可采用默认的

    Stu s("Hello World!");
    s.dis();

    return 0;
}

