# include <stdio.h>

int main (void)
{	
	char ch;
	printf("������i��");
	int i;
	scanf("%d",&i);
	printf("i = %d\n",i);

	while ((ch=getchar()) !='\n')
		continue;
	printf("������j��");
	int j;
	scanf("%d",&j);
	printf("j = %d\n",j);

/*	while ((ch=getchar()) !='\n')
		continue;
*/
	printf("������k��");
	int k;
	scanf("%d",&k);
	printf("k = %d\n",k);

	return 0;
}
/*
while ((ch=getchar()) !='\n')
		continue;
		�öγ�����������Ϊ���������ַ�����Ʒ���ʽ��һ��ʱ��
		���Զ����Ƿ����ݣ���������Ʒ���ʽ��ͬ�����ݣ�����������Ʒ��������
		����Ժ�������Ӱ�졣
*/