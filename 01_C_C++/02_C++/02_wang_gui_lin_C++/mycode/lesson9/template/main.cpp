/*
 * 函数模板基本语法：
 * template<typename/class 类型参数表>
 * 返回类型 函数模板名(函数参数列表){
 *      函数模板定义体
 * }
 * 调用时：
 * 函数模板名<类型>(参数列表);或者不用写“<类型>”
 *
 * 函数模板的短板也是非常明显：参数个数必须相同
 *
*/
#include <iostream>

using namespace std;

/*函数模板：根据具体的类型，产生模板函数*/
template<typename T>
void Swap(T&a, T&b)
{
    T t = a;
    a = b;
    b = t;
}
int main()
{
    int ia=4,ib=5;
    double da=4.01,db=5.01;
    char ca='a',cb='b';

    Swap(ia,ib);//Swap<int>(ia,ib);
    Swap(da,db);//Swap<double>(da,db);
    Swap(ca,cb);//Swap<char>(ca,cb);

    cout<<ia<<","<<ib<<endl;
    cout<<da<<","<<db<<endl;
    cout<<ca<<","<<cb<<endl;

    return 0;
}

