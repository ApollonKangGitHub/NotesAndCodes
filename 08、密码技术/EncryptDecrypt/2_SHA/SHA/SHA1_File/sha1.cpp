#include "sha1.h"

void ShaAlgorithm(const char * plaintextFileName)
{
	FILE * fp = fopen(plaintextFileName,"r");
    assert(NULL != fp);

	unsigned char plaintext[64] = {0};//512bit,put message that read from plaintext file
	unsigned char ciphertext[20] = {0};//put last hash value
	int len = 0;//message block length

	ShaMess sha;
	fseek(fp, 0, SEEK_END);
	ShaInit(&sha, (uint32)ftell(fp));
	fseek(fp, 0, SEEK_SET);


	while(!feof(fp)){
		int len = fread(plaintext, sizeof(plaintext), 1, fp);
		//如果某次读取后到文件末尾，则进行补位，在补位函数中加密后，退出循环
		if(len == 0){//到文件末尾和出错均返回0
			if(feof(fp)){
				ShaPadding(&sha, plaintext, strlen((const char*)plaintext));
				break;
			}
			else{
				printf("read error!\n");
				return;
			}
		}
		else{
		//某次读取后，没有到文件末尾(读取达到sizeof(plaintext)字节)则直接加密
			ShaCalcHashValue(&sha, plaintext);	
		}
		memset(plaintext, 0, sizeof(plaintext));//clean last message
	}

	fclose(fp);	
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
void ShaInit(ShaMess * sha, uint32 len)
{
	sha->length[1] = 0;
	sha->length[0] = len << 3;
	sha->length[1] = len >> 29;
	
	sha->buffer[0] = 0X67452301;//A
    sha->buffer[1] = 0XEFCDAB89;//B
    sha->buffer[2] = 0X98BADCFE;//C
    sha->buffer[3] = 0X10325476;//D
    sha->buffer[4] = 0XC3D2E1F0;//E
}
void ShaPadding(ShaMess * sha, unsigned char * plaintext, int len)
{
	if(len < 56){//index < 55
		plaintext[len] |= 0X80;//补1，0不需要补，每次读取文件时已经初始化为0
		
		//length信息进行大小端转换后放入plaintext的后64bit
		//即长度信息的高位放在数组低字节地址
		put_uint32(&(sha->length[0]), plaintext, 60);
		put_uint32(&(sha->length[1]), plaintext, 56);	
		ShaCalcHashValue(sha, plaintext);
	}
	else{
		//长度超过56Byte即448bit，则需要补位(64-len + 56)Ｂ,还有8Ｂ存放长度信息(总共128Ｂ)
		unsigned char * newPlaintext = (unsigned char *)malloc(128);
		memset(newPlaintext, 0, 128);
		memcpy(newPlaintext, plaintext, 64);
		
		plaintext[len] |= 0X80;
		put_uint32(&(sha->length[0]), newPlaintext, 124);
		put_uint32(&(sha->length[1]), newPlaintext, 120);

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
			ki = KEY1;
		else if(i<40)
			ki = KEY2;
		else if(i<60)
			ki = KEY3;
		else
			ki = KEY4;
		
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
//小端转大端：4个8bit的小端信息转1个32bit的大端信息
void get_uint32(uint32 * n, void *b, int i){
    (*n) = (((uint32)((uint8 *)b)[(i)+3])) 		
   		| (((uint32)((uint8 *)b)[(i)+2]) << 8)  	
   		| (((uint32)((uint8 *)b)[(i)+1]) << 16) 	
   		| (((uint32)((uint8 *)b)[(i)+0]) << 24);
}

//小端转大端：1个32bit的小端信息，合并为4个8bit的大端信息
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
