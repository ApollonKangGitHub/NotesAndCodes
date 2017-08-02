/*
 *不可以定义引用的引用(int && a)，但是可以为引用再次引用(int &ra = a;int &rra = ra;)
 *可以定义指针的指针(int *& a)，但不能定义引用的指针(int &* a)
 *可以定义指针数组(int *a[n])，不能定义引用数组(int &a[n])，但是能声明数组引用()
 *可以取引用的地址，但是不能定义引用的指针。
*/
#include <iostream>

using namespace std;

int main()
{
    /*①引用*/
    int a = 10;
    int &ra = a;//right
    int &rra = ra;//right
    //int &&rra = ra;//error,因为引用不是定义，不能像指针那样多级使用

    /*②指针*/
    int b = 20;
    int * pb = &b;//right
    int ** ppb = &pb;//right
    int ***pppb = &ppb;//right

    //指针是嵌套使用
    //引用是线性声明
    //即存在双指针，不存在双引用

    /*③指针与引用*/
    int t = 30;
    int &rt = t;
    int * pt = &t;//right
    int *& n = pt;//right,只能为指针声明引用
    //int &* m = &rt;//error,不能为引用定义指针

    /*数组与引用*/
    int a,b,c;
    int *arr[] = {&a, &b, &c};//right
    //int &ref_arr[] = {a, b, c};//error,等价于int &* ref_arr
    int b[] = {1,2,3,4,5,5};
    int (&arr_ref)[] = b;//right,等价于int *&arr_ref = b;

    return 0;
}

