# include <stdio.h>
# include <stdlib.h>
# include <conio.h>

void system_conversion(int * p,int * q);//进制转化函数


int main (void)
{
	char ch;
	do
	{
		int num;
		int k;//虽然system是进制的意思，但不能int system；因为清屏函数system("cls")会因定义的常量system而被判定为不是一个函数（而是一个常量）。

		system("cls");

		printf("请输入您要转化的十进制数字:\n");
		scanf("%d",&num);
		printf("请输入您要转化进制类型(例如：2):\n");
		scanf("%d",&k);

		system_conversion(&num,&k);
		printf("您要继续吗？(y 或 n):\n");
		scanf(" %c",&ch);
	}while(ch =='y' || ch == 'Y');
	
	getch();
	return 0;
}

void system_conversion(int * p,int * q)
{
	int num = *p;
	int k = *q;
	char length[100];
	itoa(num,length,k);//包含在stdlib.h库中的进制转化函数，itoa(a,b,c)中a为要转化的数字，b为转化后的内容按字符串格式输出，c为转化类型
	printf("十进制数%ld转化为%d进制数为%s\n",num,k,length);

	return;	
}
