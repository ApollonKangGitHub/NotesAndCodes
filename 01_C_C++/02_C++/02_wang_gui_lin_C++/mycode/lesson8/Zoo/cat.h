#ifndef CAT_H
#define CAT_H
#include "animal.h"

class Cat:public Animal
{
public:
    Cat();
    ~Cat();
    virtual void voice();
};

#endif // CAT_H
