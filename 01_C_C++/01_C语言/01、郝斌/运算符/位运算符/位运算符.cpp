# include <stdio.h>
# include <stdlib.h>
int main (void)
{
	char ch;

	do
	{
		system("cls");
		system("color 0A");

		int i,j,k;

		printf("������Ҫ����λ������������֣�i��j����\n");
		scanf("%d,%d",&i,&j);

		k = i & j;//��λ��
		printf("%d\n",k);

		k = i | j;//��λ��

		printf("%d\n",k);//ע�⵱��λ����ʱ��������һλΪ1����������Ϊ����������������ֵΪ����Ҫȡ����1֮��ȡ�෴����

		k = i ^ j;//��λ���
		printf("%d\n",k);

		k = ~ j;//��λȡ��
		printf("%d\n",k);

		printf("�Ƿ��������Y/N��:");
		scanf(" %c",&ch);

	}while('Y' == ch || 'y'==ch);

	return 0;
}