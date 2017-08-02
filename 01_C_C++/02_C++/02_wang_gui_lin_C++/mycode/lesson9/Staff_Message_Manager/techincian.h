#ifndef TECHINCIAN_H
#define TECHINCIAN_H

#include "employee.h"

class Techincian : virtual public Employee
{
public:
    Techincian();
    /*覆写*/
    virtual void init();
    virtual void CalcSarlary();
    virtual void Promote();
    virtual void DisplayInfo();
private:
    int _hourAmount;
    int _moneyPerHour;
};

#endif // TECHINCIAN_H
