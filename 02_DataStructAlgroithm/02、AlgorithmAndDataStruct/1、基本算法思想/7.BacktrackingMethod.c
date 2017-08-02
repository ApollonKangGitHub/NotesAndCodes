#include<stdio.h>
#define MAXN 5
#define NUM 7

int num[NUM]={0};
int lottcry[MAXN]={0};
void combine(int n, int m)
{
	int i,j;
	for(i=n; i>=m; i--){
		lottcry[m-1]=num[i-1];
		if(m>1)
			combine(i-1,m-1);
		else{
			for(j=MAXN; j>=0; j--)
				printf("%3d",lottcry[j]);
			printf("\n");
		}
	}
}

int main(void)
{
	int i,j;
	for(i=0; i<NUM; i++)
		num[i]=i+1;
	for(i=0; i<MAXN; i++)
		lottcry[i]=0;
	combine(NUM,MAXN);
	return 0;
}