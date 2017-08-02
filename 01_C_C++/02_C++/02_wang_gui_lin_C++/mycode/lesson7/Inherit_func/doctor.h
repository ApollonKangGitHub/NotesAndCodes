#ifndef DOCTOR_H
#define DOCTOR_H
#include "graduate.h"

class Doctor : public Graduate
{
public:
    Doctor(string na,int ag,float sc,double sa,int y,int m,int d,string ti);
    void dump();
private:
    string title;
};

#endif // DOCTOR_H
