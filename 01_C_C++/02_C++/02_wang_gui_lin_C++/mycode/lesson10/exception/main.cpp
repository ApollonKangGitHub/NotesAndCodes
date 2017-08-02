#include <iostream>
#include <cmath>
using namespace std;

class A{
public:
    A(int i, int j, int k):_a(i),_b(j),_c(k){}
    double _a;
    double _b;
    double _c;
};
double triangle(double x, double y, double z)
{
    double area;
    double s = (x+y+z)/2;
    if(x+y>z && y+z>x && x+z >y)
        area = sqrt(s*(s-x)*(s-y)*(s-z));
    else
        throw A(x,y,z); //throw 数据为任意类型(类对象也可以)，但是必须与catch匹配
    return area;
}
int main()
{
    int a, b,c;
    cin>>a>>b>>c;
    try{
        while(a>0&&b>0&&c>0){
            cout<<triangle(a,b,c)<<endl;
            cin>>a>>b>>c;
            }
    }catch(int e){//try与catch的花括号不能省略
        //catch与throw必须类型匹配，否则匹配不到，
        //调用系统的异常处理，自动结束
        //但是一个try可以配多个catch，以匹配throw的不同异常类型
        //catch(...)表示接受类型匹配不上的，类似于swtich的default
        cout<<"catch a exception "<<e<<endl;
        cout<<a<<","<<b<<","<<c<<" ";
        cout<<"can't construct a triangle!"<<endl;
    }
    catch(A a){
        cout<<"catch a exception ";
        cout<<"a:"<<a._a<<" b:"<<a._b<<" c:"<<a._c<<endl;
    }
    catch(...){
        cout<<"catch a exception "<<endl;
    }
    return 0;
}
