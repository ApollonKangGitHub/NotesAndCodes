#ifndef MYSTRING_H
#define MYSTRING_H

#include <stdio.h>
#include <string.h>

#include <iostream>
using namespace std;

class MyString
{
public:
    MyString(const char *p = NULL);
    MyString(const MyString & another);
    MyString& operator=(const MyString & another);
    MyString operator+(const MyString & another);
    bool operator>(const MyString & another);
    bool operator<(const MyString & another);
    bool operator==(const MyString & another);
    friend ostream& operator<<(ostream &os, const MyString &s);
    friend istream& operator>>(istream &is, MyString &s);
    char& operator[](int idx);
    char at(int idx);
    char * c_str();
    ~MyString();
private:
    char * _str;
};

#endif // MYSTRING_H
