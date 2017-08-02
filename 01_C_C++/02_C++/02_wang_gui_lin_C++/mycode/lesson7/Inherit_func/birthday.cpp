#include "birthday.h"
#include <iostream>
using namespace std;

Birthday::Birthday(int y, int m, int d)
    :year(y),month(m),day(d)
{

}
void Birthday::dis()
{
    cout<<"birthday:"<<year<<":"<<month<<":"<<day<<endl;
}

