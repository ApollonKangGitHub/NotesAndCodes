#include <iostream>
#include "list.h"

using namespace std;

int main()
{
    List link;
    //link.CreateList();//初始化由构造器完成

    for(int i=0; i<10; i++)
        link.AddNode(i);
    link.TraverList();
    return 0;
}

