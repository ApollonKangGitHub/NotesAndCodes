#include <iostream>
#include "sofa.h"
#include "bed.h"
#include "sofabed.h"

using namespace std;

int main()
{
    Sofa s;
    s.sit();
    Bed b;
    b.sleep();
    SofaBed sb;
    sb.sit();
    sb.sleep();
    return 0;
}
