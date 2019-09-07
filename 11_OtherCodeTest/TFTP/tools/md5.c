/*
 * Mail:mailbox_krj@163.com
 * Author:Kangruojin
 * Time:2017年7月21日13:00:36
 * Version:V1.1
 */
#include <md5.h>
#include <tftpPublic.h>
#include <tftpType.h>

UINT8 gMd5Result[33] = {0};

EXTERN VOID md5_algroithm(CHAR CONST * file, UINT8 * result)
{
	/* 用来接收文件中读取的一个512bit的分组 */
	UINT8 plaintext[64] = {0}; 

	FILE * fp = fopen(file, "r");/* 打开文件 */
	assert(fp != NULL);
	
	/* 定义结构体变量，结构体保存散列值和文件长度 */
	MD5STR md5;
	fseek(fp, 0, SEEK_END);
	size_t len = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	
	/* 获取文件长度，初始化结构体 */
	md5_init(&md5, len);
	
	/* 每次读取一个分组，没到文件末尾则继续读取 */
	while(!feof(fp)){
		len = fread(plaintext, 64, 1, fp);
		/* 未到文件末尾 */
		if(!feof(fp)){
			/* 文件还未读取完毕，则直接处理，不需要补位 */
			md5_calcHashValue(&md5, plaintext);
		}
		else{
			/* 文件读取完毕则需要补位处理,因为到文件尾时，返回的是0，而不是读取到的字节个数 */
			len = strlen((const char *)plaintext);
			/* 补位函数中直接调用处理函数，则返回值跳出循环 */
			md5_padding(&md5, plaintext, len);
			break;
		}
		/* 每次分组处理完毕，缓冲区清零 */
		memset(plaintext, 0, 64);
	}
	/* 输出散列值 */
	md5_showHashValue(&md5, result);
	fclose(fp);
}

LOCAL VOID md5_showHashValue(MD5STR * md5, UINT8 * result)
{
	UINT8 index = 0;
	UINT8 len = 0;
	memset(result, 0, sizeof(result));
	for(index = 0; index < 4; index++){
		/* 从低地址到高地址依次输出 */
		len += tftp_sprint(result + len, "%0x", ((UINT8 *)(md5->state))[index * 4 + 0]);
		len += tftp_sprint(result + len, "%0x", ((UINT8 *)(md5->state))[index * 4 + 1]);
		len += tftp_sprint(result + len, "%0x", ((UINT8 *)(md5->state))[index * 4 + 2]);
		len += tftp_sprint(result + len, "%0x", ((UINT8 *)(md5->state))[index * 4 + 3]);
	}
}

LOCAL VOID md5_init(MD5STR * md5, UINT32 len)
{
	md5->length[1] = 0;
	/* 字节数乘以8为bit数 */
	md5->length[0] = len << 3;
	md5->length[1] = len >> 29;
	/* 散列值初始化，注意值的存放方式 */
	md5->state[0] = 0X67452301;
	md5->state[1] = 0XEFCDAB89;
	md5->state[2] = 0X98BADCFE;
	md5->state[3] = 0X10325476;
}
LOCAL VOID md5_padding(MD5STR * md5, UINT8 * data, UINT32 len)
{
	/* 信息长度小于56则不用增加新分组 */
	if(len < 56){
		/* 补1 */
		data[len] |= 0X80;
		for(int i = 0; i < 8; i++){
			/* 填充长度信息，数据高位放在高地址（小端） */
			data[i + 56] = ((UINT8 *)(md5->length))[i];
		}
		/* 填充完毕后计算散列值 */
		md5_calcHashValue(md5, data);
	}
	/* 大于等于56需要增加新分组 */
	else{
		UINT8 * newData = (UINT8 *)malloc(128);
		if(newData == NULL){
			perror("malloc at padding\n");
			exit(EXIT_FAILURE);
		}
		memset(newData, 0, 128);
		memcpy(newData, data, len);

		newData[len] |= 0X80;
		for(int i = 0; i < 8; i++){
			newData[i + 120] = ((UINT8 *)(md5->length))[i];
		}
		/* 包含数据信息的分组 */
		md5_calcHashValue(md5, newData);		
		/* 包含长度信息的新增加的分组 */
		md5_calcHashValue(md5, newData + 64);	
		/* 内存释放 */
		free(newData);
	}
}
LOCAL VOID md5_calcHashValue(MD5STR * md5, UINT8 * data)
{
	UINT32 m[16] = {0};
	
	/* 根据输入的512bit进行Mj的自分组计算 */
	md5_calcM(m, data);

	/* 初始化a、b、c、d（前一组的散列值输出，或最初始的ABCD） */
	UINT32 a = md5->state[0];
	UINT32 b = md5->state[1];
	UINT32 c = md5->state[2];
	UINT32 d = md5->state[3];
	
	/*
	 * 第一轮
	 * ①func(X,Y,Z) = (X & Y) | (~X & Z)
	 * ②Mj = M[i]
	 * ③s=7、12、17、22。
	 * 64个Ti直接计算出来，而不是让计算机根据公式再去计算
	 */
	MD5_FIRST_ROUND(a, b, c, d, m[ 0], 7,  0xd76aa478);   
	MD5_FIRST_ROUND(d, a, b, c, m[ 1], 12, 0xe8c7b756);   
	MD5_FIRST_ROUND(c, d, a, b, m[ 2], 17, 0x242070db);   
	MD5_FIRST_ROUND(b, c, d, a, m[ 3], 22, 0xc1bdceee);   
	MD5_FIRST_ROUND(a, b, c, d, m[ 4], 7,  0xf57c0faf);   
	MD5_FIRST_ROUND(d, a, b, c, m[ 5], 12, 0x4787c62a);   
	MD5_FIRST_ROUND(c, d, a, b, m[ 6], 17, 0xa8304613);   
	MD5_FIRST_ROUND(b, c, d, a, m[ 7], 22, 0xfd469501);   
	MD5_FIRST_ROUND(a, b, c, d, m[ 8], 7,  0x698098d8);   
	MD5_FIRST_ROUND(d, a, b, c, m[ 9], 12, 0x8b44f7af);   
	MD5_FIRST_ROUND(c, d, a, b, m[10], 17, 0xffff5bb1);   
	MD5_FIRST_ROUND(b, c, d, a, m[11], 22, 0x895cd7be);   
	MD5_FIRST_ROUND(a, b, c, d, m[12], 7,  0x6b901122);   
	MD5_FIRST_ROUND(d, a, b, c, m[13], 12, 0xfd987193);   
	MD5_FIRST_ROUND(c, d, a, b, m[14], 17, 0xa679438e);   
	MD5_FIRST_ROUND(b, c, d, a, m[15], 22, 0x49b40821);   

	/*第二轮
	 *①func(X,Y,Z) = (X & Z) | (Y & ~Z)
	 *②index(Mj) = [index(Mj-1) + 5] % 16,其中M0 = M[1]
	 *③s = 5、9、14、20
	 */
	MD5_SECOND_ROUND(a, b, c, d, m[ 1], 5,  0xf61e2562);   
	MD5_SECOND_ROUND(d, a, b, c, m[ 6], 9,  0xc040b340);   
	MD5_SECOND_ROUND(c, d, a, b, m[11], 14, 0x265e5a51);   
	MD5_SECOND_ROUND(b, c, d, a, m[ 0], 20, 0xe9b6c7aa);   
	MD5_SECOND_ROUND(a, b, c, d, m[ 5], 5,  0xd62f105d);   
	MD5_SECOND_ROUND(d, a, b, c, m[10], 9,  0x02441453);   
	MD5_SECOND_ROUND(c, d, a, b, m[15], 14, 0xd8a1e681);   
	MD5_SECOND_ROUND(b, c, d, a, m[ 4], 20, 0xe7d3fbc8);   
	MD5_SECOND_ROUND(a, b, c, d, m[ 9], 5,  0x21e1cde6);   
	MD5_SECOND_ROUND(d, a, b, c, m[14], 9,  0xc33707d6);   
	MD5_SECOND_ROUND(c, d, a, b, m[ 3], 14, 0xf4d50d87);   
	MD5_SECOND_ROUND(b, c, d, a, m[ 8], 20, 0x455a14ed);   
	MD5_SECOND_ROUND(a, b, c, d, m[13], 5,  0xa9e3e905);   
	MD5_SECOND_ROUND(d, a, b, c, m[ 2], 9,  0xfcefa3f8);   
	MD5_SECOND_ROUND(c, d, a, b, m[ 7], 14, 0x676f02d9);   
	MD5_SECOND_ROUND(b, c, d, a, m[12], 20, 0x8d2a4c8a);   
	
	/*
	 *第三轮：
	 *①func(X,Y,Z) = X ^ Y ^ Z
	 *②index(Mj) = [index(Mj-1) + 3] % 16,其中M0 = M[5]
	 *③s=4、11、16、23
	 */
	MD5_THIRD_ROUND(a, b, c, d, m[ 5], 4,  0xfffa3942);   
	MD5_THIRD_ROUND(d, a, b, c, m[ 8], 11, 0x8771f681);   
	MD5_THIRD_ROUND(c, d, a, b, m[11], 16, 0x6d9d6122);   
	MD5_THIRD_ROUND(b, c, d, a, m[14], 23, 0xfde5380c);   
	MD5_THIRD_ROUND(a, b, c, d, m[ 1], 4,  0xa4beea44);   
	MD5_THIRD_ROUND(d, a, b, c, m[ 4], 11, 0x4bdecfa9);   
	MD5_THIRD_ROUND(c, d, a, b, m[ 7], 16, 0xf6bb4b60);   
	MD5_THIRD_ROUND(b, c, d, a, m[10], 23, 0xbebfbc70);   
	MD5_THIRD_ROUND(a, b, c, d, m[13], 4,  0x289b7ec6);   
	MD5_THIRD_ROUND(d, a, b, c, m[ 0], 11, 0xeaa127fa);   
	MD5_THIRD_ROUND(c, d, a, b, m[ 3], 16, 0xd4ef3085);   
	MD5_THIRD_ROUND(b, c, d, a, m[ 6], 23, 0x04881d05);   
	MD5_THIRD_ROUND(a, b, c, d, m[ 9], 4,  0xd9d4d039);   
	MD5_THIRD_ROUND(d, a, b, c, m[12], 11, 0xe6db99e5);   
	MD5_THIRD_ROUND(c, d, a, b, m[15], 16, 0x1fa27cf8);   
	MD5_THIRD_ROUND(b, c, d, a, m[ 2], 23, 0xc4ac5665);   
	
	/*
	 *第四轮：
	 *①func(X,Y,Z) = Y ^ (X | ~Z)
	 *②index(Mj) = [index(Mj-1) + 7] % 16,其中M0 = M[0]。
	 *③s=6、10、15、21、。
	 */
	MD5_LAST_ROUND(a, b, c, d, m[ 0], 6,  0xf4292244);   
	MD5_LAST_ROUND(d, a, b, c, m[ 7], 10, 0x432aff97);   
	MD5_LAST_ROUND(c, d, a, b, m[14], 15, 0xab9423a7);   
	MD5_LAST_ROUND(b, c, d, a, m[ 5], 21, 0xfc93a039);   
	MD5_LAST_ROUND(a, b, c, d, m[12], 6,  0x655b59c3);   
	MD5_LAST_ROUND(d, a, b, c, m[ 3], 10, 0x8f0ccc92);   
	MD5_LAST_ROUND(c, d, a, b, m[10], 15, 0xffeff47d);   
	MD5_LAST_ROUND(b, c, d, a, m[ 1], 21, 0x85845dd1);   
	MD5_LAST_ROUND(a, b, c, d, m[ 8], 6,  0x6fa87e4f);   
	MD5_LAST_ROUND(d, a, b, c, m[15], 10, 0xfe2ce6e0);   
	MD5_LAST_ROUND(c, d, a, b, m[ 6], 15, 0xa3014314);   
	MD5_LAST_ROUND(b, c, d, a, m[13], 21, 0x4e0811a1);   
	MD5_LAST_ROUND(a, b, c, d, m[ 4], 6,  0xf7537e82);   
	MD5_LAST_ROUND(d, a, b, c, m[11], 10, 0xbd3af235);   
	MD5_LAST_ROUND(c, d, a, b, m[ 2], 15, 0x2ad7d2bb);   
	MD5_LAST_ROUND(b, c, d, a, m[ 9], 21, 0xeb86d391); 
	
	/* 4轮64步完毕后更新散列值缓冲区 */
	md5->state[0] += a;
	md5->state[1] += b;
	md5->state[2] += c;
	md5->state[3] += d;
}
LOCAL VOID md5_calcM(UINT32 * m, UINT8 * data)
{
	int i = 0; 
	int j = 0;
	for(i = 0; i < 16; i++){
		/* 低位->低位 */
		m[i] = data[j + 0] 
			| (data[j + 1] << 8) 
			| (data[j + 2] << 16) 
			| (data[j + 3] << 24);
		j += 4;
	}
}
