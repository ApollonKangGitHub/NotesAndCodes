/*
 * static成员函数，它的作用只有一个：用于管理static成员变量
 * static成员函数既属于(拥有权)类，也属于(使用权)对象，但终归是属于类的。
 * static修饰的成员函数，因为其本质属于类，所以没有this指针。
 * 并且static没有this的缘故，故其不能访问非static数据成员，也不能访问非static函数成员
 *
*/
#include <iostream>

using namespace std;

class School{
public:
    string &get_lack(){
        return lake;
    }
    static string &get_lib(){
        return lib;
    }

private:
    string lake;
    static string lib;
};

string School::lib = "";

int main()
{
    School::get_lib() = "<<APUE>>\n";
    School::get_lib() += "<<C and Pointer>>\n";
    School XUPT;
    XUPT.get_lack() = "Lover Lack\n";
    School BeiDa;
    BeiDa.get_lack() = "WeiMing Lack\n";

    XUPT.get_lib() += "<<UNIX Socket>>\n";
    BeiDa.get_lib() += "<<China History>>\n";

    cout<<"XiYou:"<<endl;
    cout << XUPT.get_lib();
    cout << XUPT.get_lack() << endl;

    cout<<"Beida:"<<endl;
    cout << BeiDa.get_lib();
    cout << BeiDa.get_lack() << endl;
    return 0;
}

