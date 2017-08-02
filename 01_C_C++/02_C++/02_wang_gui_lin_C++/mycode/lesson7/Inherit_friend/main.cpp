#include <iostream>
using namespace std;

class Student{
public:
    Student(int a, int b)
        :_a(a),_b(b){}
    friend ostream &operator<<(ostream & out, Student & stu);
    ~Student(){cout<<"~Student"<<endl;}
private:
    int _a;
    int _b;
};
//如果“Student & stu”前加const，那么Graduate的赋值重载中类型转换就可以不加&
ostream &operator<<(ostream & out, Student & stu){
    cout<<"Student stu:"<<endl;
    out<<stu._a<<"--"<<stu._b<<endl;

    return out;
}
class Graduate:public Student{
public:
    Graduate(int a, int b, int c, int d)
        :Student(a,b),_c(c),_d(d){}
#if 1
    friend ostream &operator<<(ostream & out, Graduate & gra);
#endif
    ~Graduate(){cout<<"~Graduate()"<<endl;}
private:
    int _c;
    int _d;
};
#if 1
/*子类的赋值重载*/
ostream &operator<<(ostream & out, Graduate & gra)
{
    cout<<"Graduate gra:"<<endl;
    //调用父类的赋值重载，如果是直接cout<<gra<<endl;则会死循环栈溢出
    //out<<(Student&)gra<<endl;
    out<<static_cast<Student&>(gra);
    out<<gra._c<<"--"<<gra._d<<endl;

    return out;
}
#endif
int main()
{
    Student a(1,2);
    cout<<a<<endl;

    Graduate g(1,2,3,4);
    cout<<g<<endl;//找不到本类的赋值重载，则隐式转换并调用了父类的赋值重载
    return 0;
}
