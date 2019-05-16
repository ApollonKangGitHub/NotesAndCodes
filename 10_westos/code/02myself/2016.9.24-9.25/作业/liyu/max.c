#include "common.h"
void max(int (*p)[4],int n)
{
	int i,j,k,max=0;
	for(i=0;i<n;i++)
	if(max<*(*(p+i)+3))
		max=*(*(p+i)+3);
//	printf("%d\n",max);
	int min=*(*(p)+3);
	for(i=0;i<n;i++)
	if(min>*(*(p+i)+3))
	 min=*(*(p+i)+3);
	float aver=0;
	for(i=0;i<n;i++)
	aver=aver+(*(*(p+i)+3));
	aver=aver/5;
	printf("平均成绩为%f\n",aver);
	for(k=0;k<n;k++)
	{	if(min==*(*(p+k)+3))
		printf("最小为%d号学生成绩为%d\n",k,min);
		 if(max==*(*(p+k)+3))
		printf("最大为%d号学生成绩为%d\n",k,max);
}}
