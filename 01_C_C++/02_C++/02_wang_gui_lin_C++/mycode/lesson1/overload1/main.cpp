/*重载原则：
 *①函数名相同，函数参数列表不同(类型、个数、顺序)
 *②匹配原则1：严格匹配，找到再调用
 *③匹配原则2：通过隐式类型转换寻求一个匹配，找到则调用
 *④返回值类型不构成重载条件
 *⑤二义性：如果计算机存在有两种隐式转换选择，计算机不会去选，而报二义性错误
 * eg1：double可以截断为float和int，如果abs(-4.4)并且只注释掉double的ads则会产生二义性
 * eg2：double->int/float会产生两义性，int->long/double也会产生两义性；即两个特例
 * 为了避免重载中的二义性问题，使用时按所需强制转换，不要让计算机去选择

 *同一个名字因为参数列表不同，展现了不同的结果，也叫静多态
*/
#include <iostream>

using namespace std;

float abs(float i){
    return (i >= 0 ? i : -i);
}

double abs(double i){
    return (i >= 0 ? i : -i);
}

int abs(int i){
    return (i >= 0 ? i : -i);
}

int main()
{
    /*abbiguous二义性*/
    float i = abs(-5.5f);/*默认调用第一个*/
//    float j = abs(-4.4);/*默认调用第二个*/
    cout << i << endl;
    cout << j << endl;

    /*浮点数默认大小(类型)*/
    cout << "sizeof(4.5)=" << sizeof(4.5) << endl;/*default*/
    cout << "sizeof(4.5f)=" << sizeof(4.5f) << endl;
    return 0;
}

