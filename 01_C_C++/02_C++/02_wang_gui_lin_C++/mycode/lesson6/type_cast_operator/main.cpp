/*
 * 实现其他类类型到本类类型的转换：
 * 用类型转换操作符函数转换(在源类中写)：
 * class 源类{
 *      operator 转换目标类型(void)//无参无返回
 *      {
 *          根据需要完成源类型到目标类型的转换
 *      }
 * };
 *
 *
*/
#include <iostream>

using namespace std;

class Point2D{
public:
    Point2D(int x, int y)
        :_x(x),_y(y){}
    void dis(){
        cout<<"("<<_x<<","<<_y<<")"<<endl;
    }
private:
    int _x;
    int _y;
};
class Point3D{
public:
    Point3D(int x, int y, int z)
        :_x(x),_y(y),_z(z){}

    operator Point2D()
    {//无返回指的是不能自己定义返回值类型，编译器自己根据需求确定
        return Point2D(this->_x, this->_y);
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

    p2 = p3;
    p2.dis();
    return 0;
}

