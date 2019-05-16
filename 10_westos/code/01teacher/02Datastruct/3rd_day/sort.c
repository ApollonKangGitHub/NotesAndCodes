#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct Node{
   void (*pa)(int * ,int);
   void	(*pb)(int *,int);
   void (*pc)(int *,int,int );
  void (*pd)(int *,int);
  void (*pe)(int *,int);
  void (*pf)(int *,int);
}laosiji;
laosiji lvdi;
void xier_sort(int a[],int n)  //希尔排序
{       int i,j;
        int t;
	int d=n/2;
  while(d>=0){    
   for(i=1;i<n;i++)
         {t=a[i];
           for(j=i-d;j>=0&&t<a[j];j-=d)
                a[j+d]=a[j];
                 a[j+d]=t;
        }
d--;
}
for(i=0;i<10;i++)
   printf("%5d",a[i]);
printf("\n");
}

void insert_sort(int a[],int n)  //插入排序
{	int i,j;
	int t;
	for(i=1;i<n;i++)
  	 {t=a[i];
 	   for(j=i-1;j>=0&&t<a[j];a[j+1]=a[j],j--);
		 a[j+1]=t;
	}
for(i=0;i<n;i++)
   printf("%5d",a[i]);
printf("\n");
}
void select_sort(int a[],int n)   //选择排序
{int i,j;
int t;
int k;
  for(i=0;i<n-1;i++)
   {k=i;
   for(j=i+1;j<n;j++)
     if(a[k]>a[j])
    k=j;
	if(k-i){
	t=a[i];
	a[i]=a[k];
	a[k]=t;
    }	

 }

for(i=0;i<10;i++)
  printf("%5d",a[i]);
	printf("\n");
}

int sort(int a[],int left,int right)  //快速排序
{  int x;
x=a[left];
  while(left<right){
   while(left<right&&a[right]>=x)   right--;
    a[left]=a[right];
   while(left<right&&a[left]<=x)  left++;
   a[right]=a[left];
	}
  a[left]=x;
return left;
}
void quick_sort(int a[],int left,int right)
{ 
  int mid=sort(a,left,right);
 if(left<right){
	quick_sort(a,left,mid-1);
       quick_sort(a,mid+1,right);
}
}
void maopao1_sort(int a[],int n) //冒泡排序
{int i,j;
int t;
for(i=0;i<n-1;i++)
  for(j=i+1;j<n;j++)
   {if(a[i]>a[j])
     {t=a[i];
	a[i]=a[j];
	a[j]=t;

	}

   }


}
void maopao2_sort(int a[],int n)  //冒泡排序
{int i,j;
int t,s;
for(i=0;i<n;i++)
 { t=0;
    for(j=n-1;j>i;j--)
  	{if(a[j-1]>a[j])
          {s=a[j-1];
 	  a[j-1]=a[j];
 	 a[j]=s;
          
	  }
	}
   if(t)  break;

}
}
laosiji lvdi={
  .pa=insert_sort,
  .pb=select_sort,
  .pc=quick_sort,
  .pd=xier_sort,
  .pe=maopao1_sort,
  .pf=maopao2_sort,
};

int main(void)
{
	int a[10]={2,1,4,7,4,8,3,6,4,7};
int i;
//lvdi.pa(a,10);
//lvdi.pb(a,10);
lvdi.pc(a,0,10);
//lvdi.pd(a,10);
//lvdi.pe(a,10);
//lvdi.pf(a,10);
for(i=0;i<10;i++)
   printf("%5d",a[i]);
  printf("\n");
return 0;
}





