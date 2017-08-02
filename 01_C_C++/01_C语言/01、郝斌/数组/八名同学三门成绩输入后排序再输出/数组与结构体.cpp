# include <stdio.h>

typedef struct StudentScore
{
	double score1;
	double score2;
	double score3;
	double score;
}SCORE;

void swap (void * a, void *b, size_t size);
void score_sort(SCORE * a,int size);

int main (void)
{
	SCORE score[8];
	printf("请依次输入三门成绩以空格分隔，下一个同学回车换行输入:\n");

	for(int i=0; i<8; i++)
	{
		scanf("%lf%lf%lf",&score[i].score1 ,&score[i].score2 ,&score[i].score3 );
		score[i].score= score[i].score1+score[i].score2+score[i].score3;
	}

	score_sort(score,8);

	for(int j=0; j<8; j++)
	{
		printf("%.2lf\t",score[j].score);
		printf("%.2lf\t%.2lf\t%.2lf\t",score[j].score1,score[j].score2,score[j].score3);
		putchar('\n');
	}
	
	return 0;
}

void score_sort(SCORE * a,int size)
{
	int min;
	for(int i=0; i<size; i++)
	{
		min = i;
		for(int j=i+1; j<size; j++)
		{
			if(a[min].score > a[j].score)
				min = j;
		}
		if(min != i)
			swap(&a[min].score,&a[i].score,sizeof(double));
	}
}

void swap(void * a, void *b, size_t size)
{
	unsigned char * p = (unsigned char *)a;
	unsigned char * q = (unsigned char *)b;
	unsigned char medium;

	while(size--)
	{
		int mediun = *p;
		*p = *q;
		*q = mediun;
		p++;
		q++;
	}

	return;
}
