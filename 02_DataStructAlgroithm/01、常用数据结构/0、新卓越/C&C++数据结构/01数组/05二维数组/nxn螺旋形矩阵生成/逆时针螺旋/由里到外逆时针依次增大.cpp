#include<stdio.h>
#include <stdlib.h>

void main()
{ 
 int i=0,j=0,n=0;
 printf("������n:");
 scanf("%d",&n);//�������
 int **p=NULL;//��άָ�룬��ž���n*n��Ԫ��
 p= (int**)malloc(n*sizeof(int*));//�ȷ���n��һάָ��
 if(NULL==p)
  exit(1);
 for (i = 0; i < n ; i++)
 {
  p[i] = (int*)malloc(n*sizeof(int));//Ϊn��һάָ�����n�����ʹ�С�Ŀռ�
  if (NULL==p[i])
   exit(1);
 }
 int flag=n;//ʣ�¾���Ľ�������ѭ��
 int row=0,cloumn=0;//���б�ǣ���ʼ����Ϊ0
 while(flag)
 {
  if (flag%2)//�������Ϊ������Ϊ���²����и�ֵ
  {
   for (i=0;i<flag;i++)
    p[row+flag-1][cloumn+flag-1-i]=flag*flag-i;
   for (j=1;j<flag;j++)
    p[row+flag-1-j][cloumn]=p[row+flag-1][cloumn]-j;
   cloumn++;//��ȥһ��һ�У�Ӱ���´�ѭ�����±꣬��1
  }
  else//Ϊż����Ϊ���ϲ����и�ֵ
  {
   for (i=0;i<flag;i++)
    p[row][cloumn+i]=flag*flag-i;
   for (j=1;j<flag;j++)
    p[row+j][cloumn+flag-1]=p[row][cloumn+flag-1]-j;
   row++;//��ȥһ��һ�У�Ӱ���´�ѭ�����±꣬��1
  }
  flag--;//ʣ�¾���Ľ���
 }
 printf("%d*%d�׾���Ϊ��\n",n,n);
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