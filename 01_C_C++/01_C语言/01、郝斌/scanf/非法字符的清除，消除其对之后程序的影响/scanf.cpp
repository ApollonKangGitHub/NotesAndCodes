# include <stdio.h>

int main (void)
{	
	char ch;
	printf("请输入i：");
	int i;
	scanf("%d",&i);
	printf("i = %d\n",i);

	while ((ch=getchar()) !='\n')
		continue;
	printf("请输入j：");
	int j;
	scanf("%d",&j);
	printf("j = %d\n",j);

/*	while ((ch=getchar()) !='\n')
		continue;
*/
	printf("请输入k：");
	int k;
	scanf("%d",&k);
	printf("k = %d\n",k);

	return 0;
}
/*
while ((ch=getchar()) !='\n')
		continue;
		该段程序所起作用为：当输入字符与控制符格式不一致时，
		会自动将非法数据（与输入控制符格式不同的数据，即非输入控制符）清除，
		解除对后面程序的影响。
*/