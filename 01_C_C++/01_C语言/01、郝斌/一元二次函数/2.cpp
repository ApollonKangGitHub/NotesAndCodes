//一元二次方程ax2+bx+c=0
# include <stdio.h>
# include <math.h>
int main(void)
{
	//把三个系数保存到计算机中	
	int a = 1;
	int b = 2;
	int c = 1;//等号为赋值之意
	float delta;//delt存放的是b*b - 4*a*c
	float x1,x2;//存放方程的解

	delta = b*b - 4*a*c;

	if(delta>0)
	{
		x1 = (-b + sqrt(delta)) / (2*a);
		x2 = (-b - sqrt(delta)) / (2*a);//两个解
		printf("该一元二次方程有两个解，分别为：x1 = %f, x2 = %f\n",x1);
	}
	else if(delta==0)
	{
		x1 = (-b) / (2*a);
		x2 = x1;
		printf("该一元二次方程有唯一解为：x1 = x2 = %f\n",x1,x2);
	}
	else
	{
		printf("该一元二次方程无解");	
	}
	return 0;
}