/*注意事项：
 *   1)只有类的成员函数才能声明为虚函数
 *      虚函数仅适用于有继承关系的类对象，所以普通函数不能声明为虚函数。
 *   2)静态成员函数不能是虚函数
 *      静态成员函数不受对象的捆绑，只有类的信息。
 *   3)内联函数不能是虚函数
 *   4)构造函数不能是虚函数(复制构造也是构造)
 *      构造时，对象的创建尚未完成。构造完成后，才能算一个名符其实的对象。
 *   5)析构函数可以是虚函数且通常声明为虚函数
*/
#include <iostream>
#include "dog.h"
#include "cat.h"
using namespace std;

int main()
{
#if 0
    Dog dog;
    dog.voice();

    Cat cat;
    cat.voice();

    Animal* ani = &dog;
    ani->voice();
    ani = &cat;
    ani->voice();
#endif
    Animal * ani = new Dog;
    ani->voice();

    delete ani;

    return 0;
}

