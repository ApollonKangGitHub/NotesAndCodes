/*
 * 继承的方式不影响子类中成员的访问方式
 * 影响了父类中的成员在子类中的访问方式
 *
 *   Father                           Son
 *  (访问权限)                       (继承方式)
 *                      public         private      protected
 * public:              public         private      protected
 * protected:           protected      private      protected
 * private:             inaccess       inaccess     inaccess
 *
 *
 *公有继承：基类的公有和保护成员被继承且继承其权限分别为公有与保护，私有成员被继承但不能访问(不可见)
 *私有继承：基类的公有和保护成员被继承且继承后在子类中其权限为私有，私有成员被继承但不能访问(不可见)
 *保护继承：基类的公有和保护成员被继承且继承后在子类中其权限为保护，私有成员被继承但不能访问(不可见)
 *由此可见基类的私有成员不能被派生的子类访问，无论以何种方式继承
 *派生类继承了基类的除构造器与析构器的所有成员，但是“全盘”继承有可能不能访问，
 *会造成派生类的冗余，所以基类是需要精心设计的。派生类有自己的个性才具有意义
 *
 * public继承方式用于99.99%的继承
 * 原因：
 * public:既传承了数据、又传承了接口
 * protected:只能传承数据
 * private:既没有传承接口又没有传承数据
*/
#include <iostream>

using namespace std;
class Father
{
public:
    int x;
protected:
    int y;
private:
    int z;
};

class Son:public Father
{
public:
    int pub;
    void func(){
        x=3;
        y=4;
        //z=5;
    }
protected:
    int pro;
private:
    int pri;
};
int main()
{
    Son s;
    s.pub;
//    s.pri;
//    s.pro;
    return 0;
}

