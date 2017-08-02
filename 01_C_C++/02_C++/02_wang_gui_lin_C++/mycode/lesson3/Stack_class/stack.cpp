#include <iostream>
#include <string.h>
#include "stack.h"
/*注意：WindowsQT的头文件不区分大小写*/

using namespace std;

Stack::Stack(const Stack & another)
{
    space = new char[another._size];
    memcpy(space, another.space, another._size);
    top = another._size;
    _size = another._size;
    //mem系列函数与str系列函数的一个区别就是：str*是以'\0'作为标志，而mem*以指定长度为标准

}
bool Stack::isEmpty(){
    return (top == 0);
}
bool Stack::isFill(){
    return (top == _size);
}
void Stack::push(char c){
    space[top++] = c;
}
char Stack::pop(){
    return (space[--top]);
}
