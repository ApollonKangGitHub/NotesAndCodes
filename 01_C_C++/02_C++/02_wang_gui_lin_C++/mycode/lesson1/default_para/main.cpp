/*默认参数的规则：
 *若存在多个参数
 * 必须从右往左默认，并且不能跳跃设置默认
 * 即若设置的默认参数，其右边的任意一个参数没有设置默认，则是不能成立的
 * 原因是为了方便识别
 * 并且在调用时，传递的参数个数不能少于未设置默认参数的个数，不能多于函数参数总个数
*/

//若定义声明为一体，则默认参数定义和声明为一体
//若声明在前，定义在后，即定义声明分开，则默认参数需要写到声明，而不能写到定义
#include <iostream>
#include <time.h>
#include <Windows.h>
using namespace std;

#define DAY 30
void WeatherCast(string w = "haze")/*默认的天气值是霾（haze）*/
{
    time_t t = time(NULL);
    char tmp[64];
    strftime(tmp, sizeof(tmp), "%Y/%m/%d %X %A\t", localtime(&t));
    cout << tmp << "Today weather is " << w << endl;
}
int main()
{
    int i = 0;
    for(i = 0; i < DAY; i++){
        if(i == 15)
            WeatherCast("Sunshine");
        else if(i == 18)
            WeatherCast("Rainy");
        else
            WeatherCast();/*默认雾霾*/
        Sleep(1000);
    }
 //   WeatherCast("SunShine");

    return 0;
}

