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
Student::Student(const Student & another)
{
    this->age = another.age;
    this->name = another.name;
    this->score = another.score;
    cout<<"Student copy constructor"<<endl;
}
Student &Student::operator=(const Student &another)
{
    if(this == &another)
        return *this;
    this->age = another.age;
    this->name = another.name;
    this->score = another.score;

    cout<<"Student operator ="<<endl;

    return *this;
}
