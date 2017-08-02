#include <iostream>
using namespace std;
class Stu
{
public:
    //Stu(string n):_name(n){}
    Stu(string n = ""):_name(n){}
    void dis()
    {
     cout<<_name<<endl;
    }
private:
    string _name;
};
int main()
{
    // Stu s; //没有无参构造器
    Stu s[5]= {Stu("zhangsan"),Stu("lisi")};//不能指定个数但是只部分初始化，否则会报错。
    Stu * ps = new Stu[4]{Stu("zhangsan")};
    // C11 中支持此种初始化方法，但必须对指定的类个数初始化,否则会报错。

    s[0].dis();
    s[1].dis();
    s[4].dis();
    ps[0].dis();

    return 0;
}
