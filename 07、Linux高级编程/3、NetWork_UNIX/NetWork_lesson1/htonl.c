# include<stdio.h>
# include<arpa/inet.h>
int main(void)
{
	unsigned long num1 = 0X12345678;
	unsigned char * p = (unsigned char *)&num1;
	printf("Little Endian:%x-%x-%x-%x\n",p[0],p[1],p[2],p[3]);
	
	unsigned long num2 = htonl(num1);
	p = (unsigned char *)&num2;
	printf("Big Endian:%x-%x-%x-%x\n",p[0],p[1],p[2],p[3]);

	return 0;
}
