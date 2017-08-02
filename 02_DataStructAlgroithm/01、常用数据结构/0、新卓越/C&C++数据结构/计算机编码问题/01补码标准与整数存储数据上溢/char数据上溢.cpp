# include <stdio.h>
# define TEMP 20

int main (void)
{

	int distance = 1;

	/*char 的上溢由distance和ch初始值两个因素决定，因distance不同上溢数据不同*/
	while(distance < TEMP)
	{
		char ch = 'a';
		while(ch > 0)   ch += distance;
		printf("ch = %d\t",ch);
		printf("ch = %#X\n",ch);

		distance ++;
	}

	return 0;
}
