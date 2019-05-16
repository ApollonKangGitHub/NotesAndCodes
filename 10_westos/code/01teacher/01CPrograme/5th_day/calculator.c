#include <stdio.h>
#include <math.h>
#include<stdlib.h>
 /*
 * 简易的一个计算器， 实现 10 转 2 
 * 16 转 10、 8 转 0、 逻辑左移任意位
 *
 * */

void pri_16b(unsigned char *arr)
{
	int i = 0;
	for(i=15; i>=0; i--){
		printf("%d", arr[i]);
		if(i % 4 == 0)
			printf(" ");

	}
	printf("\n");
} 
void pri_8b(unsigned char *arr)
{
	int i = 0;
	for(i=7; i>=0; i--){
		printf("%d", arr[i]);
		if(i % 4 == 0)
			printf(" ");
	}
	printf("\n");
} 
void pri_32b(unsigned char *arr)
{
	int i = 0;
	for(i=31; i>=0; i--){
		printf("%u", arr[i]);
		if(i % 4 == 0)
			printf(" ");

	}
	printf("\n");
} 
// 十进制转二进制
int ten_to_bin(unsigned int a, unsigned char *arr)
{
	int i = 0;
	while(a){
		arr[i] = a % 2;
		a = a / 2;
		i++;
	}
	return i; //返回转换后二进制有多少位
}
// 十六进制转十进制
double hex_to_ten(unsigned int hex)
{
	int i = 0;
	unsigned char buf[16] = {0};
	double data = 0;

	while(hex){
		buf[i] = hex % 16;		
		hex = hex / 16;
		data += buf[i] * pow(16, i);	
		i++;
	}
	return data;
}
// 八进制转十进制
double octal_to_ten(unsigned int octal)
{
	unsigned char o_arr[16] = {0};
	int i = 0;
	double ret = 0;

	while(octal){
		o_arr[i] = octal % 10;	
		ret += o_arr[i] * pow(8, i);
		octal = octal / 10;
		i++;
	}
	return ret;
}
int left_shifter(unsigned int data,unsigned char* arr, int num)
{
	int i, j, tmp;
	for(j=0; j<num; j++){
		tmp = arr[31];
		for(i=30; i>=0; i--)
			arr[i+1] = arr[i];
		arr[i+1] = tmp;
	}

#if 0
	unsigned int tmp = 0;
	tmp = data & 0xe0000000;		
	data = data << num;
	tmp = tmp >> 29;
	data = data | tmp;
	return data;
#endif
}
int main()
{
	unsigned int data = 302288;
	unsigned char arr[32] = {0};

	ten_to_bin(data, arr);
	pri_32b(arr);
	unsigned int ret = left_shifter(data, arr, 17);	
	pri_32b(arr);

#if 0
	unsigned int hex = 0x8fffffff;
	double ret = hex_to_ten(hex);
	unsigned int ten = (unsigned int)ret;
	printf("ten: %u\n", ten);
	unsigned int octal = 644;
	unsigned int ret = (unsigned int)octal_to_ten(octal);
	printf("ret: %d\n", ret);

	unsigned char arr[32] = {0};
	ten_to_bin(ten, arr);
	pri_32b(arr);
	left_shifter(ten, arr, 17);	
	pri_32b(arr);


	unsigned int octal = 644;
	unsigned int ret = (unsigned int)octal_to_ten(octal);
	printf("ret: %d\n", ret);


	int i = ten_to_bin(data, arr);
	// 根据 i 的值打印二进制数
	if(i < 8){
		printf("in if : %d\n", i);
		pri_8b(arr);
	} else if(i > 8 && i < 16){
		printf("in else if i: %d\n", i);
		pri_16b(arr);
		
	} else {
		printf("in else : %d\n", i);
		pri_32b(arr);
	}
#endif	
	
	return 0;
}




