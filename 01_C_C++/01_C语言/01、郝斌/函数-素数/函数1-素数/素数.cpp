#include<stdio.h>
# include <stdlib.h>

void sushu(int number)
//Ҳ������bool sushu(int m){}�����շ��أ�if��ture���ߣ�else��flase���䴦������main����ȷ��
{
	int i;
	for(i=2; i<number; i++)
	{
		if(number%i == 0)
		break;
	}

	printf("%d���Ա�%d����!\n",number,i);
	
	if(i==number)
		printf("������!\n");
	else
		printf("��������!\n");
}

int main (void)
{	
	int number;
	char ch;

	do
	{
		system("cls");
		system("color 5A");

		printf("Please input your number:\n");
		scanf("%d",&number);

		sushu(number);
		printf("�Ƿ�Ҫ������������Y����������N.\n");
		scanf(" %c", &ch); //%cǰ�����ü�һ���ո� ԭ����
	}while(ch=='y'||ch=='Y');

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