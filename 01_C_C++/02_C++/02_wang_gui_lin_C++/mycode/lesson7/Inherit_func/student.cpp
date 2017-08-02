#include "student.h"

Student::Student(string na, int ag, float sc)
    :name(na),age(ag),score(sc)
{
    cout<<"Student constructor"<<endl;
}
void Student::dis()
{
    cout<<"name:"<<name<<endl;
    cout<<"age:"<<age<<endl;
    cout<<"acore:"<<score<<endl;
}
