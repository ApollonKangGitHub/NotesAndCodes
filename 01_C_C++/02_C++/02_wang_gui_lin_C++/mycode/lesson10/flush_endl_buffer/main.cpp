/*
 * 该代码在Windows上运行看不出效果
 * 需要在Linux上运行
*/
#include <iostream>
#include <unistd.h>
#include <stdio.h>

using namespace std;

int main()
{
    int i = 1;
    char * buf = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
    while(i++ > 0){
        printf("%d",i);
        cout<<i;
        cout<<buf;
        usleep(1000);
    }
    /*
         刷新缓冲区的方式：flush()、\n、flush、endl、unitbuf：
         cout<<i<<endl;//会换行刷新输出
         cout<<i<<flush;//不会换行刷新输出
         cout<<i<<unitbuf;//不会换行,等下一次输出时/程序结束时，刷新输出上一次
         cout<<unitbuf<<i;//不会换行,直接刷新输出本次
    */
    return 0;
}

