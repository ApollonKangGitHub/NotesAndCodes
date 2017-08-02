#include <iostream>
#include "date.h"

using namespace std;
namespace Kang{
    void Date::Print(){
        cout<<"year\t"<<"month\t"<<"day"<<endl;
        cout<<year<<"\t"<<month<<"\t"<<day<<endl;
    }
    void Date::Init(){
        cin>>year>>month>>day;
    }
    bool Date::IsLeapYear(){
        if((year%4==0 && year%100!=0) || year%400==0)
            return true;
        else
            return false;
    }
    int& Date::GetYear(){//还是不要反回引用的好
        return year;
    }
}
