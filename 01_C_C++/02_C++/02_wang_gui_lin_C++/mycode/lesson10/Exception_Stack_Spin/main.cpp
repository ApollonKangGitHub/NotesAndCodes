#include <iostream>
using namespace std;
class A
{
    public:
    A(){
        cout<<"A constructor"<<endl;
    }
    A(const A & ){
        cout<<"A copy constructor"<<endl;
    }
    ~A(){
        cout<<"~A destructor"<<endl;
    }
};
int divide(int x, int y){
    A a;
    //A *pa = new A;//栈自旋没有解决异常结束时的堆内存回收问题
    //但是很多情况下：异常处理就是结束进程，堆内存会被系统回收
    //又但是，如果不是结束进程就会有内存泄露的问题
    if(y == 0)
        throw(a);
    return x/y;
}
int myDivide(int x, int y){
    divide(x,y) ;
}
int main(){
    try{
        myDivide(4,0);
    }catch(int x){
        cout<<"x"<<endl;
        cout<<x<<endl;
    }catch(double y){
        cout<<"y"<<endl;
        cout<<y<<endl;
    }catch(const A &a){
        cout<<"no x, no y"<<endl;
    }catch(...){
        cout<<"Exception!"<<endl;
    }
    return 0;
}
