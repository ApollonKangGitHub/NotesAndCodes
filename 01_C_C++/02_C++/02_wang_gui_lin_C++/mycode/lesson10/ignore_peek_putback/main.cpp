#include <iostream>

using namespace std;

int main()
{
    /*
     * 用“I like C/          I like C++ aslo/”做测试
     */
    char buf[1024];
    cin.get(buf, 1024, '/');

    cin.ignore(100,'I');//忽略100个，到I为止(I也会被忽略)
    char peek = cin.peek();//查看缓冲区指针当前所在位置的字符(应为空格)
    cout<<"peek:"<<peek<<endl;
    cin.putback('I');//将多忽略的I退回来(指针从当前的缓冲区位置移动到I的位置)
    peek = cin.peek();//应为“I”
    cout<<"peek:"<<peek<<endl;

    cout<<buf<<endl;
    cin.get(buf, 1024, '/');
    cout<<buf<<endl;

    return 0;
}

