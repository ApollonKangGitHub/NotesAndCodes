# include <stdio.h>
# include <stdlib.h>
# include <conio.h>

void system_conversion(int * p,int * q);//����ת������


int main (void)
{
	char ch;
	do
	{
		int num;
		int k;//��Ȼsystem�ǽ��Ƶ���˼��������int system����Ϊ��������system("cls")������ĳ���system�����ж�Ϊ����һ������������һ����������

		system("cls");

		printf("��������Ҫת����ʮ��������:\n");
		scanf("%d",&num);
		printf("��������Ҫת����������(���磺2):\n");
		scanf("%d",&k);

		system_conversion(&num,&k);
		printf("��Ҫ������(y �� n):\n");
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
	itoa(num,length,k);//������stdlib.h���еĽ���ת��������itoa(a,b,c)��aΪҪת�������֣�bΪת��������ݰ��ַ�����ʽ�����cΪת������
	printf("ʮ������%ldת��Ϊ%d������Ϊ%s\n",num,k,length);

	return;	
}
