/*

	������ת����16������
	2016��5��23��18:03:51

*/


# include <stdio.h>
# include <stdlib.h>
# define MAX 8
union FloatData  //���������ڴ���ÿ����������ʼ��ַ��ͬ��
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
		
			printf("��������Ҫ��ѯ����������(���������е���ĸ��ʾ������)��\n");
			printf("short(s)  int(i)  long(l)  float(f)  double(d)\n");
			
			scanf("%c",&ch);
			switch(ch)
			{
			case 's':
				printf("������һ��short��������");
				scanf("%d",&t.s);
				printf("%d���ڴ��еĴ��Ϊ��",t.s);
				len = sizeof(short);
				break;
			case 'i':
				printf("������һ��int��������");
				scanf("%d",&t.i);
				printf("%d���ڴ��еĴ��Ϊ��",t.i);
				len = sizeof(int);
				break;
			case 'l':
				printf("������һ��long��������");
				scanf("%ld",&t.l);
				printf("%ld���ڴ��еĴ��Ϊ��",t.l);
				len = sizeof(long);
				break;
			case 'f':
				printf("������һ����������");
				scanf("%f",&t.f);
				printf("%f���ڴ��еĴ��Ϊ��",t.f);
				len = sizeof(float);
				break;
			case 'd':
				printf("������һ����������");
				scanf("%lf",&t.d);
				printf("%lf���ڴ��еĴ��Ϊ��",t.d);
				len = sizeof(double);
				break;
			default:
				system("cls");
				printf("��������Ͳ��ڴ���Χ�ڣ����������룺\n");
				POINT = true;
				break;
			}
		}
		for(int i=len-1; i>=0; --i)
			printf("%4X",t.h[i]);
		printf("\n");

}
