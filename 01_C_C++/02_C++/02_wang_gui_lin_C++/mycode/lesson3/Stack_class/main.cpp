#include <iostream>
#include "stack.h"

using namespace std;

int main(void)
{
    Stack st(26);

    for(char v='a'; !st.isFill() && v!='z'+1; v++)
        st.push(v);

    while(!st.isEmpty())
        cout<<st.pop()<<" ";
    cout<<endl;

    Stack st2(st);
    while(!st2.isEmpty())
        cout<<st2.pop()<<" ";
    cout<<endl;
#if 0
    /*new的堆中空间要自己释放*/
    Stack * pone = new Stack;
    delete pone;
    /*
     * delete时，系统先调用析构函数，释放构造函数中申请的空间
     * 然后再delete pone，释放pone申请的空间
     *
    */

    Stack * ptwo = new Stack(10);
    Stack * pthree = new Stack;

    delete pthree;
    delete ptwo;
#endif
    return 0;
}

