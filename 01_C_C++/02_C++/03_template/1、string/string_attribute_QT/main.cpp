#include<iostream>
#include<string>
using namespace std;

void StrAttribute(void)
{
    /*
     * 容量(capacity)
     * 容量是当前已经申请的内存(即总的大小)
     * 对于VS其申请的空间大小为：((str.size()/16) * 16 + 15)个，即最小15个，每溢出一次增加16个
     * 对于VC++6.0其申请的空间大小为：((str.size()/32) * 32+ 31)个，即最小31个，每溢出一次增加32个
     * QT则是在初始化时，多大的size就多大的capacity(),但是在增加的过程中（若果基数比较小）则成倍增加
     * 如果基数比较大，则会不是成倍增加
    */

    string test(200,'a');
    cout << "capacity:" << test.capacity() << endl;
    test+= "b";
    cout << "capacity:" << test.capacity() << endl;

    string test1(2000,'a');
    cout << "capacity:" << test1.capacity() << endl;
    test+= "b";
    cout << "capacity:" << test1.capacity() << endl;

    string test2(40000,'a');
    cout << "capacity:" << test2.capacity() << endl;
    test+= "bbbb";
    cout << "capacity:" << test2.capacity() << endl;
}
int main(void)
{
    StrAttribute();

    //system("pause");
    return 0;
}
