/*
 *Time:2017年7月19日18:40:36
 *Author:Kangruojin
 *Mail:mailbox_krj@163.com
 *Version:v1.2
*/
#include "sha1.h"

void ShaAlgorithm(const char * plaintextFileName)
{
	//test用
	unsigned char plaintext[64] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";//超过448bit
	//unsigned char plaintext[64] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	unsigned char ciphertext[20] = {0};//put last hash value
	
	ShaMess sha;
	ShaInit(&sha, strlen((const char *)plaintext));
	ShaPadding(&sha, plaintext, strlen((const char*)plaintext));
	
	ShaGetCiphertext(&sha, ciphertext);
}
void ShaGetCiphertext(ShaMess * sha, unsigned char * ciphertext)
{
	//小端转大端
	for(int i = 0; i < 5; i++){
		put_uint32(&(sha->buffer[i]), ciphertext , i*4);
	}
	for(int i = 0; i < 20; i++){
		printf("%02x",ciphertext[i]);
	}
	printf("\n");
}
void ShaInit(ShaMess * sha, uint32 file_length)
{
	sha->length[1] = 0;
	//length[0]要左移3位，所以高三位是1时要保存到，length[1]中低三位
	if(file_length & 0X80000000){
		sha->length[1] |= 0X04;//第三位
	}
	if(file_length & 0X40000000){
		sha->length[1] |= 0X02;//第二位
	}
	if(file_length & 0X20000000){	
		sha->length[1] |= 0X01;//第一位
	}
	sha->length[0] = file_length << 3;
    
	sha->buffer[0] = 0X67452301;//A
    sha->buffer[1] = 0XEFCDAB89;//B
    sha->buffer[2] = 0X98BADCFE;//C
    sha->buffer[3] = 0X10325476;//D
    sha->buffer[4] = 0XC3D2E1F0;//E
}
void ShaPadding(ShaMess * sha, unsigned char * plaintext, int len)
{
	printf("size = %d\n",len);
	if(len < 56){//index < 55
		printf("at padding if\n");
		plaintext[len] |= 0X80;//补1，0不需要补，每次读取文件时已经初始化为0
		
		//length信息进行大小端转换后放入plaintext的后64bit
		//即长度信息的高位放在数组低字节地址
		put_uint32(&(sha->length[0]), plaintext, 60);
		put_uint32(&(sha->length[1]), plaintext, 56);	
#if 1
		//补位后的信息打印
		for(int i = 0; i < 64; i++)	
			printf("%02x",plaintext[i]);
		printf("\n");
#endif
		ShaCalcHashValue(sha, plaintext);
	}
	else{
		printf("at padding else\n");
		//长度超过56Byte(56~64Byte)，则需要补位(64-len + 56)Ｂ,还有8Ｂ存放长度信息(总共128Ｂ)
		unsigned char * newPlaintext = (unsigned char *)malloc(128);
		memset(newPlaintext, 0, 128);
		memcpy(newPlaintext, plaintext, 64);
		
		newPlaintext[len] |= 0X80;
		put_uint32(&(sha->length[0]), newPlaintext, 124);
		put_uint32(&(sha->length[1]), newPlaintext, 120);
#if 1
		//补位后的信息打印
		for(int i = 0; i < 128; i++)	
			printf("%02x",newPlaintext[i]);
		printf("\n");
#endif

		ShaCalcHashValue(sha, newPlaintext);
		ShaCalcHashValue(sha, newPlaintext + 64);

		free(newPlaintext);
	}
}
void ShaCalcHashValue(ShaMess * sha, unsigned char * plaintext)
{
	uint32 w[80] = {0};
	ShaCalcW(w,plaintext);//生成W0~W79

	uint32 ki,tmp;
	//初始化循环输入ＡＢＣＤＥ	
	uint32 A = sha->buffer[0];
	uint32 B = sha->buffer[1];	
	uint32 C = sha->buffer[2];
	uint32 D = sha->buffer[3];
	uint32 E = sha->buffer[4];		

	for(int i = 0; i < 80; i++){
		tmp = E;
		//判断选择Ki
		if(i < 20)
			ki = 0X5A827999;
		else if(i<40)
			ki = 0X6ED9EBA1;
		else if(i<60)
			ki = 0x8F1BBCDC;
		else
			ki = 0xCA62C1D6;
		
		//判断选择对应的Hash Function
		if(i < 20)							
			tmp += ((B & C) | ((~B) & D));
		else if(i < 40 || i >= 60)	
			tmp += (B ^ C ^ D);
		else							
			tmp += ((B & C) | (C & D) | (D & B));
		
		tmp += LoopLeftMove(A, 5) + w[i] +ki;
		//更新本次循环输出，即下次循环输入
		E = D;
		D = C;
		C = LoopLeftMove(B,30);
		B = A;
		A = tmp;
	}
	//更新结果：最终将80次循环的结果+到原有结果的基础上
	sha->buffer[0] += A;
	sha->buffer[1] += B;
	sha->buffer[2] += C;
	sha->buffer[3] += D;
	sha->buffer[4] += E;
}

void ShaCalcW(uint32 * w, unsigned char * plaintext)
{
	/***************************************************************
	 *计算W0~W79：
	 *先将512bit的信息，分为32*16的16组即为W0~W15的16组
	 *其他的组由公式计算：
	 *Wt = {W(t-16) ^ W(t-14) ^ W(t-8) ^ W(t-3)}结果循环左移一位
	 ***************************************************************/
	
	for(int i = 0; i < 16; i++){
		get_uint32(&(w[i]), plaintext, i*4);//w[i]为大端
		//printf("w[%d]:%08lx\n",i,w[i]);
	}
	
	//计算W16~W79
	for(int i = 16; i < 80; i++){
		w[i] = LoopLeftMove((w[i-16] ^ w[i-14] ^ w[i-8] ^ w[i-3]),1);
		//printf("w[%d]:%08lx\n",i,w[i]);
	}
}
//4个8bit的信息转1个32bit的信息
void get_uint32(uint32 * n, void *b, int i){
    (*n) = (((uint32)((uint8 *)b)[(i)+3])) 		
   		| (((uint32)((uint8 *)b)[(i)+2]) << 8)  	
   		| (((uint32)((uint8 *)b)[(i)+1]) << 16) 	
   		| (((uint32)((uint8 *)b)[(i)+0]) << 24);
}

//1个32bit的信息，合并为4个8bit的信息
void put_uint32(uint32 * n, void *b, int i)
{
	((uint8 *)b)[(i)+3] = (uint8)(((*n)) & 0XFF);
    ((uint8 *)b)[(i)+2] = (uint8)(((*n) >> 8) & 0XFF);	
    ((uint8 *)b)[(i)+1] = (uint8)(((*n) >> 16) & 0XFF);	
    ((uint8 *)b)[(i)+0] = (uint8)(((*n) >> 24) & 0XFF);	
}
//循环左移n位
uint32 LoopLeftMove(uint32 x, int n)
{
	x = (x << n) | ((x & 0XFFFFFFFF) >> (32-n));
	return x;
}
