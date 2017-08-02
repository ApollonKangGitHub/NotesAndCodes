#include "graduate.h"

Graduate::Graduate(string na, int ag, float sc, double sa)
    :Student(na,ag,sc),salary(sa)
{
}

void Graduate::print()
{
    dis();
    cout<<"salary:"<<salary<<endl;
}
/**************************************
 * 继承了父类的三个成员变量，但是private不可见
 * Student(another);赋值兼容（子类对象（引用/指针），可以赋给父类对象（引用/指针））
 * 父类只有三个成员变量，故赋值只拷贝了三个
********************************************/
Graduate::Graduate(const Graduate & another)
    :Student(another),salary(another.salary)//不能用this，因为此时还未创建对象

{
    //this->salary = another.salary;//可以用this
    cout<<"Graduate copy constructor"<<endl;
}
Graduate& Graduate::operator=(const Graduate & another)
{
    if(this == &another)
        return *this;
    Student::operator=(another);//直接调用父类重载函数，因为父类重在函数被继承
    this->salary = another.salary;
    cout<<"Graduate operator ="<<endl;

    return *this;
}
