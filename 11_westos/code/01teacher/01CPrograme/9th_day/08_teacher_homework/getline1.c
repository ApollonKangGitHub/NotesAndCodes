#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
long  pos=0;
ssize_t  getline1(char **s,size_t *,FILE *stream);
int main(int argc,char *argv[])
{
	FILE *fp=fopen(argv[1],"r");
	if(fp==NULL)
	{
		perror("fopen error\n");
		exit(EXIT_FAILURE);
	}
	char *s=NULL; //初始化避免出错 在这不初始化会出错
	ssize_t read = 0;
	size_t line=0;

//reading file every line
	while((read=getline1(&s,&line,fp)) != -1)
	{
		fputs(s,stdout);
		sleep (2);
		printf("\n");
	}
}
//----------------------------------------------------------------------
//getline implement
ssize_t  getline1(char **s,size_t *len,FILE *stream)
{
//---------------------------initialize variable----------------
	*len=10;
	*s=(char*)malloc((char)*len);
	int i = 0;
	pos=ftell(stream);   //position varaible of all function
	int ch=fgetc(stream);
//------------------------------------------------------------------
		//count  charater of  every line
	while( ch!= '\n' && ch != EOF  ) 
		{
			i++;
			ch = fgetc(stream);
		}
//------------------------------------------------------------------------
	if(ch != EOF)
	{
		//judge whether need to remalloc
		if( *len < i )
		{
			*s=(char*)realloc(*s,i);
			*len=i;
		}
		//file pointer point current position
		
		fseek(stream,pos,SEEK_SET);

#if 1 		
		ch = fgetc(stream);
		for(i=0;i< *len  && ch != '\n' ;i++)
		{
			(*s)[i] = ch;
			ch=fgetc(stream);
		}
#endif	
		(*s)[i] = '\0';
	 	 return *len;
	}
	else
	{
		return EOF;
	}
}
