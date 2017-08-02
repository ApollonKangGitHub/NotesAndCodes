#include <iostream>
#include "student.h"
#include "graduate.h"
#include "doctor.h"
#include "birthday.h"

using namespace std;

int main()
{
    Student s("Mr.Kang", 21, 145);
    s.dis();

    cout<<"-----------------------"<<endl;
    Graduate g("YuYu", 21, 145, 10000, 1996, 2, 14);
    g.print();
    g.getBirthday();

    cout<<"-----------------------"<<endl;
    Doctor d("Peter", 21, 140, 20000, 1996, 7, 8, "Doctor Wang");
    d.dump();
    return 0;
}

