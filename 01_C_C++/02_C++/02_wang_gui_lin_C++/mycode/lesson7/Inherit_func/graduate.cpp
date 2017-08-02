#include "graduate.h"
/*
 * 派生类名::派生类名（参数总表）：基类名（参数表）,内嵌子对象（参数表）
 * {
 *      派生类新增成员的初始化语句; //也可出现地参数列表中
 * }
 * 父类中如果有标配（重载/默认参数），子类中的构造器中可以不用显式的调用父类的构造器
 * 子类只需要对父类负责，不需要对父类的父类负责；递归遵守
*/
Graduate::Graduate(string na, int ag, float sc, double sa, int y, int m, int d)
    :Student(na,ag,sc),salary(sa),birth(y,m,d)
{
    cout<<"Graduate constructor"<<endl;
}
void Graduate::print()
{
    dis();//name、age、score
    cout<<"salary:"<<salary<<endl;
}
void Graduate::getBirthday()
{
    birth.dis();
}
