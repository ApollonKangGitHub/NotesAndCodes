#include <stdio.h>
#include <stdlib.h>
#define MAX 5
#define T_Num 2

void shellsort(int A[], int N);
void printarray(int A[]);

int main()
{
	int i, s[MAX];

	for (i = 0; i < MAX; i++)
	s[i] = 1+(int) (100.0*rand()/(RAND_MAX+1.0));//rand()随机数生成函数

	printf("before   :"); 
	printarray(s);
	shellsort(s, MAX);
	return 0;
}
void shellsort(int V[], int n)
{
	int gap, i, j, temp;
	gap = n/T_Num;
	bool flag = false;
	while(gap > 0) 
	{
		printf("\ngap = %d\t\tV[j] - V[j+gap]\n", gap); 
		for (i = gap; i < n; i++) 
		{
			printf("i = %d\t\t", i);

			for (j = i-gap; j>=0; j -= gap) 
			{
				if (V[j] > V[j+gap]) 
				{
					temp = V[j];
					V[j] = V[j+gap];
					V[j+gap] = temp;
				}
				printf("[%2d]-[%2d]  ", j, j+gap); 
			}
			printf("\n");
		}
		printf("after gap(%d):", gap); 
		printarray(V);
		gap /= T_Num;

		if(!flag&&(gap<=1))
		{
			gap = 1;
			flag = !flag;
		}
	}
}
void printarray(int a[])
{
	int i;
	for (i = 0; i < MAX; i++)
	printf(" %d", a[i]);
	printf("\n");
}