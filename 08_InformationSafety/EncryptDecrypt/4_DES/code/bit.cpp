#include "bit.h"
//获取指定地址指定位信息（0/1）
int get_bit(unsigned char * input, int pos)
{
	//单字节最高位为第0位
	unsigned char mask, i, bit;
	for(bit = pos % 8, mask = 0X80, i = 0; i < bit; i++){
		mask >>= 1;
	}
	return ( ( (mask & input[pos/8]) == mask ) ? 1 : 0 );
}
//设置指定地址指定位信息（value = 0/1）
void set_bit(unsigned char * input, int pos, int value)
{
	unsigned char mask, i, bit;
	for(bit = pos % 8, mask = 0X80, i = 0; i < bit; i++){
		mask >>= 1;
	}
	(value) ? (input[pos/8] |= mask) : (input[pos/8] &= (~mask));
}
//异或操作,output存储异或后的结果，size为需要异或的位数
void xor_bit(unsigned char * input1, unsigned char * input2, unsigned char * output, int size)
{
	int i;
	for(i = 0; i < size; i++){
		if(get_bit(input1, i) == get_bit(input2, i)){
			set_bit(output, i, 0);//相同为0
		}
		else{	
			set_bit(output, i, 1);//不同为1
		}
	}
}
//循环左移，size为总循环的长度，num为循环左移的位数
void rol_bit(unsigned char * input, int size, int num)
{
	//注意：低字节为左，高字节为右（与字符存储方式对应）
	//如果低字节为右，高字节为做，写法相似
	int left_bit = 0, loop_bit = 0, i = 0, j = 0;

	if(size > 0){
		for(i = 0; i < num; i++){//循环左移一位，共num次
			for(j = 0; j <= (size-1)/8; j++){//多字节操作
				left_bit = get_bit(&input[j], 0);//获取最高位
				if(j == 0){
					//如果是低字节，则其第一位，是左边溢出的，需要保存并在最终放到高字节右边最后一位
					loop_bit = left_bit;
				}
				else{
					//不是则直接将本字节第一位，设置到上一字节（低字节也是左边的字节）最后一位
					set_bit(&input[j-1], 7, left_bit);
				}
				input[j] <<= 1;
			}
			//把左边移出的一位，移入最右边一位（即循环左移）
			set_bit(input, size-1, loop_bit);
		}
	}
}
