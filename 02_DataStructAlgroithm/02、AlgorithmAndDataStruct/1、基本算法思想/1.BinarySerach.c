/*
 *2017��4��9��15:11:27
 *���ַ�����Ʒ�۸����Ϸ
*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int RandomPrice(void);
int GuessPrice(int);

int main(void)
{
	const int price = RandomPrice();
	int guess;
	while(1){
		if(guess = GuessPrice(price)){
			break;
		}
	}
}

int RandomPrice(void)
{
	srand(time(NULL));//����
	return rand()%1000;
}

int GuessPrice(const int price)
{
	int guess_price;
	printf("���������µļ۸�(�۸�����Ϊ[0,999]):\n");
	scanf("%d",&guess_price);
	system("cls");
	if(guess_price == price){
		printf("��ϲ�����ˣ�\n");
		return 1;
	}
	else{
		if(guess_price > price){
			printf("�µĴ���,�����²�:\n");
		}
		else{
			printf("�µ�С��,�����²�:\n");
		}
		return 0;
	} 
}