/**********************************************
    * constructor 构造器
    * 与类名相同，无返回值，生成对象时自定调用，相当于初始化
    * 可以有参数，能够重载、以及设置默认参数
    * 如果不自定义任何构造器，则系统会有一个默认的无参构造器生成，
    * 若自定义了一个构造器，则系统不再生成构造器
    * 注意：无参数构造器与有参数但是有默认参数的构造器，定义对象时可能会产生二义性
    * 就是之前提到的：重载与默认参数不要在同一个函数名中同时出现
******************************************/
/**********************************************
    * destructor 析构器
    * 与~+类名，无参数、无返回值、用于对象销毁时的内存处理工作（对象消失时，自动被调用）
    * 所谓消失，指的是跳出其作用空间，且以后不会再使用
    * 若无自定义析构器，则系统默认生成一个析构器
    * 对于系统自行析构的，先创建的后析构、后创建的先析构
******************************************/
#ifndef _STACK_H
#define _STACK_H

#define STACK_SIZE 1024//默认1024

class Stack{
public:
#if 0
    Stack(){//无参构造器，初始化工作交给构造器
        top = 0;
        space = new char[STACK_SIZE];
        _size = STACK_SIZE;
    }
#endif
    Stack(int size = 1024){//构造器重载实现栈空间的按需申请.默认参数实现标配
        top = 0;
        space = new char[size];
        _size = size;
    }
    Stack(const Stack & another);
    bool isEmpty();
    bool isFill();
    void push(char c);
    char pop();
    ~Stack(){
        delete space;
    }
private:
    char * space;
    int top;
    int _size;
};

#endif
