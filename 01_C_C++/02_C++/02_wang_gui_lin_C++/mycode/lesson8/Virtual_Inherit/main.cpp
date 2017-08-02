#if 1
#include <iostream>
/*
 * 如果X和Y类中均有_data数据成员，会有二义性，所以：
 * 将X和Y共有的_data提取到Vir类中，
 * 并使得X和Y分别虚继承Vir(virtual关键字)
 * 而Z多继承X与Y，那么X就可以访问_data
 *
 * 虚基类与虚继承是需要设计和抽象的，虚继承是继承的一种扩展
*/
using namespace std;

class Vir{//虚基类
public:
    Vir(int v = 0):_data(v){}
    int _data;
};
class X:virtual public Vir{
public:
    X(int x = 0):Vir(x){}
    void setData(int data)
    {
        _data = data;
    }
};
class Y:virtual public Vir{
public:
    Y(int y = 0):Vir(y){}
    int getData(){
        return _data;
    }
};
class Z:public X, public Y{
public:
    Z(int x=0, int y=0, int z=0):X(x),Y(y),Vir(z){}
    void dis()
    {
        cout<<X::_data<<endl;
        cout<<Y::_data<<endl;
        cout<<_data<<endl;
    }
};
int main()
{
    Z z(-1,-2,-3);
    z.dis();
    cout<<"-----------------"<<endl;
    cout<<"getdata:"<<z.getData()<<endl;
    cout<<"-----------------"<<endl;

    z.setData(10);
    z.dis();
    cout<<"-----------------"<<endl;
    cout<<"getdata:"<<z.getData()<<endl;
    cout<<"-----------------"<<endl;
    z.setData(20);

    z.dis();
    cout<<"-----------------"<<endl;
    cout<<"getdata:"<<z.getData()<<endl;
    cout<<"-----------------"<<endl;

    X x(-1);
    Y y(-2);
    cout<<x._data<<endl;
    cout<<y._data<<endl;
    cout<<"-----------------"<<endl;

    z.dis();//z与x、y的空间均不同，z输出结果依旧是之前的20
    cout<<"-----------------"<<endl;
    cout<<"getdata:"<<z.getData()<<endl;
    cout<<"-----------------"<<endl;

    return 0;
}

#endif
#if 0

#include <iostream>

using namespace std;

class Base{
public:
    virtual void foo(){cout<<"call Base::foo()\n";}
    void bar(){cout<<"call Base::Derive()\n"; foo();}
};
class Derive:public Base{
public:
    virtual void foo(){cout<<"call Derive::foo()\n";}
    void bar(){cout<<"call Derive::Derive()\n"; foo();}
};
int main(void){

    Base * ptr = new Derive();
    //父类指针调用父类的bar()函数，虚表中存在的是覆写了父类foo()函数的子类foo()，所以调用子类foo()
    if(ptr!=NULL)
        ptr->bar();
    return 0;
}
#endif
