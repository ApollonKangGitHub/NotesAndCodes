#ifndef SOFABED_H
#define SOFABED_H
#include "sofa.h"
#include "bed.h"

class SofaBed:public Sofa,public Bed
{
public:
    SofaBed();
    ~SofaBed();
};
#endif // SOFABED_H
