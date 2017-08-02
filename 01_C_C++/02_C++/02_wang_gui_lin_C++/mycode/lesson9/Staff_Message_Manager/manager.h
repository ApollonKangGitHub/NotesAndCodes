#ifndef MANAGER_H
#define MANAGER_H

#include "employee.h"

class Manager : virtual public Employee
{
public:
    Manager();
    virtual void init();
    virtual void CalcSarlary();
    virtual void Promote();
    virtual void DisplayInfo();
    void addFixSalary(float addAmount);
protected:
    float _fixSalary;
};

#endif // MANAGER_H
