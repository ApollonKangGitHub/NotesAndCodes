/*
 *2017年4月9日15:11:27
 *二分法猜商品价格的游戏
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
	srand(time(NULL));//种子
	return rand()%1000;
}

int GuessPrice(const int price)
{
	int guess_price;
	printf("请输入您猜的价格(价格区间为[0,999]):\n");
	scanf("%d",&guess_price);
	system("cls");
	if(guess_price == price){
		printf("恭喜猜中了！\n");
		return 1;
	}
	else{
		if(guess_price > price){
			printf("猜的大了,请重新猜:\n");
		}
		else{
			printf("猜的小了,请重新猜:\n");
		}
		return 0;
	} 
}