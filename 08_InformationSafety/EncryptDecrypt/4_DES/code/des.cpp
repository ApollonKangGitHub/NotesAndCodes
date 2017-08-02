/*
 *Time:2017年7月25日21:31:51
 *Author:Kangruojin
 *Mail:mailbox_krj@163.com
 *Version:V1.1
*/
#include "des.h"
#include "bit.h"
//key.txt需要安全保管，不能让其他人知道
//秘文组出初始置换
static const int DesInitial[64] = {
   58, 50, 42, 34, 26, 18, 10,  2, 60, 52, 44, 36, 28, 20, 12,  4,
   62, 54, 46, 38, 30, 22, 14,  6, 64, 56, 48, 40, 32, 24, 16,  8,
   57, 49, 41, 33, 25, 17,  9,  1, 59, 51, 43, 35, 27, 19, 11,  3,
   61, 53, 45, 37, 29, 21, 13,  5, 63, 55, 47, 39, 31, 23, 15,  7
};
//密钥置换
static const int DesTransform[56] = {
   57, 49, 41, 33, 25, 17,  9,  1, 58, 50, 42, 34, 26, 18,
   10,  2, 59, 51, 43, 35, 27, 19, 11,  3, 60, 52, 44, 36,
   63, 55, 47, 39, 31, 23, 15,  7, 62, 54, 46, 38, 30, 22,
   14,  6, 61, 53, 45, 37, 29, 21, 13,  5, 28, 20, 12,  4
};
//子密钥移位
static const int DesSubkey[16] = {
   1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1
};
//压缩置换（56bit->48bit）
static const int DesPermuted[48] = {
   14, 17, 11, 24,  1,  5,  3, 28, 15,  6, 21, 10,
   23, 19, 12,  4, 26,  8, 16,  7, 27, 20, 13,  2,
   41, 52, 31, 37, 47, 55, 30, 40, 51, 45, 33, 48,
   44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32
};
//明文右半部分扩展置换
static const int DesExpansion[48] = {
   32,  1,  2,  3,  4,  5,  4,  5,  6,  7,  8,  9,
    8,  9, 10, 11, 12, 13, 12, 13, 14, 15, 16, 17,
   16, 17, 18, 19, 20, 21, 20, 21, 22, 23, 24, 25,
   24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32,  1
};
//8个S盒
static const int DesSbox[8][4][16] = {
	{
		{14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7},
		{ 0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8},
		{ 4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0},
		{15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13},
	},
	
	{
		{15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10},
		{ 3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5},
		{ 0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15},
		{13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9},
	},
		
	{
		{10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8},
		{13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1},
		{13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7},
		{ 1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12},
	},
		
	{
		{ 7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15},
		{13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9},
		{10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4},
		{ 3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14},
	},
			
	{
		{ 2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9},
		{14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6},
		{ 4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14},
		{11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3},
	},
			
	{
		{12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11},
		{10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8},
		{ 9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6},
		{ 4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13},
	},
				
	{
		{ 4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1},
		{13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6},
		{ 1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2},
		{ 6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12},
	},

	{
		{13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7},
		{ 1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2},
		{ 7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8},
		{ 2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11},
	},
};
//P盒置换
static const int DesPbox[32] = {
   16,  7, 20, 21, 29, 12, 28, 17,  1, 15, 23, 26,  5, 18, 31, 10,
    2,  8, 24, 14, 32, 27,  3,  9, 19, 13, 30,  6, 22, 11,  4, 25
};
//末置换
static const int DesFinal[64] = {
   40,  8, 48, 16, 56, 24, 64, 32, 39,  7, 47, 15, 55, 23, 63, 31,
   38,  6, 46, 14, 54, 22, 62, 30, 37,  5, 45, 13, 53, 21, 61, 29,
   36,  4, 44, 12, 52, 20, 60, 28, 35,  3, 43, 11, 51, 19, 59, 27,
   34,  2, 42, 10, 50, 18, 58, 26, 33,  1, 41,  9, 49, 17, 57, 25
};


void des(OperType type, char * infile, char * outfile, char * keyfile)
{
	unsigned char key[8] = {0};//随机产生的密钥64bit
	unsigned char data[8] = {0};//进行加密/解密的分组64bit
	unsigned char iv[8] = {0};//CBC模式的初始化向量(initialization vector)64bit
	unsigned char temp[8] = {0};
	
	get_KeyAndVector(key, iv, type, keyfile);//获取密钥和初始向量
	
	FILE * fpin = fopen(infile, "r");		assert(fpin != NULL);
	FILE * fpout = fopen(outfile, "w");		assert(fpout != NULL);

	int len = 0;
	while(!feof(fpin)){
		if((len = fread(data, 1, 8, fpin)) == 0){//没有读到内容则结束
			if(!feof(fpin))
				printf("文件读写出错!\n");
			break;
		}
		else{
			if(type == ENCRYPT){
				//先异或，再加密，加密完成后更新向量为加密后的秘文
				xor_bit(iv, data, data, 64);
				des_AlgorithmDeal(data, key, type);
				memcpy(iv, data, 8);
			}
			else{
				memcpy(temp , data, 8);//因为data会改变，data改变后需要用其改变前的值，因此要保存
				//先解密，再异或，异或完成后更新向量为上一组秘文
				des_AlgorithmDeal(data, key, type);
				xor_bit(iv, data, data, 64);
				memcpy(iv, temp, 8);//秘文组复制非iv
			}
			fwrite(data, 1, 8, fpout);
		}
		memset(data, 0, 8);
	}
	fclose(fpin);
	fclose(fpout);
}
void get_KeyAndVector(unsigned char * key, unsigned char * iv, OperType type, char * keyfile)
{
	if(type == ENCRYPT){//生成密钥和初始化向量并保存
		FILE * fpkey = fopen(keyfile, "w");
		assert(fpkey != NULL);
		srand(time(NULL));
		for(int i = 0; i<8; i++){
			key[i] = rand()%256;//密钥生成
			iv[i] = rand()%256;//出始向量生成
		}
		fprintf(fpkey,"%08lx%08lx",((unsigned long *)key)[0],((unsigned long *)key)[1]);
		fprintf(fpkey,"%08lx%08lx",((unsigned long *)iv)[0],((unsigned long *)iv)[1]);
		fclose(fpkey);
	}
	else{//读取密钥和初始化向量	
		FILE * fpkey = fopen(keyfile, "r");
		assert(fpkey != NULL);
		//注意：fscanf()第三个及以后的参数是地址，不是值
		fscanf(fpkey, "%08lx%08lx", (unsigned long *)key, ((unsigned long *)key) + 1);
		fscanf(fpkey, "%08lx%08lx", (unsigned long *)iv, ((unsigned long *)iv) + 1);
		fclose(fpkey);
	}
}
static void permute(unsigned char * source, const int * index, int len)
{
	unsigned char temp[8] = {0};
	for(int i = 0; i < len; i++){
		set_bit(temp, i, get_bit(source, index[i]-1));//表中是从1开始，数组下表要减去1
	}
	memcpy(source, temp, len/8);
}
//算法处理函数
static void des_AlgorithmDeal(unsigned char data[], unsigned char key[], OperType type)
{
	int i, j, k, p, row, col;
	unsigned char temp[8], lkey[4], rkey[4], ldata[6], rdata[6], exp_data[6], xor_data[6], value;
	unsigned char subKey[16][7] = {0};

	if(key != NULL){//子密钥生成	
		memcpy(temp, key, 8);//temp暂存key
		//密钥置换：64bit->56bit
		permute(temp, DesTransform, 56);
		//密钥分为左右两部分各自28bit
		memset(lkey, 0, 4);
		memset(rkey, 0, 4);
		for(i = 0; i < 28; i++){
			set_bit(lkey, i, get_bit(temp, i));//temp的前28给left
			set_bit(rkey, i, get_bit(temp, i+28));//temp的后28给right
		}

		//进行16次循环，分别求出16个子密钥
		for(i = 0; i < 16; i++){
			rol_bit(lkey, 28, DesSubkey[i]);//左边28位循环左移
			rol_bit(rkey, 28, DesSubkey[i]);//右边28位循环左移
			for(j = 0; j < 28; j++){//和并为56bit是子密钥
				set_bit(subKey[i], j, get_bit(lkey, j));	
				set_bit(subKey[i], j+28, get_bit(rkey, j));	
			}
			//子密钥压缩置换成48位子密钥
			permute(subKey[i], DesPermuted, 48);
		}
	}
	//明文初始置换
	memcpy(temp, data, 8);
	permute(temp, DesInitial, 64);

	//明文分组分成左右两部分各自32bit
	memcpy(ldata, &temp[0], 4);
	memcpy(rdata, &temp[4], 4);
	for(i = 0; i<16; i++){
		//32bit经过扩展后为48bit
		memcpy(exp_data, rdata, 4);
		permute(exp_data, DesExpansion, 48);
		//压缩后的子密钥和扩展后的明文有半部分进行异或操作,结果放入xor_data[]中
		if(type == ENCRYPT){
			xor_bit(subKey[i], exp_data, exp_data, 48);//加密:K0~K15
		}
		else{	
			xor_bit(subKey[15-i], exp_data, exp_data, 48);//解密:K15~K0
		}
		//S盒代替压缩：(6*8)48bit->(4*8)32bit
		for(j = 0, p = 0; j < 8; j++){//p从0~32
			//根据6bit信息获取行和列
			row = (get_bit(exp_data, j*6+0) * 2) + (get_bit(exp_data, j*6+5) * 1); //b1b6
			col = (get_bit(exp_data, j*6+1) * 8) + (get_bit(exp_data, j*6+2) * 4) +
				  (get_bit(exp_data, j*6+3)) * 2 + (get_bit(exp_data, j*6+4) * 1); //b2b3b4b5
			//根据行和列获取Ｓ盒中对应值，计算4bit信息
			value = (unsigned char)DesSbox[j][row][col];
			//value为0~15，从左到右取第4、5、6、7位（低四位）即可，即4bit
			for(k = 4; k < 8; k++){
				set_bit(exp_data, p, get_bit(&value, k));
				p++;
			}
		}
		//做Ｐ盒置换
		permute(exp_data, DesPbox, 32);
		//置换结果与最初左半部分异或得到右半部分
		xor_bit(exp_data, ldata, exp_data, 32);
		//右半部分32bit作为左半部分
		memcpy(ldata, rdata, 4);
		memcpy(rdata, exp_data, 4);
	}
	//最后一轮操作不需要左右调换，则复制回去时再将已经调换的调换一次，即没有调换
	memcpy(data, rdata, 4);
	memcpy(data + 4, ldata, 4);
	//末置换
	permute(data, DesFinal, 64);
}
