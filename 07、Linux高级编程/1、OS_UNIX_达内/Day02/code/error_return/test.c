# include"error_return.h"
int main(void)
{
/*a*/
	print_string("hello everyone!");
/*b*/
	char * str1 = test_string("hello everyone!");
	printf("hello everyone:%s\n",str1);
	char * str2 = test_string("error");
	printf("error:%s\n",str2);
/*c*/
	int num = rand_test();
	if(num == -1)
		printf("生成的数字为5，错误不可用！\n");
	else
		printf("生成的数字为：%d\n",num);
	
/*d*/
	int max_num = 0;
	num = max_int(-1,-3,&max_num);
	if(num == -1)
		printf("错误两个值一样大！\n");
	else
		printf("大值为：%d\n",max_num);

	return 0;
}
