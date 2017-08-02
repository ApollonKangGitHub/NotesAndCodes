/***
 * 设置默认参数并且存在重载
 *2017年3月7日18:42:40
*/
#include <iostream>

using namespace std;

void print(int a)
{
    cout<<a<<endl;
}

void print(int a, int b = 10)
{
    cout<<a<<"\t"<<b<<endl;
}
int main()
{
    print(1,2);
    /*二义性错误*/
//    print(10);

    /*一个或两个或多个参数的实现，可以采用重载或默认参数来实现，但是对于同一个函数名不能够同时使用*/
    cout << "Hello World!" << endl;
    return 0;
}

