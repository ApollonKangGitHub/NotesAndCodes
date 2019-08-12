#ifndef __TFTP_TASK_H_
#define __TFTP_TASK_H_

#include <tftpType.h>
#include <tftpPublic.h>

/* 任务detach状态 */
#define __TFTP_TASK_CREATE_DETACHED_ PTHREAD_CREATE_DETACHED
#define __TFTP_TASK_CREATE_ATTACHED_ PTHREAD_CREATE_JOINABLE

typedef struct tftpTaskInfo_s{
	CHAR _name[32];		/* 任务名 */
	INT32 _id;			/* 任务ID */
	INT32 _stackSize;	/* 任务栈大小 */
	INT32 _detachState;	/* 分离属性 */
	VOID * (*_deal_function)(VOID *);	/* 任务处理函数 */
}tftpTaskInfo_t;

typedef struct tftpTaskInfoList_s{
	tftpTaskInfo_t _taskInfo;			/* 存放任务信息 */
	struct tftpTaskInfoList_s * _next;	/* 指向下一个节点 */
}tftpTaskInfoList_t;

EXTERN tftpReturnValue_t tftp_task_module_init(VOID);
EXTERN tftpReturnValue_t tftp_task_destroy(tftpTaskInfo_t * taskInfo);
EXTERN tftpReturnValue_t tftp_task_create_init(tftpTaskInfo_t * taskInfo);
EXTERN tftpReturnValue_t tftp_task_get_info(INT32 tid, tftpTaskInfo_t * taskInfo);

#endif