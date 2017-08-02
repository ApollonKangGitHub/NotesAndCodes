/*
 * 1、C++ 不能被重载的四个运算符：
 * ①.成员选择符
 * ②.*成员对象选择符
 * ③::域解析符
 * ④?:条件操作符
 * ⑤sizeof
 *
 * 2、可以被重载的运算符：
 * new、new[]、delete、delete[]、+、-、*、/、%、^、&、|、~、&&、||、！
 * >、<、=、==、+=、-=、/=、*=、%=、^=、&=、|=、>>、<<、<<=、>>=、！=
 * ++、--、<=、>=、,、->、->*、()、[]
 * 其中：=、()、[]、->、->*只能被重载为成员函数而不能重载为友元，
 * 一元运算符、与等号相关的（除了==）二元运算符建议重载为成员函数
 * 而其他的二元运算符重载为友元
 *
 * 通常情况下：
 * 双目运算符重载时，重载在友元中需要两个参数，重载在成员函数中需要一个参数(已经包含this)
 * 同理单目运算符重载时，友元时需要一个参数，成员时需要0个参数
 * 三目不能重载
 * 特别注意：对于运算符的重载不能失去其原有意义！！
 *
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
    Complex operator+(Complex &another);
    Complex & operator+=(const Complex &another);
    Complex operator-()const;//单目运算符：负号重载
private:
    float _x;
    float _y;
};

Complex Complex::operator+(Complex &another){
    Complex tmp;
    tmp._x = this->_x + another._x;
    tmp._y = this->_y + another._y;

    return tmp;
}
Complex & Complex::operator+=(const Complex &another){
    this->_x += another._x;
    this->_y += another._y;

    return *this;
}
Complex Complex::operator-()const
{
    return (Complex(-this->_x,-this->_y));
}
int main()
{
#if 0
    Complex a1(10,0), b1(10,0), c1(20,0);

    a1.dis();   b1.dis();   c1.dis();
    //b1 += a1;   c1 += b1;
    //(c1 += b1) += a1;//等价于c1+=b1; c1+=a1;
    c1 += b1 += a1;
    a1.dis();   b1.dis();   c1.dis();
#endif

#if 1
    Complex t1(10,-10);
    Complex t2 = -t1;
    Complex t3 = -(-t1);//等价于t3 = (t1.operator-()).operator-();
    t1.dis();
    t2.dis();
    t3.dis();
#endif
    return 0;
}


