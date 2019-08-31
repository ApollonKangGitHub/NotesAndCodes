#ifndef __TFTP_TYPE_H_
#define __TFTP_TYPE_H_

#include <stdio.h>

#define IN
#define OUT

#define TRUE 	(1)
#define FALSE 	(0)

#define LOCAL 	static
#define EXTERN 	extern
#define CONST  	const
#define VOLATILE volatile 
#define BOOL 	int
#define VOID 	void 
#define CHAR 	char

#define UINT64 	unsigned long long
#define UINT32 	unsigned int 
#define UINT16 	unsigned short 
#define UINT8 	unsigned char

#define INT64 	signed long long
#define INT32 	signed int 
#define INT16 	signed short 
#define INT8 	signed char 

#define __GET_BIT(addr, bitPos) \
		(((((UINT8 *)(addr))[(bitPos) / 8]) >> ((bitPos) % 8)) & 1U)
#define __SET_BIT(addr, bitPos, setBit) ((setBit) \
		? ((((UINT8 *)(addr))[(bitPos) / 8]) |= (1U << ((bitPos) % 8))) \
		: ((((UINT8 *)(addr))[(bitPos) / 8]) &= ~(1U << ((bitPos) % 8))))

#define _TEST_FALSE(addr, bitPos) \
		(__GET_BIT((addr), (bitPos)) ? (0) : (1U))
#define _TEST_TRUE(addr, bitPos) \
		(__GET_BIT((addr), (bitPos)) ? (1U) : (0))

typedef enum tftpReturnValue_e
{
	tftp_ret_Ok,
	tftp_ret_Error,
	tftp_ret_Invalid,
	tftp_ret_NotFound,
	tftp_ret_NotSupport,
	tftp_ret_Null,
	tftp_ret_Max
}tftpReturnValue_t;

EXTERN CHAR * tftp_err_code_msg[tftp_ret_Max + 1];

#define tftp_err_msg(index) \
		((index >= tftp_ret_Ok && index < tftp_ret_Max) ? \
		tftp_err_code_msg[index] : \
		tftp_err_code_msg[tftp_ret_Max])

#define tftp_print printf
#define tftp_vfprint vfprintf
#define tftp_sprint sprintf
#define tftp_gets fgets
#define tftp_perror perror
#define tftp_fflush fflush

#endif /* __TFTP_TYPE_H */
