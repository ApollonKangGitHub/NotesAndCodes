/*多态与赋值兼容：
 * C++中所谓的动多态(Dynmic polymorphism)是指，由继承而产生的相关的不同的类，
 * 其对象对于同一种消息表现得不同的行为相应，多态性是面向对象程序设计的一个重要特征，
 * 能增加程序的灵活性。可以减轻系统升级,维护,调试的工作量和复杂度
 *
 * 赋值兼容规则是指在需要基类对象的任何地方都可以使用公有派生类的对象来替代。
 * 赋值兼容是一种默认行为，不需要任何的显示的转化步骤,
 * 在替代之后，派生类对象就可以作为基类的对象使用，但只能使用从基类继承的成员。
*/

#include <iostream>

using namespace std;
class Shape
{
public:
    Shape(int x, int y)
        :_x(x),_y(y){}
    void draw(){
        cout<<"draw from ("<<_x<<","<<_y<<")"<<endl;
    }
    void func(){
        cout<<"void func()"<<endl;
    }
protected:
    int _x;
    int _y;
};
/*
 * 赋值兼容规则中所指的替代包括以下的情况：
 *      ①派生类的对象可以赋值给基类对象。
 *      ②派生类的对象可以初始化基类的引用。
 *      ③派生类对象的地址可以赋给指向基类的指针。
 * 并且赋值兼容只能发生在公有派生的父子类对象之间
*/
//class Circle:protected Shape
class Circle:public Shape
{
public:
    Circle(int x, int y, int r)
        :Shape(x,y),_radius(r){}
    Circle & operator=(const Circle &another)
    {
        cout<<"Circle & operator=(const Circle &another)"<<endl;
        if(this == &another)
            return *this;
        Shape::operator=(another);
        this->_radius = another._radius;
        return *this;
    }
    void draw(){
        cout<<"draw from ("<<_x<<","<<_y<<")"<<endl;
        cout<<"radius:"<<_radius<<endl;
    }
    void print(){
        cout<<"void print()"<<endl;
    }
private:
    int _radius;
};

int main()
{
    Shape s(0,0);
    s.draw();

    Circle c(5,4,3);
    c.draw();
#if 1
    /*子类转父类*/
    cout<<"---------------------"<<endl;
    s = c;//赋值兼容(对象)
    s.draw();//父类对象s看到的是父类的draw()接口,而不是子类的draw()接口
    s.func();//s可以看到
    //s.print();//s只能访问子类继承的成员

    Shape & rs = c;//赋值兼容(引用)
    rs.draw();

    Shape * ps = &c;//赋值兼容(指针)
    ps->func();
#endif
#if 1
    /*父类转子类有越界问题*/
    cout<<"---------------------"<<endl;
    Circle *pc;
    pc = static_cast<Circle*>(&s);

    pc->draw();
    pc->func();
    pc->print();

    cout<<"---------------------"<<endl;
    //Circle & operator=(const Circle &another)
    c = static_cast<Circle&>(s);
    c.draw();
    c.func();
    c.print();
#endif
    return 0;
}

