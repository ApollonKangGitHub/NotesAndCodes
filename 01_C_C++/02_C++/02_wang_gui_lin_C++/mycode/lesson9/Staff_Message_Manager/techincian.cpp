#include "techincian.h"

Techincian::Techincian()
{  
}
void Techincian::init()
{
    cout<<"Please enter the name of the technician:"<<endl;
    cin>>name;
    cout<<"Please enter the hours of technical personnel:"<<endl;
    cin>>_hourAmount;
    _moneyPerHour = 100;//默认每小时100元
}
void Techincian::CalcSarlary()
{
    salary = _hourAmount * _moneyPerHour;
}void Techincian::Promote()
{
    grade = 3;//技术人员为3级
}
void Techincian::DisplayInfo()
{
    cout<<"Name:"<<name<<endl;
    cout<<"Job number:"<<number<<endl;
    cout<<"Grade:"<<grade<<endl;
    cout<<"Salary:"<<salary<<endl;
}

