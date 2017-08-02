/*
 *2017年4月9日15:37:23
 *递推算法：
 *顺推法与逆推法
 *
 *顺推法：由已知条件除法，逐步推算出要解决问题的方法(如：斐波那契数列)
 *逆推法：由已知结果除法，用迭代表达式推算出问题的起始条件(顺推法的逆过程)
 *
 *例题：
 *顺推法：以斐波那契的顺推法求兔子数量为例(小兔子3个月成为大兔并且可以生一个小兔子，求第N个月总共有多少只兔子)
 *逆推法：第一个月存放一笔钱，每月月末取1000，银行整存零取的年利息为1.71%，如果第24个月连本带利取到1000元，求第一个月存了多少钱
*/

void FibonacciRabbit(void);//顺推球兔子数
void Retroduction(void);//逆推求本金数

#include<stdio.h>

int main(void)
{
	FibonacciRabbit();//也可以用数组元素从小到大计算得出(这里没有用数组)
	printf("===================================\n");
	//Retroduction();//数组元素从大到小计算得出(也可以不用数组而用类似上题中的方法)
	return 0;
}

void FibonacciRabbit(void)
{
	/*如果不知道其规律满足斐波那契数列，则求解方法就不尽相同*/
	int last_one_month = 1, last_two_month = 1, month_num = 1;/*上一个月，上两个月，当前月*/
	int month, n;
	printf("请输入月数:\n");
	scanf("%d",&month);

	printf("第1个月兔子总数为：%d\n",last_two_month);
	printf("第2个月兔子总数为：%d\n",last_one_month);
	for(n = 3; n<=month; n++){//前两个月为1不用修改month_num的初始值
		month_num = last_one_month + last_two_month;
		last_two_month = last_one_month;
		last_one_month = month_num;
		printf("第%d个月兔子总数为：%d\n",n,month_num);
	}
}
void Retroduction(void)
{
	//(上一个月余额*(1+0.0171/12)) - 1000 = 本月余额
	//上一个月余额 = (本月余额+1000)/(1+0.0171/12)

	const double interest = 0.0171;//年利息
	const double withdraw = 1000;//每月取得
	int month;

	double money[25];
	money[24] = 1000;
	
	for(month = 23; month > 0; month--){
		money[month] = (money[month+1] + withdraw)/(1+interest/12);
		printf("第%d个月的余额为：%.3lf\n", month, money[month]);
	}
}