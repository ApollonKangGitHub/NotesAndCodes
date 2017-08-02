#include <iostream>
#include "date.h"
/*
 * C的封装格式：数据与行为方式分离，数据放到struct、以引用或指针的方式传递个行为函数
 * C++认为C的封装不彻底：数据与行为分离且无权限限制。
 * C++封装：数据与行为彻底封装，逻辑抽象、对内数据开放、对外提供接口
 * class默认权限是private私有的，struct默认权限是公有
 * 这是C++中class对C的struct的升级，增加了权限控制
*/
using namespace std;
using namespace Kang;

int main(void)
{
    Date date;
    date.Init();
    date.Print();

    date.GetYear() = 1999;//返回引用居然可以修改protected权限的值：语言层面的Bug

    if(date.IsLeapYear())
        cout<<date.GetYear()<<"is leap year"<<endl;
    else
        cout<<date.GetYear()<<"is not leap year"<<endl;
    return 0;
}

