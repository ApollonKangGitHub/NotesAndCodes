#include <iostream>

using namespace std;

#if 0
//四种强转
static_cast         //静态类型转换：隐式类型转化时，可以用此类型
reinterpret_cast    //重解释类型转换：双向都不能隐式转换（即无隐式转换），就用此类型
const_cast          //(脱)常类型转换：只能应用于指针和引用

dynamic_cast        //动态类型转换：用于多态中的父子类之间的强制转化
#endif

int main()
{
//static_cast
    int a=5;
    float b=10.12;

    a = static_cast<float>(b);
    b = static_cast<int>(a);

    void *q;
    int *p;

    p = static_cast<int *>(q);//void *到其它类型指针需要强转
    q = p;

    int x = 10;
    int y = 3;
    float z = static_cast<float>(x)/y;
    cout<<z<<endl;
//reinterpret_cast
    int arr[5] = {1, 2, 3, 4, 5};
    int *parr = reinterpret_cast<int*>(reinterpret_cast<int>(arr)+1);

    cout<<hex<<"*p:"<<*parr<<endl;

    /*
     *
     *int aa;
     *int bb[10];
     *双向隐式转换都报错，就用reinterpret_cast强转
     *aa = bb;
     *bb = aa;
    */

//const_cast
    /*脱常时表现行为怪异*/
    const int acon = 19;
    int &racon = const_cast<int &>(acon);
    racon = 200;
    cout<<dec<<"acon="<<acon<<"\t"<<"racon="<<racon<<endl;/*值不同*/
    cout<<hex<<"&acon="<<&acon<<"\t"<<"&racon="<<&racon<<endl;/*地址相同*/

    int *pacon = const_cast<int *>(&acon);
    * pacon = 400;
    cout<<dec<<"acon="<<acon<<"\t"<<"*pacon="<<*pacon<<endl;/*值不同*/
    cout<<hex<<"&acon="<<&acon<<"\t"<<"&pacon="<<&pacon<<endl;/*地址不同*/

    struct A{int data;};
    const A xx = {1111};

    /*自定义可以脱常*/
    A &a1 = const_cast< A&>(xx);/*脱常*/
    a1.data = 222;
    cout<<dec<<a1.data<<"\t"<<xx.data<<endl;
    A *p1 = const_cast<A*>(&xx);
    p1->data = 333;
    cout<<p1->data<<"\t"<<xx.data<<endl;

/*
 * 用const_cast修改以后，其结果是令人不可思议的，MSDN上解释说：
 *
 * 可以改变 const 自定义类的成员变量，但是对于内置数据类型(引用、指针)
 * 却表现未定义行为(不同平台结果各异).
 *
 * Depending on the type of the referenced object, a write operation through
 * the resulting pointer, reference, or pointer to data member might produce
 * undefined behavior.
 *
*/
    return 0;
}

