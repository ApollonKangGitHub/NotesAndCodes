#ifndef BED_H
#define BED_H

#include "furniture.h"

class Bed:virtual public Furniture
{
public:
    Bed(float len, float wid, float wei);
    ~Bed();
    void sleep();
};

#endif // BED_H
