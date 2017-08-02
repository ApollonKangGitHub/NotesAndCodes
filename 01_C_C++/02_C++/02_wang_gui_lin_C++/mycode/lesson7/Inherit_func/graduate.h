#ifndef GRADUATE_H
#define GRADUATE_H
#include "student.h"
#include "birthday.h"

class Graduate : public Student
{
public:
    Graduate(string na, int ag, float sc, double sa, int y=0, int m=0, int d=0);
    void print();
    void getBirthday();
private:
    double salary;
    Birthday birth;
};

#endif // GRADUATE_H
