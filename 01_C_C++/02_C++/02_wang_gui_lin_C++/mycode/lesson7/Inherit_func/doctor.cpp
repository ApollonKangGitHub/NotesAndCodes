#include "doctor.h"

Doctor::Doctor(string na,int ag,float sc,double sa,int y,int m,int d,string ti)
    :Graduate(na,ag,sc,sa,y,m,d),title(ti)
{
    cout<<"Doctor constructor"<<endl;
}

void Doctor::dump()
{
    print();
    cout<<"title:"<<title<<endl;
}
