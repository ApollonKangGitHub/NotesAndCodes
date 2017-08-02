/*
 * <<、>>流的重载：
 * 由于"cout.operator<<(a对象)"不能用
 * （要这样用就必须将重载加入到标准库中，修改标准库是不允许的）
 * 所以只能使用"operator<<(cout, a对象)"即只能使用友元不能用成员
 * 格式比较固定
*/
#include <iostream>

using namespace std;

class Complex{
public:
    Complex(float x=0, float y=0)
        :_x(x),_y(y){}

    void dis(){
        cout<<"("<<_x<<","<<_y<<")"<<endl;
    }
    friend ostream& operator<<(ostream &os, const Complex &c);
    friend ostream& operator>>(ostream &is, Complex &c);
private:
    float _x;
    float _y;
};
ostream& operator<<(ostream &os, const Complex &c)
{
    os<<"("<<c._x<<","<<c._y<<")";
    return os;
}
ostream& operator>>(ostream &is, Complex &c)
{
    is>>c._x;
    is>>c._y;
    return is;
}
int main()
{
    Complex a(1,2), b(5,6);
    cout<<a<<b<<endl;
    operator<<(operator<<(cout, a), b)<<endl;// 等价

    cin >> c;
    //operator>>(cin,c);//等价
    cout<<a<<b<<endl;

    return 0;
}


