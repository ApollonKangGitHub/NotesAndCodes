#include<stdio.h>
#include <stdlib.h>

void main()
{ 
 int i=0,j=0,n=0;
 printf("请输入n:");
 scanf("%d",&n);//矩阵阶数
 int **p=NULL;//二维指针，存放矩阵n*n个元素
 p= (int**)malloc(n*sizeof(int*));//先分配n个一维指针
 if(NULL==p)
  exit(1);
 for (i = 0; i < n ; i++)
 {
  p[i] = (int*)malloc(n*sizeof(int));//为n个一维指针分配n个整型大小的空间
  if (NULL==p[i])
   exit(1);
 }
 int flag=n;//剩下矩阵的阶数控制循环
 int row=0,cloumn=0;//行列标记，初始计数为0
 while(flag)
 {
  if (flag%2)//矩阵阶数为奇数，为左下侧行列赋值
  {
   for (i=0;i<flag;i++)
    p[row+flag-1][cloumn+flag-1-i]=flag*flag-i;
   for (j=1;j<flag;j++)
    p[row+flag-1-j][cloumn]=p[row+flag-1][cloumn]-j;
   cloumn++;//拆去一行一列，影响下次循环列下标，加1
  }
  else//为偶数，为右上侧行列赋值
  {
   for (i=0;i<flag;i++)
    p[row][cloumn+i]=flag*flag-i;
   for (j=1;j<flag;j++)
    p[row+j][cloumn+flag-1]=p[row][cloumn+flag-1]-j;
   row++;//拆去一行一列，影响下次循环行下标，加1
  }
  flag--;//剩下矩阵的阶数
 }
 printf("%d*%d阶矩阵为：\n",n,n);
 i=n;
 while(i--)
  printf("*******");
 printf("\n");
 for(i=0;i<n;i++)
 {   
  for(j=0;j<n;j++)
   printf("%d\t",p[i][j]);
  printf("\n\n");  
      }
 
 for (i = 0; i < n; i++)
  free(p[i]);
 free(p);
}