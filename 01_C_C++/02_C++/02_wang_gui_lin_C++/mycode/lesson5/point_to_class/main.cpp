#include <iostream>

using namespace std;

class Kangruojin{
public:
    Kangruojin(){
        arr[0] = fun0;
        arr[1] = fun1;
        arr[2] = fun2;
        arr[3] = fun3;
    }
    void select(int idx){
        (this->*arr[idx])();//根据->*找到偏移位置的值
    }
private:
     void fun0(){cout<<"void fun()0"<<endl;}
     void fun1(){cout<<"void fun()1"<<endl;}
     void fun2(){cout<<"void fun()2"<<endl;}
     void fun3(){cout<<"void fun()3"<<endl;}

     enum{num=4};
     void (Kangruojin::*arr[num])(void);
};

void (*arr[4])(int);
int main()
{
    Kangruojin k;
    k.select(1);
    k.select(2);
    k.select(3);
    return 0;
}

