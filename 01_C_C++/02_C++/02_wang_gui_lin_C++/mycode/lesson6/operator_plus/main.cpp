#include <iostream>

using namespace std;

class Complex{
public:
    Complex(float x=0, float y=0)
        :_x(x),_y(y){}

    void dis(){
        cout<<"("<<_x<<","<<_y<<")"<<endl;
    }
    friend const Complex operator+(Complex &a, Complex &b);//友元函数
    //const Complex operator+(Complex &another);//成员函数
private:
    float _x;
    float _y;
};

#if 1
const Complex operator+(Complex &a, Complex &b){
    Complex tmp;
    tmp._x = a._x + b._x;
    tmp._y = a._y + b._y;
    return tmp;
}
#endif

#if 0
const Complex Complex::operator+(Complex &another){
    Complex tmp;
    tmp._x = this->_x + another._x;
    tmp._y = this->_y + another._y;

    return tmp;
}
#endif
int main()
{
    Complex a(1,2), b(3,4);
    Complex c;
    c = a+b;
    a.dis();
    b.dis();
    c.dis();

    //(a+b) = c;
    //重载运算符返回值为const类型，所以说const是很重要的限定，
    //防止一些非法的赋值方式
    return 0;
}


