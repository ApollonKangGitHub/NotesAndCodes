/*
 * 对于命名空间重名的
 * 如果两个重名的空间中无重名的函数、变量等
 * 这两个命名空间就会被合并
 *
*/
#include <iostream>
#include "cat.h"
#include "dog.h"
#include "automan.h"

using namespace Animal;
using namespace Robot;
using namespace std;

int main()
{
    Dog Heizi;
    Cat Mimi;
    Automan Aidi;
    return 0;
}

