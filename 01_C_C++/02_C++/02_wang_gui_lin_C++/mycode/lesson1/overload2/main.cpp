/*重载原理：name mangling(命名倾轧)
 *声明定义阶段与操作阶段均会进行倾轧(编译阶段)
 *使用extern ""，可以将某函数不倾轧，可C++需要倾轧以支持重载，为什么弄一个不倾轧出来呢
 *
 *分析：
 *C++要兼容C，就必须兼容(C语法与C库)，C库只在连链接时，加入，不存在倾轧，而C++会倾轧，
 *要想使用不参加倾轧的C库函数，C++中编译时就不能倾轧C的头文件中对于库函数的声明
 *即C库中已经不能改动，既不能倾轧，则必须将头文件中的声明也设置为不倾轧，以此对应
 *可以查看C的头文件，可以发现其中有一个extern "C"，表示不倾轧C的函数声明
*/
#include <iostream>
#include <string.h>
using namespace std;
/*//设置为不倾轧
extern "C"//extern也被重载，即声明其中函数不进行倾轧
{
    void func(int a){
        cout<<"a = "<<a<<endl;
    }
    void func(char a){
        cout<<"a = "<<a<<endl;
    }
    void func(int a, char b){
        cout<<"a = "<<a<<endl<<"b = "<<b<<endl;
    }
    void func(char a, int b){
        cout<<"a = "<<a<<endl<<"b = "<<b<<endl;
    }
}
*/
//不设置，C++编译器默认倾轧
void func(int a){
    cout<<"a = "<<a<<endl;
}
void func(char a){
    cout<<"a = "<<a<<endl;
}
void func(int a, char b){
    cout<<"a = "<<a<<endl<<"b = "<<b<<endl;
}
void func(char a, int b){
    cout<<"a = "<<a<<endl<<"b = "<<b<<endl;
}

/*倾轧原理,底层自动转换成类似于下面的格式*/
void func_i(int a){
    cout<<"a = "<<a<<endl;
}
void func_c(char a){
    cout<<"a = "<<a<<endl;
}
void func_ic(int a, char b){
    cout<<"a = "<<a<<endl<<"b = "<<b<<endl;
}
void func_ci(char a, int b){
    cout<<"a = "<<a<<endl<<"b = "<<b<<endl;
}

int main(void){
    int a = 10;
    char b = 'b';

    func(a);
    func(b);
    func(a,b);
    func(b,a);

    cout<<"name mangling:"<<endl;
    /*调用时根据类型，自动倾轧成相应格式。先检测存在与否，不存在则根据隐式转换后的形式，再倾轧*/
    func_i(a);
    func_c(b);
    func_ic(a,b);
    func_ci(b,a);

    return 0;
}

/*查看string.h，在函数声明之前就声明extern "C"，即不倾轧

#ifndef _INC_STRING
#define _INC_STRING

#ifdef __cplusplus  //如果是C++编译器就要进行不倾轧设置
extern "C" {
#endif

... //函数声明等

#ifdef __cplusplus//与上面匹配
}
#endif
*/
