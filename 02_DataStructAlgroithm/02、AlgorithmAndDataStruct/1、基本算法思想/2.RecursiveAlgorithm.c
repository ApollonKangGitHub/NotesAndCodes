/*
 *2017��4��9��15:37:23
 *�����㷨��
 *˳�Ʒ������Ʒ�
 *
 *˳�Ʒ�������֪�����������������Ҫ�������ķ���(�磺쳲���������)
 *���Ʒ�������֪����������õ������ʽ������������ʼ����(˳�Ʒ��������)
 *
 *���⣺
 *˳�Ʒ�����쳲�������˳�Ʒ�����������Ϊ��(С����3���³�Ϊ���ò��ҿ�����һ��С���ӣ����N�����ܹ��ж���ֻ����)
 *���Ʒ�����һ���´��һ��Ǯ��ÿ����ĩȡ1000������������ȡ������ϢΪ1.71%�������24������������ȡ��1000Ԫ�����һ���´��˶���Ǯ
*/

void FibonacciRabbit(void);//˳����������
void Retroduction(void);//�����󱾽���

#include<stdio.h>

int main(void)
{
	FibonacciRabbit();//Ҳ����������Ԫ�ش�С�������ó�(����û��������)
	printf("===================================\n");
	//Retroduction();//����Ԫ�شӴ�С����ó�(Ҳ���Բ�������������������еķ���)
	return 0;
}

void FibonacciRabbit(void)
{
	/*�����֪�����������쳲��������У�����ⷽ���Ͳ�����ͬ*/
	int last_one_month = 1, last_two_month = 1, month_num = 1;/*��һ���£��������£���ǰ��*/
	int month, n;
	printf("����������:\n");
	scanf("%d",&month);

	printf("��1������������Ϊ��%d\n",last_two_month);
	printf("��2������������Ϊ��%d\n",last_one_month);
	for(n = 3; n<=month; n++){//ǰ������Ϊ1�����޸�month_num�ĳ�ʼֵ
		month_num = last_one_month + last_two_month;
		last_two_month = last_one_month;
		last_one_month = month_num;
		printf("��%d������������Ϊ��%d\n",n,month_num);
	}
}
void Retroduction(void)
{
	//(��һ�������*(1+0.0171/12)) - 1000 = �������
	//��һ������� = (�������+1000)/(1+0.0171/12)

	const double interest = 0.0171;//����Ϣ
	const double withdraw = 1000;//ÿ��ȡ��
	int month;

	double money[25];
	money[24] = 1000;
	
	for(month = 23; month > 0; month--){
		money[month] = (money[month+1] + withdraw)/(1+interest/12);
		printf("��%d���µ����Ϊ��%.3lf\n", month, money[month]);
	}
}