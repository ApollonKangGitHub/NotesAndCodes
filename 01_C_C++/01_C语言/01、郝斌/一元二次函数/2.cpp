//һԪ���η���ax2+bx+c=0
# include <stdio.h>
# include <math.h>
int main(void)
{
	//������ϵ�����浽�������	
	int a = 1;
	int b = 2;
	int c = 1;//�Ⱥ�Ϊ��ֵ֮��
	float delta;//delt��ŵ���b*b - 4*a*c
	float x1,x2;//��ŷ��̵Ľ�

	delta = b*b - 4*a*c;

	if(delta>0)
	{
		x1 = (-b + sqrt(delta)) / (2*a);
		x2 = (-b - sqrt(delta)) / (2*a);//������
		printf("��һԪ���η����������⣬�ֱ�Ϊ��x1 = %f, x2 = %f\n",x1);
	}
	else if(delta==0)
	{
		x1 = (-b) / (2*a);
		x2 = x1;
		printf("��һԪ���η�����Ψһ��Ϊ��x1 = x2 = %f\n",x1,x2);
	}
	else
	{
		printf("��һԪ���η����޽�");	
	}
	return 0;
}