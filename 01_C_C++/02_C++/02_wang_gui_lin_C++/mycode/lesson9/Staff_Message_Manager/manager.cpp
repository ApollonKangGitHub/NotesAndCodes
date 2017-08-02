#include "manager.h"

Manager::Manager()
{
    //_fixSalary = 8000;
}
void Manager::init()
{
    cout<<"Please enter the name of the manager:"<<endl;
    cin>>name;
     _fixSalary = 8000;
}
void Manager::CalcSarlary()
{
    salary = _fixSalary;
}
void Manager::Promote()
{
    grade = 4;//修改级别为4
}
void Manager::DisplayInfo()
{
    cout<<"Name:"<<name<<endl;
    cout<<"Job number:"<<number<<endl;
    cout<<"Grade:"<<grade<<endl;
    cout<<"Salary:"<<salary<<endl;
}
void Manager::addFixSalary(float addAmount)
{
    _fixSalary += addAmount;
}
