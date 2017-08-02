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
	printf("������ѧ������,������10��:\n");
	scanf("%d",&number);

	for(i=0; i < number; i++)
	{
		printf("�������%d��ѧ���ĵ�������\n",i+1);
		scanf("%s",score[i].name);

		printf("������%s����ѧ�����ģ�Ӣ�����Ƴɼ���\n",score[i].name);
		scanf("%d%d%d",&score[i].math,&score[i].chinese,&score[i].english);
		score[i].total = score[i].math+score[i].chinese+score[i].english;
		score[i].average = score[i].total / 3;
	}

	score_sort(score,number);

	printf("��ƽ���ɼ�����Ϊ��\n");
	for(i=0; i<number; i++)
		printf("��%d��%s��\t��ѧ%d\t����%d\tӢ��%d\t�ܷ�%d\tƽ����%d\n",i+1,score[i].name,score[i].math,score[i].chinese,score[i].english,score[i].total,score[i].average);
	
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
