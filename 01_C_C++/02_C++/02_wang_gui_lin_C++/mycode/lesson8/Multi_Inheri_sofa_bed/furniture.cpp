#include "furniture.h"
#include <iostream>
using namespace std;
Furniture::Furniture(float len, float wid, float wei)
    :_length(len),_width(wid),_weight(wei)
{

}

void Furniture::discript()
{
    cout<<"length = "<<_length<<endl;
    cout<<"width = "<<_width<<endl;
    cout<<"weight = "<<_weight<<endl;
}
