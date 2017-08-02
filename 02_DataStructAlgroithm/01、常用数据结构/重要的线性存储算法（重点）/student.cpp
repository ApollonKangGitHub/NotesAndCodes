# include <stdio.h>
# include <stdlib.h>

typedef struct student
{
	int math;
	int chinese;
	int english;
	int total;
	int average;
	char name[10];
}STU,* PSTU;

void score_sort(PSTU score,int size);

int main(void)
{
	STU score[10];
	int i,j;
	int number;
	printf("请输入学生人数,不多于10人:\n");
	scanf("%d",&number);

	for(i=0; i < number; i++)
	{
		printf("请输入第%d个学生的的姓名：\n",i+1);
		scanf("%s",score[i].name);

		printf("请输入%s的数学，语文，英语三科成绩：\n",score[i].name);
		scanf("%d%d%d",&score[i].math,&score[i].chinese,&score[i].english);
		score[i].total = score[i].math+score[i].chinese+score[i].english;
		score[i].average = score[i].total / 3;
	}

	score_sort(score,number);

	printf("按平均成绩排序为：\n");
	for(i=0; i<number; i++)
		printf("第%d名%s：\t数学%d\t语文%d\t英语%d\t总分%d\t平均分%d\n",i+1,score[i].name,score[i].math,score[i].chinese,score[i].english,score[i].total,score[i].average);
	
	return 0;
}

void score_sort(PSTU score,int size)
{
	int i,j;
	for(i=0; i<size; i++)
	{
		for(j=i+1; j<size; j++)
		{
			if(score[i].average > score[j].average)
			{
				STU temp = score[i];
				score[i] = score[j];
				score[j] = temp;
			}
		}
	}

}
