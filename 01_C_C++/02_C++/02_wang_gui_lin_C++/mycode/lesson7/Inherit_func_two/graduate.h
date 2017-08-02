#ifndef GRADUATE_H
#define GRADUATE_H
#include "student.h"

class Graduate : public Student
{
public:
    Graduate(string na, int ag, float sc, double sa);
    void print();
    Graduate(const Graduate & another);
    Graduate& operator=(const Graduate & another);
private:
    float salary;
};

#endif // GRADUATE_H
