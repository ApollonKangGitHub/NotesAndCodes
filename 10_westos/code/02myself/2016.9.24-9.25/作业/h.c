#include<stdio.h>
void graaa(void (*ptrans)(int (*)[4],int n),int (*pa)[4],int n)
{
	ptrans(pa,5);
}
void maa(void (*pt)(int (*)[4],int n),int (*pa)[4],int n)
{
	pt(pa,5);
}
void grape(int (*p)[4],int n)
{	
	int i,j;
	for(i=0;i<n;i++)
		for(j=0;j<3;j++)
			*(*(p+i)+3)+=*(*(p+i)+j);	
}
void max(int (*p)[4],int n)
{
	int i,j,k,max=0;
	for(i=0;i<n;i++)
	if(max<*(*(p+i)+3))
		max=*(*(p+i)+3);
	printf("%d\n",max);
	int min=*(*(p)+3);
	for(i=0;i<n;i++)
	if(min>*(*(p+i)+3))
	 min=*(*(p+i)+3);
	float aver=0;
	for(i=0;i<n;i++)
	aver+=*(*(p+i)+3);
	aver=aver/n;
	for(k=0;k<n;k++)
	{	if(min==*(*(p+k)+3))
		printf("最小为%d号学生成绩为%d\n",k,min);
		 if(max==*(*(p+k)+3))
		printf("最大为%d号学生成绩为%d\n",k,max);
}}
int main()
{
	int i,j;
	int score[5][4]={52,53,44,0,
			34,43,55,0,
			43,54,11,0,
			33,44,53,0,
			22,33,34,0};
//	grape(score,5);
	graaa(grape,score,5);
	for(i=0;i<5;i++)
	{
		printf("\n");
		for(j=0;j<4;j++)
		printf("%d\t",*(*(score+i)+j));
		
	}
	printf("\n");
//	max(score,5);
	maa(max,score,5);
}
