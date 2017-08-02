# include <stdio.h>
# include <math.h>
# include <stdlib.h>

int main(void)
{
	double a, b, c;	
	double delta;
	double x1, x2;	
	char ch;
	
	do	
	{	
		system("cls");//清屏函数，包含在stdlib.h库中
		system("color f0");//窗口颜色

		printf("请输入一元二次方程的三个系数:\n");
		printf("a = ");
		scanf("%lf", &a);
		
		printf("b = ");
		scanf("%lf", &b);
		
		printf("c = ");
		scanf("%lf", &c);
		
		delta = b*b - 4*a*c;
		
		if (delta > 0)
		{
			x1 = (-b + sqrt(delta)) / (2*a);
			x2 = (-b - sqrt(delta)) / (2*a);//sqrt()->开方，包含在math.h库中
			printf("有两个解，x1 = %lf, x2 = %lf\n", x1, x2);
		}
		else if (0 == delta)
		{
			x1 = x2 = (-b) / (2*a);
			printf("有唯一解，x1 = x2 = %lf\n", x1, x2);
		}
		else
		{
			printf("无实数解!\n");
		}

		printf("您想继续么，想继续请输入y，不想继续请按n: ");
		scanf(" %c", &ch);  //%c前面必须得加一个空格 原因略
	} while ('y'==ch || 'Y'==ch);
	
	return 0;
}

/*

	system("pause")可以实现冻结屏幕，便于观察程序的执行结果；
	system("CLS")可以实现清屏操作。
	而调用color函数可以改变控制台的前景色和背景，具体参数如下：。
	system("color 0A"); 其中color后面的0A 第一个字符（0）是背景色代号，第二个字符（A）是前景色代号。各颜色代码如下：
	0=黑色 1=蓝色 2=绿色 3=湖蓝色 4=红色 5=紫色 6=黄色 7=白色 8=灰色 
	9=淡蓝色A=淡绿色 B=淡浅绿色 C=淡红色 D=淡紫色 E=淡黄色 F=亮白色

*/