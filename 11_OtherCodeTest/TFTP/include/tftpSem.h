#ifndef __TFTP_SEM_H_
#define __TFTP_SEM_H_

#include <tftpType.h>
#include <tftpTask.h>
#include <tftpPublic.h>

#define __TFTP_SEM_NAME_TASK_ 		"semTaskInfo"
#define __TFTP_SEM_NAME_SLEF_ 		"semSelfInfo"
#define __TFTP_SEM_NAME_POOL_		"semPool"
#define __TFTP_SEM_NAME_CHILD_		"semChild"

#define __TFTP_SEM_NAME_LENGTH_ (32)

typedef sem_t tftpSem_t;

typedef enum tftpSemStatus_e
{
	tftp_semStatus_wait,	/* 占用 */
	tftp_semStatus_post,	/* 挂起 */
	tftp_semStatus_max
}tftpSemStatus_t;

typedef enum tftpSemShare_e
{
	tftp_semShared_thread,	/* 线程之间共享 */
	tftp_semShared_process,	/* 进程之间共享 */
	tftp_semShared_max
}tftpSemShare_t;

#define __TFTP_DEFINED_SEM_TIMEOUT_ (1)
#ifndef __TFTP_DEFINED_SEM_TIMEOUT_
	typedef struct timespec tftpSemTimeout_t;
#else
	typedef struct tftpSemTimeout_s{
		time_t _sec;      /* Seconds */ 
		long   _nsec;     /* Nanoseconds [0 .. 999999999]  */
	}tftpSemTimeout_t;
#endif

typedef struct tftpSemInfo_s{
	CHAR _semName[__TFTP_SEM_NAME_LENGTH_];	/* 信号量名字 */
	tftpSemShare_t _pshared;	/* 共享范围 */
	tftpSem_t * _semId;			/* 创建的信号量ID */
	tftpPid_t _semTask;			/* 信号量占用者tid */
	tftpSemStatus_t _status;	/* 信号量状态 */
	BOOL _waitForever;			/* 是否等待超时，TRUE时_timeout才有效，FALSE时为一直等 */
	tftpSemTimeout_t _timeout;	/* 信号量wait时间 */
}tftpSemInfo_t;

typedef struct tftpSemInfoList_s
{
	tftpSemInfo_t _semInfo;		/* 信号量结构 */
	struct tftpSemInfoList_s * _next;	/* 下一个信号量 */
	struct tftpSemInfoList_s * _pre;	/* 上一个信号量 */
}tftpSemInfoList_t;

EXTERN tftpReturnValue_t tftp_sem_create(tftpSemInfo_t * semInfo);
EXTERN INT32 tftp_sem_destroy(tftpSem_t * semId);
EXTERN INT32 tftp_sem_wait(tftpSemInfo_t * semInfo);
EXTERN INT32 tftp_sem_post(tftpSem_t * semId);
EXTERN tftpReturnValue_t tftp_sem_module_init(VOID);
EXTERN tftpReturnValue_t tftp_sem_create_init(IN OUT tftpSemInfo_t * pSemInfo);
EXTERN tftpReturnValue_t tftp_sem_save_tid(tftpSem_t * semId, tftpPid_t tid);
EXTERN tftpSemInfo_t * tftp_sem_info_node_find(IN tftpSem_t * semId, OUT tftpSemInfo_t ** pSemInfo);

#endif