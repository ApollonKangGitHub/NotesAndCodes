#include "dog.h"
#include <iostream>

using namespace std;

Dog::Dog()
{
    cout<<"Dog()"<<endl;
}
Dog::~Dog()
{
    cout<<"~Dog()"<<endl;
}
void Dog::voice()
{
    cout<<"I'm a dog.Wang wang, wang wang wang wang!"<<endl;
}
