#include "mystring.h"

MyString::MyString(const char *p)
{
    if(p == NULL){
        _str = new char[1];
        *_str = '\0';
    }else{
        int len = strlen(p);
        _str = new char[len];
        strcpy(_str, p);
    }
}

/*******************************************************************
 * 拷贝构造器：
 * 格式：A（const A & another);
 * 若不自定义，则默认是系统自定义
 * 系统提供的拷贝构造器，默认是一个等位拷贝，即江湖上说的“浅浅的拷贝”
 * 浅拷贝会导致内存重析构，(double free),但是内存重析构在Windows上可能不会报错
 * 在有些情况(含有堆空间的时候)，要自实现拷贝构造
********************************************************************/
MyString::MyString(const MyString & another)
{
    //_str = another._str;//系统默认浅拷贝
    //同类对象之间无隐私，异类对象之间有友元
    #if 1

    int len = strlen(another._str);
    _str = new char[len];
    strcpy(_str, another._str);

    #endif
}

/*******************************************************************
 * 赋值运算符重载：
 * 格式：A& operator=(A& another);
 * 系统/编译器提供默认重载,
 * 默认赋值运算符重载也是一种等位赋值（浅赋值），若是自定义，编译器不再提供
 * 浅复制不但会导致重析构，还会导致自身内存泄漏；
 * 对于自赋值
********************************************************************/

MyString& MyString::operator=(const MyString & another)
{
    if(this == &another)
        return *this;//自赋值，不会删除自身空间，排除自赋值逻辑错误
    delete []this->_str;//先删除自身，否则会导致内存泄露
    int len = strlen(another._str);//求赋值对象的长度
    this->_str = new char[len+1];//根据赋值对象为被赋值对象创建新的空间
    strcpy(this->_str, another._str);//复制

    return *this;//返回this以实现连等：a = b = c = d;
}

MyString MyString::operator+(const MyString & another)
{
    MyString tmp;
    delete []tmp._str;

    int len = strlen(this->_str);
    len += strlen(another._str);
    tmp._str = new char[len+1];
    /*
     * 一定要清空，有可能有的平台会自动初始化堆空间为0(如Linux)
     * 但是为了跨平台性与安全性，还是要初始化清空
    */
    memset(tmp._str, 0, len+1);

    strcat(tmp._str, this->_str);
    strcat(tmp._str, another._str);

    return tmp;
}
bool MyString::operator>(const MyString & another)
{
    if(strcmp(this->_str,another._str) > 0)
        return true;
    else
        return false;
}
bool MyString::operator<(const MyString & another)
{
    if(strcmp(this->_str,another._str) < 0)
        return true;
    else
        return false;
}
bool MyString::operator==(const MyString & another)
{
    if(strcmp(this->_str,another._str) == 0)
        return true;
    else
        return false;
}
char& MyString::operator[](int idx)//返回指定位置字符的引用以便修改
{
    return this->_str[idx];
}
char MyString::at(int idx)//只是读取，返回字符串即可
{
    return this->_str[idx];
}
char * MyString::c_str()
{
    return _str;
}
MyString::~MyString()
{
    delete []_str;
}
ostream& operator<<(ostream &os, const MyString &s)
{
    os<<s._str;
    return os;
}
istream& operator>>(istream &is, MyString &s)
{
    delete s._str;
    char buf[4096];//设置的值必须要防止输入很长而溢出

    is>>buf;//scanf("%s",buf);
    int len = strlen(buf);
    s._str = new char[len+1];
    strcpy(s._str, buf);

    return is;
}
