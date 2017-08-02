# include <stdio.h>
int main(void)
{
	float score;

	printf("please input your score(0-100):");
	scanf("%f",&score);

	if (score > 100)
		printf("输入有误!\n");
	else if(score >=85 && score <=100)//不可以写成 85<= score <=100
		printf("优秀!\n");
	else if(score >=75 && score < 85)
		printf("良好!\n");
	else if(score >=60 && score < 75)
		printf("及格!\n");
	else if(score >=0 && score < 60)
		printf("不及格!\n");
	else 
		printf("输入有误!\n");

	return 0;
}