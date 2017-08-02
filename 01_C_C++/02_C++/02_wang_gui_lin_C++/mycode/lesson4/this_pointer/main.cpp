#include <iostream>
/*this指针是系统在创建对象时，默认生成的指向当前对象的指针*/
using namespace std;

class Student{
public:
    Student(string name, int age):name(name),age(age)
    {
        cout<<"this:"<<this<<endl;
        #if 0
        this->name = name;//name为参数name、this->name是对象的成员name
        this->age = age;
        #endif
    }

    void display()
    {
        //默认的是this->name与this->age
        cout<<name<<"  "<<age<<endl;
        age=30;
    }
#if 0
    Student * growUP()
    {
        this->age++;
        return this;
    }
#endif
#if 1
    Student & growUP()
    {
        this->age++;
        return *this;
    }
#endif
private:
    string name;
    int age;
};
int main()
{
    Student Mike("Mike", 20);
    cout<<"&Mike:"<<&Mike<<endl;
    Mike.display();//输出20后改为30

    //多次修改age并diaplay输出后，重新改为30
#if 0
    Mike.growUP()->growUP()->growUP()->growUP()->display();
#endif
#if 1
    Mike.growUP().growUP().growUP().growUP().display();
#endif
    Mike.display();//输出30

    return 0;
}

