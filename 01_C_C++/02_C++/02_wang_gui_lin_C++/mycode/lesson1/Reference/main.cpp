/*
 *引用并非定义，只是一种关系型声明。声明它与原有某一变量的关系（与原变量地址绑定）
 *声明的变量类型与原变量保持一致，不分配内存，公共用一块地址。即除了名字，其它均相同
 *声明时必须初始化，一经声明，不可变更
 *可对引用再次引用，多次引用的结果使得原始变量拥有多个别名
 *
*/
#include <iostream>

using namespace std;

int main()
{
    int a = 10;
    int &ra = a;/*b是a的别名。b即是a，a即是b*/
    cout<<"a = "<<a<<"\tra ="<<ra<< endl;

    ra = 100;

    int &rra = ra;

    cout<<"a = "<<a<<"  ra = "<<ra<<"  rra = "<<rra<<endl;
    cout<<"&a = "<<&a<<"  &ra = " <<&ra<<"  &rra = "<< &rra <<endl;
    cout<<"sizeof(a) = "<<sizeof(a)<<"  sizeof(ra) = "<<sizeof(ra)<<"  sizeof(rra) = "<<sizeof(rra)<<endl;

    return 0;
}

