#include "employee.h"

int Employee::startNum = 100;//当前最大值(即已有员工)为100

Employee::Employee()
{
#if 0
/*
 * 为了防止构造器层级之间调用，重复打印构造器中无用的信息
 * 因而废掉了构造器(构造器中不写初始化的输出东西)，
 * 而采用具体类中的init()函数来代替
*/
    cout<<"Please enter employee name:"<<endl;
    cin>>name;
#endif
    grade = 1;//默认为1
    number = startNum++;//工号与创建新员工有关，与具体员工职能无关
}
Employee::~Employee()
{}

