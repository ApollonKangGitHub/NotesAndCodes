# include <stdio.h>
# include <stdlib.h>

int main(void)
{
	long sum1 = 1;
	long sum2 = 1;
	long t;
	int k,n;
	char ch;

	do
	{
		system("cls");

		point:printf("��ֱ��������Ҫ���ҵ�����n(���������������ƣ�������0<n<47)��\n");
		scanf("%d",&n);
		system("cls");
		if(n<=0 || n>=47)
		{
			printf("����������������룺\n");
			goto point;
		}
		for(k=n;k>1;k--)
		{
			sum1 = sum1+sum2;
			t = sum1;
			sum1 =sum2;
			sum2 =t;
		}
		printf("쳲��������е�%d��Ϊ:%ld\n",n,sum1);
		printf("�������Ƿ�������ң������밴y���˳��밴n:\n");
		scanf(" %c",&ch);

	}while(ch == 'y' || ch == 'Y');

	
	return 0;
}