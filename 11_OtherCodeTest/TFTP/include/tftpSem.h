#ifndef __TFTP_SEM_H_
#define __TFTP_SEM_G_

#include <tftpType.h>

#include <tftpPublic.h>
typedef struct tftpOperatorSem_s{
	sem_t	_sem;			/* 创建的信号量 */
	mode_t 	_semMode;		/* 权限 */	
	INT32 	_semFlag;		/* 信号量操作标志 */
	CHAR 	_semName[32];	/* 信号量名字 */
}tftpOperatorSem_t;

#endif