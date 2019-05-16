# include<stdio.h>
# include<string.h>

# define LEN 20

int add(char * a, char * b)
{
	while(1){
		if(*a > '9' || *a < '0' || *a == '\0')
			break;
		a++;
	}	
	while(1){
		if(*b > '9' || *b < '0' || *b == '\0')
			break;
		b++;
	}
	if(*a != '\0' || *b != '\0')
		return -1;
	else
		return (atoi(a) + atoi(b));
}

int main(void)
{
	char a[LEN],b[LEN];
	//memset(a,0,LEN);
	//memset(a,0,LEN);
	scanf("%s",a);
	scanf("%s",b);

	int sum = add(a,b);
	
	if(sum == -1)
		printf("参数类型错误！\n");
	else
		printf("sum = %d\n",sum);
	return 0;
}
