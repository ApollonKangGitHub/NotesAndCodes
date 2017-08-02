/*先设置断点：在具体行号边点击右键设置
 *点击进行调试
 *查看汇编代码
 *比较压栈过程
*/
#include <iostream>

using namespace std;

#define N 200 //在预处理阶段替换
int main()
{
    //int a = 200;//每次使用a，都要去a的地址空间区提取a的值
    const int a = 200;//每次使用a都是直接用200，而不是取a的空间去找a的值
    int b= 10;
    int c;
    c = b + 200;
    //c = b + N；

    return 0;
}

