# include <stdio.h>
int main (void)
{
	int i = 0;
	while(i<3)
	{
		switch(i++)//注意此处i先使用再自加。换成++i输出结果会发生变化。
		{
		case 0: 
			printf("fat  ");
			//break;
		case 1: 
			printf("hat  ");
			//break;
		case 2: 
			printf("cat  ");
			//break;
		default : 
			printf("Oh no!");
			break;
		}
		//没有break，所以case i以后的语句都会执行。
		putchar('\n');
	}
	return 0;
}