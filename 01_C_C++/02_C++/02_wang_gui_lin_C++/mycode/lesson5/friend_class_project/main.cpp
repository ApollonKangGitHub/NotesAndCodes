/*
 * 像这种专门处理点的函数类，必然要用到点的信息
 * 然而每一个函数均设为friend，且得考虑前向性声明等问题
 * 显得十分麻烦
 *
 * 把B类声明为A类的友元，就可通过B类对象的成员函数，访问A类对象的public成员函数
 * 从而通过A的对象的public成员函数访问A的对象的private成员
 *
 * 注意事项：
 * ①友元关系不能被继承
 * ②友元关系具有单向性
 * ③友元不具有传递性
 *
*/
#include <iostream>
#include <math.h>
using namespace std;

class Point{
public:
    Point(double xx, double yy):x(xx),y(yy){}
    friend class PointManagement;//友元类
    void Getxy();
private:
    double x,y;
};

class PointManagement{
public:
    double getDirectDistance(Point &a, Point &b);//直线距离
    double getTrictDistance(Point &a, Point &b);//三角距离
};

double PointManagement::getDirectDistance(Point &a, Point &b)
{
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx*dx + dy*dy);
}
double PointManagement::getTrictDistance(Point &a, Point &b)
{
}
int main()
{
    Point a(1,2);
    Point b(4,6);

    PointManagement pm;
    double dis = pm.getDirectDistance(a,b);
    cout<<dis<<endl;
    return 0;
}

