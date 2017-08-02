# include <stdio.h>
int main (void)
{
	int a[5]={1,2,3,4,5};
	int i;

	for(i=0;i<=4;i++)
	{
		printf("%#x  ",(a+i));//a+i 表示a加上i乘以（a所指向的变量所占的字节数），故a+i（如：a+2）表示的就是第i+1（如：2+1=3）个元素的首地址
		printf("%#x  ",(i+a));

		printf("%p  ",a+i);//%#x表示以0x形式十六进制输出，%p(三十二位十六进制)表示输出（a+1）的地址（地址就是十六进制形式）
		printf("%p  ",&a[i]);
		printf("%p  ",*(a+i));

		printf("%d  ",*(a+i));
		printf("%d  ",*(i+a));
		printf("%d",a[i]);

		printf("\n");
	}
	printf("\n");

	return 0;
}