#include <stdio.h>

void Temperature(double n);

int main(void)
{
    double a;
    scanf("%lf",&a);
//	scanf("%.2lf",&a);                //,该写法错误，scanf()不能制定精度！！
    while(a > -273.16)                // 绝对零度不可达
    {
        Temperature(a);
        scanf("%.2lf",&a);
        printf("found2");
    }


    return 0;
}

void Temperature(double n)
{
    const double F_S1 = 1.8;
    const double F_S2 = 32.0;
    const double C_K = 273.16;
    double m = n * F_S1 + F_S2;        //华氏温度转换为摄氏温度
    double o = m + C_K;                //摄氏温度转换为绝对温度

    printf("%.2lf\n",n);
    printf("%.2lf\n",m);
    printf("%.2lf\n",o);
}