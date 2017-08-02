#include <iostream>

using namespace std;
/*
 * 纯虚函数没有实现体，含有纯虚函数的类称作为抽象基类，抽象基类不可以实例化
 * 存在的意义就是被继承，提供族类的公共接口(interface)，实现多态。
 * 纯虚函数只有声明，没有实现，被初始化为"0"
 * 如果一个类中声明了纯虚函数，而在派生类中没有对该函数定义，则该函数在派生类中
 * 仍然为纯虚函数，派生类仍未纯虚基类。
 *
*/
class Shape
{
public:
    Shape(int x, int y)
        :_x(x),_y(y){}
    virtual void draw()=0;
protected:
    int _x;
    int _y;
};

class Circle:public Shape
{
public:
    Circle(int x, int y, int r)
        :Shape(x,y),_radius(r){}
    void draw(){
        cout<<"draw from ("<<_x<<","<<_y<<")";
        cout<<",radius = "<<_radius<<endl;
    }
private:
    int _radius;
};
class Rect:public Shape
{
public:
    Rect(int x, int y, int len, int wid)
        :Shape(x,y),_len(len),_wid(wid){}
    virtual void draw(){
        cout<<"draw from ("<<_x<<","<<_y<<")";
        cout<<",len = "<<_len<<",wid = "<<_wid<<endl;
    }
private:
    int _len;
    int _wid;
};
int main()
{
    Shape *ps;
    Circle c(10,2,3);
    Rect r(1,2,3,4);

    ps = &c;
    ps->draw();
    ps = &r;
    ps->draw();
    return 0;
}
