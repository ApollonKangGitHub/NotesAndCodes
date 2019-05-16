# include<stdio.h>
# define NUM1 100
# define NUM2 4

int InScore(int (*score)[NUM2]);
void OutScore(int (*score)[NUM2],int len);
int main(void)
{
	int score[NUM1][NUM2];
	int len = InScore(score);
	OutScore(score,len);
	return 0;
}

int InScore(int (*score)[NUM2])
{
	int choice;
	int i;
	int len=0;
	for(i=0;i<NUM1;++i)
	{
		len++;
		printf("请输入学号为%d的学生成绩：\n",i);
		printf("数学：");
		scanf("%d",&score[i][0]);
		printf("英语：");
		scanf("%d",&score[i][1]);
		printf("C语言：");
		scanf("%d",&score[i][2]);
		score[i][3] = score[i][0]+score[i][1]+score[i][2];
		printf("是否想结束输出？是选1，否选2：");
		scanf("%d",&choice);
		if(choice == 1)
		{
			system("clear");
			return len;
		}
	}
}
void OutScore(int (*score)[NUM2],int len)
{
	int total,i;
	float ave;
	int max_score = score[0][3];
	int min_score = score[0][3];
	int max_number = 0;
	int min_number = 0;

	printf("学号\t数学\t英语\tC语言\t总分\n");
	for(i=0;i<len;++i)
	{
		printf("%d\t%d\t%d\t%d\t%d\n",i,score[i][0],score[i][1],score[i][2],score[i][3]);
		total =total + score[i][3];
		if(score[i][3]>max_score)
		{
			max_score = score[i][3];			
			max_number = i;
		}
		if(score[i][3]<min_score)
		{
			min_score = score[i][3];
			min_number = i;
		}
	}
	ave = total/len;
	printf("总分最高分为:%d\n最低分为：%d\n平均分为：%.2f\n",max_score,min_score,ave);	
	printf("最高分对应的学生学号为：%d，最低分对应的学生学号为：%d\n",max_number,min_number);

}
