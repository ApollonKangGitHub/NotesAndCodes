#ifndef SOFA_H
#define SOFA_H

#include "furniture.h"

class Sofa:virtual public Furniture
{
public:
    Sofa(float len, float wid, float wei);
    ~Sofa();
    void sit();
};
#endif // SOFA_H
