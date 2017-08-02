/*
 * 实现其他类类型到本类类型的转换：
 * 类型转换构造函数(在目标类中写)：
 * class 目标类{
 *      目标类(const 源类 & 源类对象的引用)
 *      {
 *          根据需要完成源类型到目标类型的转换
 *      }
 * };
 *
 * 两个类型转换的声明的关键字：
 * implicit：声明为隐式
 * explicit：声明为显式
 *
*/
#include <iostream>

using namespace std;

class Point2D{
public:
    Point2D(int x, int y)
        :_x(x),_y(y){}
    friend class Point3D;
private:
    int _x;
    int _y;
};
class Point3D{
public:
    Point3D(int x, int y, int z)
        :_x(x),_y(y),_z(z){}

    /*我们把这一类单参的构造器，称为类型转换构造器，explicit声明为显式转换*/
    explicit Point3D(const Point2D & p2){
        this->_x = p2._x;
        this->_y = p2._y;
        this->_z = 0;
    }
    void dis(){
        cout<<"("<<_x<<","<<_y<<","<<_z<<")"<<endl;
    }
private:
    int _x;
    int _y;
    int _z;
};

int main()
{
    Point2D p2(1,2);
    Point3D p3(3,4,3);

    //p3 = p2;//隐式转换
    //p3 = (Point3D)p2;//C的显式转换
    p3 = static_cast<Point3D>(p2);//C++的显式转换
    p3.dis();
    return 0;
}

