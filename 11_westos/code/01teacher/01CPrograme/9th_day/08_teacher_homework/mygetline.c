#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define max 100
int mygetline( char**lineptr,int * n,FILE * fp)
{ 
    char  i,j;
      int cnt=0;
	int line_number=-1;   //增加行号
	if(*lineptr==NULL)
	{*n=max;
	*lineptr=malloc(*n);
	}
    while((i=fgetc(fp))-EOF)
	{if(i=='\n')
		{line_number++;
		//printf("\n");
		break;
		}
         cnt++;
	*(*lineptr+cnt-1)=i;
	*(*lineptr+cnt)='\0';
       if(*n<=cnt)
	{
	*lineptr=realloc(*lineptr,cnt*3);
	}
        *n=cnt;
	}
	return line_number;     


}
int main(int argc,char * argv[])
{FILE * fp=fopen("a.txt","r");
  if(fp==NULL)	{
	perror("fopen err");
	exit(EXIT_FAILURE);
	}
  int len;
  char * line=NULL;
  int size=0;
 while((size=mygetline(&line,&len,fp))!=EOF)
	{
printf("%s",line);
        //printf("%d\n",size);
	//printf("%d\n",len);
	strcpy(line," ");   //清除缓存区  解决程序遇到第一行空格就退出，无法读取剩余的行
printf("\n");

	}
    if(line)
     free(line);
     fclose(fp);

return 0;
}


