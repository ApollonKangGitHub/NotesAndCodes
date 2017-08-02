#ifndef SOFABED_H
#define SOFABED_H
#include "sofa.h"
#include "bed.h"

class SofaBed:public Sofa,public Bed
{
public:
    SofaBed(float len, float wid, float wei);
    ~SofaBed();
};
#endif // SOFABED_H
