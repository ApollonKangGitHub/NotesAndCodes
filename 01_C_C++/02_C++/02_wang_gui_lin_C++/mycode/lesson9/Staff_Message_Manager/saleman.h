#ifndef SALEMAN_H
#define SALEMAN_H

#include "employee.h"

class SaleMan : virtual public Employee
{
public:
    SaleMan();
    virtual void init();
    virtual void CalcSarlary();
    virtual void Promote();
    virtual void DisplayInfo();
protected:
    float _monthSaleAmount;//销售额
    float _rate;//提成百分比
};

#endif // SALEMAN_H
