# include<stdio.h>
# include<stdlib.h>
# include<string.h>
char *  myitoa(int data,char **ps)
{
	*ps = malloc(sizeof(char)*12);//2147483648  ten bit
	memset(*ps , 0, sizeof(char)*12);//将空间全部初始化为'\o'
	int i = 10;
	while(data)
	{
		*(*ps+i) = data%10 + 48;
		data /= 10;
		i--;
	}
	i++;
	return (*ps+i);
}
int main(void)
{
	int data = 1234;
	char *pa = NULL;

	char * ps = myitoa(data,&pa);
	printf("%s\n",ps);
	free(pa);

	return 0;
}
