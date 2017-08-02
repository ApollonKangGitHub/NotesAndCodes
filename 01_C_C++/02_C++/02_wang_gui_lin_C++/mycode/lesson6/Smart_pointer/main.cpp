#include <iostream>
#include <memory>
using namespace std;

class A{
public:
    A(){cout<<"A()"<<endl;}
    ~A(){cout<<"~A()"<<endl;}
    void func(){
        cout<<"I'am function in A"<<endl;
    }
    int data;
};
class Smart{//智能指针的简单实现
public:
    Smart(A*p)
        :ptr(p){}
    ~Smart(){
        delete ptr;
    }
    A *operator->(){
        return ptr;
    }
    A& operator *(){
        return *ptr;
    }
private:
    A * ptr;
};
void func1()
{
    A * p = new A;
    delete p;
}
void func2()
{
    //auto_ptr为类模板,auto_ptr<A>为模板类
    //智能指针，自动托管，不需要关心delete的问题
    //delete在ptr离开栈空间的时候发生

    auto_ptr<A> ptr(new A);
    (*ptr).func();
    ptr->func();//ptr为对象，其行为表现的像一个指针，是因为重载了->和.
}
void func3()
{
    Smart smt(new A);
    smt->func();//需要重载->
    (*smt).func();//需要重载*
}
int main()
{
    func1();
    cout<<endl;
    func2();
    cout<<endl;
    func3();
    return 0;
}

