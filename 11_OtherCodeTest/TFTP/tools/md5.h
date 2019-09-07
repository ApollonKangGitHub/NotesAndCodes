#ifndef _MD5_H_
#define _MD5_H_

#include <tftpPublic.h>
#include <tftpType.h>

typedef struct md5_struct{
	UINT32 state[8];			/* 存放散列值 */
	UINT32 length[2];			/* 用length[0]存放 */
}MD5STR;

LOCAL VOID md5_showHashValue(MD5STR *, UINT8 *);
LOCAL VOID md5_init(MD5STR *, UINT32);
LOCAL VOID md5_padding(MD5STR *, UINT8 *, UINT32);
LOCAL VOID md5_calcHashValue(MD5STR *, UINT8 *);
LOCAL VOID md5_calcM(UINT32 *, UINT8 *);

#define MD5_FIRST_ROUND(a, b, c, d, mj, s, ti) \
	do { \
		UINT32 tmp = (b & c) | ((~b) & d); \
		tmp += a + mj + ti; \
		a = b + ((tmp << s) | (tmp >> (32 - s))); \
	}while(0)
	
#define MD5_SECOND_ROUND(a, b, c, d, mj, s, ti) \
	do{ \
		UINT32 tmp = (b & d) | (c & (~d)); \
		tmp += a + mj + ti; \
		a = b + ((tmp << s) | (tmp >> (32 - s))); \
	}while(0)
	
#define MD5_THIRD_ROUND(a, b, c, d, mj, s, ti) \
	do{ \
		UINT32 tmp = b ^ c ^ d; \
		tmp += a + mj + ti; \
		a = b + ((tmp << s) | (tmp >> (32 - s))); \
	}while(0)
		
#define MD5_LAST_ROUND(a, b, c, d, mj, s, ti) \
	do{ \
		UINT32 tmp = c ^ (b | (~d)); \
		tmp += a + mj + ti; \
		a = b + ((tmp << s) | (tmp >> (32 - s))); \
	}while(0)

#endif /* _MD5_H_ */
