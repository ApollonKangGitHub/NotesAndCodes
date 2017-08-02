# include<stdio.h>

int add(int x,int y)
{
	printf("address_x = %p\naddress_y = %p\n",&x,&y);
	return (x+y);
}
int main(void)
{
	int sum = add(3,5);
	printf("sum = %d\n",sum);
}