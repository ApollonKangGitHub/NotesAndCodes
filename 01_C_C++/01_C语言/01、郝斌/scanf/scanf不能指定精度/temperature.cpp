#include <stdio.h>

void Temperature(double n);

int main(void)
{
    double a;
    scanf("%lf",&a);
//	scanf("%.2lf",&a);                //,��д������scanf()�����ƶ����ȣ���
    while(a > -273.16)                // ������Ȳ��ɴ�
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
    double m = n * F_S1 + F_S2;        //�����¶�ת��Ϊ�����¶�
    double o = m + C_K;                //�����¶�ת��Ϊ�����¶�

    printf("%.2lf\n",n);
    printf("%.2lf\n",m);
    printf("%.2lf\n",o);
}