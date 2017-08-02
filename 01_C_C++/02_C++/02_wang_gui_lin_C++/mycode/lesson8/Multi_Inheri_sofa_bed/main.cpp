#include <iostream>
#include "sofa.h"
#include "bed.h"
#include "sofabed.h"

using namespace std;

int main()
{
    Bed b(2.4, 2.1, 214.62);
    b.discript();
    cout<<"-----------------"<<endl;
    Sofa s(2.2, 2.0, 212.06);
    s.discript();
    cout<<"-----------------"<<endl;

    SofaBed sb(2.1, 1.5, 62.214);
    sb.sleep();
    sb.sit();
    cout<<"-----------------"<<endl;
    sb.Sofa::discript();
    cout<<"*****************"<<endl;
    sb.Bed::discript();
    cout<<"*****************"<<endl;
    sb.discript();
    cout<<"-----------------"<<endl;

    return 0;
}
