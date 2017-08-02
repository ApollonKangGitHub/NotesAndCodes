#include<iostream>
#include<iomanip>

using namespace std;

int main(void)
{
    int a = 100;
    float b = 1.23456;

    printf("*********************\n");
    /*设置右对齐占8字符*/
    printf("%8d\n",a);
    cout<<setw(8)<<a<<endl;/*#include<iomanip>,setw()为设置域宽，默认右对齐*/

    /*设置左对齐占8字符*/
    printf("%-8d\n",a);
    cout<<setiosflags(ios::left)<<setw(8)<<a<<endl;

    /*设置精确度与域宽*/
    printf("%10.2f\n",b);
    cout<<setw(10)<<setiosflags(ios::right)<<setprecision(2)<<setiosflags(ios::fixed)<<b<<endl;

    printf("%o\n",a);
    printf("%d\n",a);
    printf("%x\n",a);

    cout<<oct<<a<<endl;/*八进制*/
    cout<<dec<<a<<endl;/*十进制*/
    cout<<hex<<a<<endl;/*十六进制*/

    /*注意：上一步按十六进制输出，之后就默认成了上一次的设置，而不像C那样暂时性按格式输出*/
    cout<<setfill('x')<<setw(20)<<a<<endl;

    int hour = 17, min = 3, sec = 20;
    /*时钟需要将输出格式恢复到十进制*/
    cout<<dec<<setfill('0')<<setw(2)<<hour<<":"<<setw(2)<<min<<":"<<setw(2)<<sec<<endl;/*setfill()可以只设置一次，而setw必须每次设置*/
    return 0;
}
