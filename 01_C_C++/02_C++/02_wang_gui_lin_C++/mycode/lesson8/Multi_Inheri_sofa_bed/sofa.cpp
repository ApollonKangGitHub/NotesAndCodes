#include "sofa.h"
#include <iostream>
using namespace std;

Sofa::Sofa(float len, float wid, float wei)
    :Furniture(len, wid, wei)
{}
Sofa::~Sofa()
{}
void Sofa::sit()
{
    cout<<"take a rest"<<endl;
}
