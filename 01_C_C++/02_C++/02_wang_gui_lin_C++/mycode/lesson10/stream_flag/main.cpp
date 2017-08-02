#include <iostream>

using namespace std;

int main()
{
    int integerVal;
    cout<<"Before a bad inout operation:"<<endl;
    cout<<"cim.eof():"<<cin.eof()<<endl;
    cout<<"cin.fail():"<<cin.fail()<<endl;
    cout<<"cin.bad():"<<cin.bad()<<endl;
    cout<<"cin.good():"<<cin.good()<<endl;

    cin>>integerVal;// 输入字符a或者Ctrl+z测试
    cout<<"Before a bad inout operation:"<<endl;
    cout<<"cim.eof():"<<cin.eof()<<endl;
    cout<<"cin.fail():"<<cin.fail()<<endl;
    cout<<"cin.bad():"<<cin.bad()<<endl;
    cout<<"cin.good():"<<cin.good()<<endl;

    cin.clear();//标志位重置
    cout<<"Before a bad inout operation:"<<endl;
    cout<<"cim.eof():"<<cin.eof()<<endl;//eof()是一种fail()
    cout<<"cin.fail():"<<cin.fail()<<endl;//fail()不是一种eof()
    cout<<"cin.bad():"<<cin.bad()<<endl;
    cout<<"cin.good():"<<cin.good()<<endl;


    return 0;
}

