#include <iostream>
#include <fstream>

using namespace std;
//不能传fstream fs和fstream *fs，因为这两种方式都会调用拷贝构造器
void func(fstream &fs)
{}
int main()
{
    fstream fs;
    //fstream fs2(fs);//会调用拷贝构造器，而所有流类的拷贝构造器都是私有的
    fstream fs3;
    //fs3 = fs;//会调用赋值运算重载，而所有的流类的赋值运算都是私有的
    //所以流类对象不可以赋值或者复制

    func(fs);
    return 0;
}

