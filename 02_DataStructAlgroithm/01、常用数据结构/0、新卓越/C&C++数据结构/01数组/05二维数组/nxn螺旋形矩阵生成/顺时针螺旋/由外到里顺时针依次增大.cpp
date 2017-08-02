#include<stdio.h>  
#include<malloc.h> 
int printfnum(int n)
{
    int **p=NULL;
    int i,j,k=1,line,row,sum=0;
    if((p=(int**)malloc(sizeof(int**)*n))==NULL)  
    {    
        printf("不能分配内存!!!\n");    
        return 1;    
    }    
    for(i=0;i<n;i++)    
    {    
        if((p[i]=(int*)malloc(sizeof(int*)*n))==NULL)    
        {    
            printf("不能分配内存!!!\n");    
            return 1;    
        }    
    }     
    for(i=0,j=0;k<=n*n;i++,j++)  
    {  
            for(row=j;row<n-j;row++)  
            {  
                p[i][row]=k++;  
            }  
            for(line=i+1;line<n-i;line++)  
            {  
                p[line][n-j-1]=k++;  
            }  
            for(row=n-j-2;row>=j;row--)  
            {  
                p[n-i-1][row]=k++;  
            }  
            for(line=n-i-2;line>i;line--)  
            {  
                p[line][j]=k++;  
            }  
    }  
    for(i=0;i<n;i++)    
    {    
        for(j=0;j<n;j++)    
        {    
            printf("%-6d",p[i][j]); 
            if(i==j)
                sum+=p[i][j];
        }    
        printf("\n\n");    
    } 
    printf("%d\n",sum);
    for(i=0;i<n;i++)   
    {    
        free(p[i]);    
        p[i]=NULL;    
    }    
    free(p);
    p=NULL;    
    return 0; 
}
int main()  
{  
    int line,n,i;
    printf("请输入数据行数:");
    scanf("%d",&line);
    printf("请输入数据:");
    for(i=0;i<line;i++)
    {
        scanf("%d",&n);
        printfnum(n);
    }
    return 0;
        
}

