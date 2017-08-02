#include "saleman.h"

SaleMan::SaleMan()
{
}
void SaleMan::init()
{
    cout<<"Please enter the name of the sales person:"<<endl;
    cin>>name;
    cout<<"Please enter sales month sales"<<endl;
    cin>>_monthSaleAmount;
    _rate = 0.05;
}
void SaleMan::CalcSarlary()
{
    salary = _monthSaleAmount * _rate;
}
void SaleMan::Promote()
{
    grade = 1;
}
void SaleMan::DisplayInfo()
{
    cout<<"Name:"<<name<<endl;
    cout<<"Job number:"<<number<<endl;
    cout<<"Grade:"<<grade<<endl;
    cout<<"Salary:"<<salary<<endl;
}
