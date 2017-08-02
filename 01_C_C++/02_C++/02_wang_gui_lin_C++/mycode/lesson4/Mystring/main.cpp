#include <iostream>
#include "mystring.h"

using namespace std;

int main()
{
    cout<<"************* MyString **************"<<endl;

    MyString S1;//默认参数构造
    MyString S2("String S2");//指定参数构造
    MyString S3(S2);//拷贝构造
    MyString S4 = S2;//拷贝构造
    MyString S5;//构造
    S5 = S2;//赋值运算符重载
    MyString S6("String S6");
    MyString S7,S8;//默认参数构造
    S8 = S7 = S6;//连等，赋值运算符重载
    S6 = "String S6/S7/S8";
    S8.operator =(S7.operator =(S6));//等价于S8=S7=S6;

    /*由于<<没有重载，所以暂时用c_str()来输出字符串数组*/
    cout<<"S1:"<<S1.c_str()<<endl;
    cout<<"S2:"<<S2.c_str()<<endl;
    cout<<"S3:"<<S3.c_str()<<endl;
    cout<<"S4:"<<S4.c_str()<<endl;
    cout<<"S5:"<<S5.c_str()<<endl;

    cout<<"S6:"<<S6.c_str()<<endl;
    cout<<"S7:"<<S7.c_str()<<endl;
    cout<<"S8:"<<S8.c_str()<<endl;

    if(S2 == S3)
        cout<<"S2 == S3"<<endl;
    else if(S2 > S3)
        cout<<"S2 > S3"<<endl;
    else
        cout<<"S2 < S3"<<endl;

    cout<<endl;

    MyString a="aaa", b="bbb", c="ccc";
    (a = b) = c;
    cout<<a.c_str()<<endl<<b.c_str()<<endl<<c.c_str()<<endl;

    MyString str1 = "abcd", str2 = "efgh";
    MyString str = str1 + str2;
    cout<<"str1="<<str1.c_str()<<endl;
    cout<<"str2="<<str2.c_str()<<endl;
    cout<<"str=str1+str2="<<str.c_str()<<endl;

    if(str1 == str2)
        cout<<"str1 == str2"<<endl;
    else if(str1 > str2)
        cout<<"str1 > str2"<<endl;
    else
        cout<<"str1 < str2"<<endl;

    str1[0]='f';//重载[]，等价于str1.operator [](0) = 'f';
    cout<<"str1="<<str1.c_str()<<endl;
    cout<<"str2="<<str2.c_str()<<endl;

    if(str1 == str2)
        cout<<"str1 == str2"<<endl;
    else if(str1 > str2)
        cout<<"str1 > str2"<<endl;
    else
        cout<<"str1 < str2"<<endl;

    cout<<"str1[2]="<<str1.at(2)<<endl;

    cout<<str1<<endl;//重载的<<
    cin>>str1;//重载的>>
    cout<<str1<<endl;

    return 0;
}

