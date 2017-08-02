#include "cat.h"
#include <iostream>

using namespace std;

Cat::Cat()
{
    cout<<"cat()"<<endl;
}
Cat::~Cat()
{
    cout<<"~cat()"<<endl;
}
void Cat::voice()
{
    cout<<"I'm a cat.Miao,miao miao miao miao miao!"<<endl;

}

