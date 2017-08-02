#include "salemanager.h"

SaleManager::SaleManager()
{   
}
void SaleManager::init()
{
    cout<<"Please enter the name of the sales manager:"<<endl;
    cin>>name;
    cout<<"Please enter month sales"<<endl;
    cin>>_monthSaleAmount;
    _fixSalary = 5000;//销售经理固定工资为5000
    _rate = 0.05;//销售经理提成率为0.04
}
void SaleManager::CalcSarlary()
{
    salary = _fixSalary + _monthSaleAmount * _rate;
}
void SaleManager::Promote()
{
    grade = 3;
}
void SaleManager::DisplayInfo()
{
    cout<<"Name:"<<name<<endl;
    cout<<"Job number:"<<number<<endl;
    cout<<"Grade:"<<grade<<endl;
    cout<<"Salary:"<<salary<<endl;
}
