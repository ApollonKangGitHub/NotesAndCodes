/*

	浮点数转换成16进制数
	2016年5月23日18:03:51

*/


# include <stdio.h>
# include <stdlib.h>
# define MAX 8
union FloatData  //共用体在内存中每个变量的起始地址相同。
{
	double d;
    float f;
	long int l;
	int i;
	short int s;
	
    unsigned char h[MAX];
}; 
void main(void)
{

		int len;
		FloatData t;
		int POINT = true;
		while(POINT)
		{
			POINT = false;
			char ch;
		
			printf("请输入您要查询的数据类型(输入括号中的字母表示该类型)：\n");
			printf("short(s)  int(i)  long(l)  float(f)  double(d)\n");
			
			scanf("%c",&ch);
			switch(ch)
			{
			case 's':
				printf("请输入一个short型整数：");
				scanf("%d",&t.s);
				printf("%d在内存中的存放为：",t.s);
				len = sizeof(short);
				break;
			case 'i':
				printf("请输入一个int型整数：");
				scanf("%d",&t.i);
				printf("%d在内存中的存放为：",t.i);
				len = sizeof(int);
				break;
			case 'l':
				printf("请输入一个long型整数：");
				scanf("%ld",&t.l);
				printf("%ld在内存中的存放为：",t.l);
				len = sizeof(long);
				break;
			case 'f':
				printf("请输入一个浮点数：");
				scanf("%f",&t.f);
				printf("%f在内存中的存放为：",t.f);
				len = sizeof(float);
				break;
			case 'd':
				printf("请输入一个浮点数：");
				scanf("%lf",&t.d);
				printf("%lf在内存中的存放为：",t.d);
				len = sizeof(double);
				break;
			default:
				system("cls");
				printf("输入的类型不在处理范围内，请重新输入：\n");
				POINT = true;
				break;
			}
		}
		for(int i=len-1; i>=0; --i)
			printf("%4X",t.h[i]);
		printf("\n");

}
