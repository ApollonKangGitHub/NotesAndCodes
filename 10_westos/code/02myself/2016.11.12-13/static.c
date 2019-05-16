# include<stdio.h>
static int j;
int fun1(void)
{
	static int i = 0;
	i++;
}

void fun2(void)
{
	j = 0;
	j++;
}

int main(void)
{
	int k = 0;
	int i = 0;
	for(k;k<10;k++){
		i = fun1();
		fun2();
	}
	printf("i = %d\n j = %d",i,j);
	return 0;
}
