#include "bed.h"
#include <iostream>
using namespace std;

Bed::Bed(float len, float wid, float wei)
    :Furniture(len, wid, wei)
{

}
Bed::~Bed()
{}
void Bed::sleep()
{
    cout<<"take a good sleep"<<endl;
}

