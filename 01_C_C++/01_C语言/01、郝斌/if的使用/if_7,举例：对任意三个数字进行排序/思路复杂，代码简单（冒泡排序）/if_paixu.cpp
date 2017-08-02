# include <stdio.h>

int main (void)

{
	int a, b, c, t;

	printf("please input three numbers (a,b,c):");
	scanf("%d,%d,%d",&a, &b, &c);

	if (a < b)
	{
		t = a;
		a = b;
		b = t;
	}   
	//如果小于就互换，如果不小于就无须改变

	if (a < c)
	{
		t = a;
		a = c;
		c = t;
	}

	if (b < c)               //如果a<c,那么此时的c就已经是输入数据时的a了
	{
		t = b;
		b = c;
		c = t;
	}

	printf("%d,%d,%d\n",a, b, c);


	return 0;
}