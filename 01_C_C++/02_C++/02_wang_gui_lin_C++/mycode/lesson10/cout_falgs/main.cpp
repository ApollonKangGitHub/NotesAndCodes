#include <iostream>
#include <iomanip>//引入流算子
using namespace std;

int main()
{
    int i = 0X12345678;
#if 0
    /*比较麻烦，不再使用，而采用#include <iomanip>中的流算子来代替*/
    cout<<i<<endl;//int类型默认是十进制输出格式

    cout.unsetf(ios::dec);//先关了十进制
    cout.setf(ios::hex);//再开启十六进制
    cout<<i<<endl;

    cout.unsetf(ios::hex);
    cout.setf(ios::dec);
    cout<<i<<endl;
#endif
#if 0
    cout<<hex<<i<<endl;
    cout<<dec<<i<<endl;
    cout<<oct<<i<<endl;
#endif
    /*
     * 设置域宽setw(n)
     * 设置填充字符setfill(c),需要与setw()合用
     * 设置对齐格式：setiosflags(ios::left)/setiosflags(ios::right)
     *
    */
#if 0
    double d1 = 10/2, d2 = 10.3/3;
    cout<<d1<<endl;//默认不显示小数点及其之后的.000000
    cout<<setiosflags(ios::showpoint)<<d1<<endl;//强制显示
    cout<<setiosflags(ios::showpos)<<d2<<endl;//显示正负号

    //setprecision(n)//设置精度(有效数字位数)，自动四舍五入
    cout<<resetiosflags(ios::showpos);
    double d = 1.23456;
    cout<<d<<endl;
    cout<<setprecision(0)<<d<<endl;
    cout<<setprecision(1)<<d<<endl;
    cout<<setprecision(2)<<d<<endl;
    cout<<setprecision(3)<<d<<endl;
    cout<<setprecision(4)<<d<<endl;
#endif
#if 0
    //设置浮点数显示方法：科学计数法/定点数法
    double dd = 321.23456;
    cout<<dd<<endl;
    cout<<setiosflags(ios::scientific)<<dd<<endl;//设置为科学计数法
    cout<<resetiosflags(ios::scientific)<<dd<<endl;//取消科学计数法的设置
    cout<<setiosflags(ios::fixed)<<dd<<endl;//设置为定点显示
    cout<<setprecision(64)<<setiosflags(ios::fixed)<<dd<<endl;//设置小数精度
#endif

    int num = 0XFFFFFFFF;
    cout<<hex<<num<<endl;//十六进制默认小写
    cout<<setiosflags(ios::uppercase)<<num<<endl;//设置为大写
    cout<<resetiosflags(ios::uppercase)<<num<<endl;//取消大写设置
    return 0;
}

