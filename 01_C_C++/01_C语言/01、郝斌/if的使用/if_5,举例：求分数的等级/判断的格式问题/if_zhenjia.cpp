# include <stdio.h>

int main (void)
{
	float score;

	printf("please input your score :\n");
	scanf("%f",&score);
	
	int i = (90 <= score <=100);//判断结果为逻辑值
	printf("%d\n",i);

	return 0;
}
/*
当score大于等于90时，左边成立为真，右边不执行，
	输出结果为真（1）
当score小于90时，左边为假，右边执行score小于100成立为真，
	输出结果为真（1）


所以结果无论如何为真
*/