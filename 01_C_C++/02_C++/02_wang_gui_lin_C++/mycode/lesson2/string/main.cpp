#include <iostream>
#include <string.h>
//string不是关键字，而是一个std命名空间下的类
using namespace std;

int main()
{
/* 赋值、初始化的方式与重载的运算符等操作*/
    string str1("Hello_one");
    string str2 = "Hello_two";
    cout << "str1 = " << str1 << endl;
    cout << "str2 = " << str2 << endl;
    str2 = str1;
    cout << "str2 = " << str2 << endl;

    str1="China ";
    cout<<"str1 = "<<str1<<"\tsizeof()="<<str1.size()<<endl;
    str2 = "is great";
    cout<<"str2 = "<<str2<<"\tsizeof()="<<str2.size()<<endl;

    str1 += str2;//+=被重载，-未被重载(因为意义不大)
    cout<<"str1+str2 = "<<str1<<"\tsizeof()="<<str1.size()<<endl;

    str2[1] = 'A';//[]被重载
    cout<<"str2 = "<<str2<<endl;

    char buf[20] = {};
    strcpy(buf, str2.c_str());//c.str()返回char*
    cout<<"buf = "<<buf<<endl;

    str1.swap(str2);//等效于str2.swap(str1)
    cout << "str1 = " << str1 << endl;
    cout << "str2 = " << str2 << endl;

    /*查找*/
/*
int find(char c, int pos = 0);
int find(char * s, int pos = 0);
返回下标值，没有找到返回-1，默认从 0 下标开找
*/
    int n = str2.find('C',0);
    cout<<"n = "<<n<<endl;
    n = str2.find("ina",0);
    cout<<"n = "<<n<<endl;

/*string的输入*/
    string str3;
    cin>>str3;//cin时输入空格，空格之后的不会被写入str3
    cout<<"str3 = " <<str3<< endl;

    if(str1 == str3)//直接可以比较，因为==、>、<均在string类中被重载
        cout<<"str1 = str3"<<endl;
    else if(str1 > str3)
        cout<<"str1 > str3"<<endl;
    else
        cout<<"str1 < str3"<<endl;

    return 0;
}

