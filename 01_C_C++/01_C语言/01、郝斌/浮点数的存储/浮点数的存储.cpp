#include<stdio.h>

int main(void)
{
	float i = 99.9;
	/*由于浮点数float和double类型都无法精确存储到计算机中,
	所以输出存储的浮点型数据的时候可能出错，本例便是。
	输入99.9，存储时不精确，所以输出时成了99.900002。
	*/
	printf("%f\n",i);

	return 0;
}