# include <stdio.h>
int main(void)
{
	float score;

	printf("please input your score(0-100):");
	scanf("%f",&score);

	if (score > 100)
		printf("��������!\n");
	else if(score >=85 && score <=100)//������д�� 85<= score <=100
		printf("����!\n");
	else if(score >=75 && score < 85)
		printf("����!\n");
	else if(score >=60 && score < 75)
		printf("����!\n");
	else if(score >=0 && score < 60)
		printf("������!\n");
	else 
		printf("��������!\n");

	return 0;
}