#include <iostream>
#include <string.h>
using namespace std;
/*
 * getline()与get()最大的区别就是：
 *
 * get()遇到截止符时，停止读取，但并不会将流中的截止符提取到buf中，
 * 截止符会被下次读取读到(下次读取的截止符是另一个不同的截止符，
 * 如果还是这个截止符，则这次读取数为0)。
 *
 * 而getline提供默认截止符'\n'，也可以自行设定截止符以覆盖默认，
 * 并且getline()遇到截止符号时，虽然停止但是会越过截止符，
 * 不用区手动ignore()。其它与get完全相同
*/
int main()
{
    char buf[1024];

    cin.getline(buf,10);//默认遇到'\n'结束
    cout<<buf<<endl;

    memset(buf, 0, 10);
    cin.getline(buf,100,'i');//遇到'i'结束
    cout<<buf<<endl;
    return 0;
}

