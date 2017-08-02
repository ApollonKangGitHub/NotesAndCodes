#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <iostream>
using namespace std;

class Employee
{
public:
    Employee();
    virtual void init() = 0;//初始化
    virtual void CalcSarlary() = 0;//计算薪资
    virtual void Promote() = 0;//升级
    virtual void DisplayInfo() = 0;//输出信息
    virtual ~Employee();
protected:
    string name;//姓名
    int number;//编号
    int grade;//级别
    float salary;//薪资
protected:
    static int startNum;//当前已经编号的最大值
};

#endif // EMPLOYEE_H
