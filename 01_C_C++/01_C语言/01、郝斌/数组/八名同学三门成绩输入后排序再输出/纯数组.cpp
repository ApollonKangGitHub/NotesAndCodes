# include <stdio.h>
# define NUM 8
void swap (void * a, void * b, size_t size);
void choose (int * a,int size);

int main (void)
{
	int score1[NUM];
	int score2[NUM];
	int score3[NUM];
	int score[NUM];

	printf("Please input score(score1 score2 score3),between space:\n");

	for(int i=0; i<NUM; i++)
	{
		scanf("%d%d%d",&score1[i],&score2[i],&score3[i]);
		score[i] = score1[i]+score2[i]+score3[i];
	}
	choose(score,NUM);

	for(int j=0; j<NUM; j++)
	{
		printf("%d\t",score[j]);
		printf("%d\t%d\t%d\t",score1[j],score2[j],score3[j]);
		printf("\n");
	}
	
	return 0;
}

void choose (int * a,int size)
{
	int min;
	for(int i=0; i<size; i++)
	{
		min = i;
		for(int j=i+1; j<size; j++)
		{
			if(a[min] > a[j])
				min = j;
		}
		if(min != i)
			swap(&a[min],&a[i],sizeof(int));
	}
}

void swap(void * a, void * b, size_t size)
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
