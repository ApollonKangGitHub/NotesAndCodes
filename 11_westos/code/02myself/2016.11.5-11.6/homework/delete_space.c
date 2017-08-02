# include<stdio.h>
# include<string.h>
# include<stdlib.h>

char * delete_space(char * arr)
{
	char *ret = malloc(sizeof(arr));
	int i=0;
	for(i, arr; *arr != '\0'; arr++, i++)
	{
			if(*arr == ' '){
				while(*arr++ == ' ');
					ret[i] = ' ';
				arr--;
			}
			else
				ret[i] = *arr;
	}
	return ret;

}
int main(void)
{
	char * arr = "Hello      everyone\nGood           moring!!";

	printf("%s\n",arr);
	arr = delete_space(arr);
	printf("%s\n",arr);
	return 0;
}

