/*
 * 1、一个操作符的左右操作数不一定是相同类型的对象，这就涉及到将该操作符函数定义为谁的友元，谁的成员问题。
 * 2、一个操作符函数，被声明为哪个类的成员，取决于该函数的调用对象(通常是左操作数)。
 * 3、一个操作符函数，被声明为哪个类的友员，取决于该函数的参数对象(通常是右操作数)
*/
#include <iostream>
using namespace std;

class Mail;//前向性声明，Sender的关于Mail的成员函数定义则不能放在类中

class Sender
{
public:
    Sender(string s):_addr(s){}
    Sender& operator<<(const Mail & mail); //成员
private:
    string _addr;
};

class Mail
{
public:
    Mail(string _t,string _c ):_title(_t),_content(_c){}
    friend Sender& Sender::operator<<(const Mail & mail);//友元
private:
    string _title;
    string _content;
};
Sender& Sender::operator<<(const Mail & mail)
{
    cout<<"Address:"<<_addr<<endl;
    cout<<"Title :"<<mail._title<<endl;
    cout<<"Content:"<<mail._content<<endl;
    return *this;
}
int main()
{
    Sender sender("MailBox_krj@163.com");
    Mail mail("note","meeting at 3:00 pm");
    Mail mail2("tour","One night in Xi'an");
    sender<<mail<<mail2;
    return 0;
}
