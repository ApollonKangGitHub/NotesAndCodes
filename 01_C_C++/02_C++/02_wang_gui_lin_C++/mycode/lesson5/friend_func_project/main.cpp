/*
 * 像这种专门处理点的函数类，必然要用到点的信息
 * 然而每一个函数均设为friend，显得十分麻烦
 *
*/
#include <iostream>
#include <math.h>
using namespace std;


class Point;
class PointManagement{
public:
    double getDirectDistance(Point &a, Point &b);//直线距离
    double getTrictDistance(Point &a, Point &b);//三角距离
};

class Point{
public:
    Point(double xx, double yy):x(xx),y(yy){}
    friend double getDirectDistance(Point &a, Point &b);//全局友元函数
    friend double PointManagement::getDirectDistance(Point &a, Point &b);//其它类的友元函数
    friend double getTrictDistance(Point &a, Point &b);//三角距离
    void Getxy();
private:
    double x,y;
};

double getDirectDistance(Point &a, Point &b)
{
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx*dx + dy*dy);
}
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

    double dis = getDirectDistance(a,b);
    cout<<dis<<endl;

    PointManagement pm;
    dis = pm.getDirectDistance(a,b);
    cout<<dis<<endl;
    return 0;
}

