#include<stdio.h>
# include <stdlib.h>

void sushu(int number)
//也可以用bool sushu(int m){}，最终返回（if）ture或者（else）flase，其处理结果由main函数确定
{
	int i;
	for(i=2; i<number; i++)
	{
		if(number%i == 0)
		break;
	}

	printf("%d可以被%d整除!\n",number,i);
	
	if(i==number)
		printf("是素数!\n");
	else
		printf("不是素数!\n");
}

int main (void)
{	
	int number;
	char ch;

	do
	{
		system("cls");
		system("color 5A");

		printf("Please input your number:\n");
		scanf("%d",&number);

		sushu(number);
		printf("是否要继续？继续按Y，不继续按N.\n");
		scanf(" %c", &ch); //%c前面必须得加一个空格 原因略
	}while(ch=='y'||ch=='Y');

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