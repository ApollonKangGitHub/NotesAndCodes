# include<stdio.h>
# include<string.h>
# include<stdlib.h>

void sort(char ** pps,int len)
{
	int i,j;
	char * tmp = NULL;
	for(i=0;i<len;++i)
	{
		for(j=0;j<len-i-1;++j)
		{
			if( strcmp(*(pps+j),*(pps+j+1)) == 1 )
			{
			//	*(pps+j)=*(pps+j)^*(pps+j+1);
			//	*(pps+j+1)=*(pps+j)^*(pps+j+1);
			//	*(pps+j)=*(pps+j)^*(pps+j+1);
				tmp = *(pps+j);
				*(pps+j) = *(pps+j+1);
				*(pps+j+1) = tmp;			
			}
		}
	}
}
int main(void)
{
	int i;
	char * ps[4]={"hello ","there ","is ","xian "};
	char ** pps = ps;
	printf("%s%s%s%s\n",ps[0],ps[1],ps[2],ps[3]);
	
/*	printf("%s\n",*pps);//get &"hello"
	printf("%c\n",**pps);//get "hello"
	for(i=0;i<22;++i)
	{	
		printf("%c",*(*pps+i));
	}
	printf("\n");
	for(i=0;i<22;++i)
	{
		printf("%c",**pps);
		++(*pps);
	}
	printf("\n");
*/	sort(ps,4);
	printf("%s%s%s%s\n",ps[0],ps[1],ps[2],ps[3]);

	return 0;
}
