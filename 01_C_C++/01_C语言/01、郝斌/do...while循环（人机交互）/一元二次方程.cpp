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
		system("cls");//����������������stdlib.h����
		system("color f0");//������ɫ

		printf("������һԪ���η��̵�����ϵ��:\n");
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
			x2 = (-b - sqrt(delta)) / (2*a);//sqrt()->������������math.h����
			printf("�������⣬x1 = %lf, x2 = %lf\n", x1, x2);
		}
		else if (0 == delta)
		{
			x1 = x2 = (-b) / (2*a);
			printf("��Ψһ�⣬x1 = x2 = %lf\n", x1, x2);
		}
		else
		{
			printf("��ʵ����!\n");
		}

		printf("�������ô�������������y����������밴n: ");
		scanf(" %c", &ch);  //%cǰ�����ü�һ���ո� ԭ����
	} while ('y'==ch || 'Y'==ch);
	
	return 0;
}

/*

	system("pause")����ʵ�ֶ�����Ļ�����ڹ۲�����ִ�н����
	system("CLS")����ʵ������������
	������color�������Ըı����̨��ǰ��ɫ�ͱ���������������£���
	system("color 0A"); ����color�����0A ��һ���ַ���0���Ǳ���ɫ���ţ��ڶ����ַ���A����ǰ��ɫ���š�����ɫ�������£�
	0=��ɫ 1=��ɫ 2=��ɫ 3=����ɫ 4=��ɫ 5=��ɫ 6=��ɫ 7=��ɫ 8=��ɫ 
	9=����ɫA=����ɫ B=��ǳ��ɫ C=����ɫ D=����ɫ E=����ɫ F=����ɫ

*/