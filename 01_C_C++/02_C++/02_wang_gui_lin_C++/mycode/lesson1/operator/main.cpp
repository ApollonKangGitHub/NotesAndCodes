#include <iostream>
/*C++中一切运算符都被视为函数，虽然函数可以重载，有一小部分运算符不能重载*/
using namespace std;

struct Complex{//复数
    int real;
    int image;
};
Complex operator+(Complex a, Complex b)
{
    Complex c;
    c.real = a.real + b.real;
    c.image = a.image + b.image;

    return c;
}

int main()
{
    Complex a = {4,3};
    Complex b = {5,6};

    Complex c = a + b;
    cout<< "c.real:" << c.real << endl << "c.image:" << c.image << endl;
/*相当于函数调用*/
    Complex d = operator+(a, b);
    cout<< "d.real:" << d.real << endl << "d.image:" << d.image << endl;
    return 0;
}

