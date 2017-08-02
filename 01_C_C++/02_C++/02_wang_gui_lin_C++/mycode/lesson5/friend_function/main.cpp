/*
 * 友元破坏了封装性与隐秘性
 * 但是友元提高了程序的执行效率
 * 友元可以是函数也可以是类，并且友元是存在于异类之间的
 *
*/
#include <iostream>

using namespace std;
class A;
//前向型声明，不能解决A::的问题，但是能解决A&的问题，所以将B类放到前面，给A做前向性声明
//并且前向性声明只能为引用声明空间，不能为类中函数参数声明,只有将B的函数定义放到外面
//编译器才能够识别并分配临时空间

class B{
public:
    void dis(A&a);//A的引用所以可以做前向性声明
};

class A{
public:
    A(int x=0, int y=0, int z=0):x(x),y(y),z(z)
    {}
    int getx(){return x;}
    int gety(){return y;}
    int getz(){return z;}

    friend void ::dis(A&a);//::表示还全局空间
    friend void B::dis(A &a);//B的作用域B::不能做前向性声明
    //声明非本类所属的函数本类的友元函数，并且该声明与位置无关，但是一般放在public中
    //友元函数可以是全局的，也可以是其它类中的成员函数
private:
    int x,y,z;
};

void B::dis(A&a){//拿出来以实现前向性声明
    cout<<a.getx()<<"\t"<<a.gety()<<"\t"<<a.getz()<<endl;
}
void dis(A&a){
    cout<<a.getx()<<"\t"<<a.gety()<<"\t"<<a.getz()<<endl;
}

int main()
{
    A a(1,2,4);

    dis(a);

    A a2(2,4,8);
    B b;
    b.dis(a2);

    return 0;
}

