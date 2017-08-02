/*reference本质就是对裸露的指针的包装
 *引用的优点(相对于指针)：
 * ①不需要开辟新的空间
 * ②对于函数传参，不会直接暴露变量地址
*/
#include <iostream>

using namespace std;

void Swap(int *a, int *b)/*传指针*/
{
    *a ^= *b ^= *a ^= *b;
}
void Swap(int &a, int &b)/*传引用*/
{
    a ^= b ^= a ^= b;
}
int main()
{
    int a = 10, b = -20;
    cout<<"a= "<<a<<"\tb= "<<b<<endl;
    Swap(&a,&b);
    cout<<"a= "<<a<<"\tb= "<<b<<endl;
    Swap(a,b);
    cout<<"a= "<<a<<"\tb= "<<b<<endl;

    return 0;
}

