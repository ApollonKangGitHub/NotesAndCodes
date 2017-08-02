#ifndef SALEMANAGER_H
#define SALEMANAGER_H

#include "saleman.h"
#include "manager.h"

class SaleManager : virtual public SaleMan,virtual public Manager
{
public:
    SaleManager();
    virtual void init();
    virtual void CalcSarlary();
    virtual void Promote();
    virtual void DisplayInfo();
};

#endif // SALEMANAGER_H
