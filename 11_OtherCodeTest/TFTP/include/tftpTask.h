#ifndef __TFTP_TASK_H_
#define __TFTP_TASK_H_

#include <tftpType.h>
#include <tftpPublic.h>

#ifdef TASK_COMM_LEN
#define __TFTP_TASK_NAME_LENGTH_ 	TASK_COMM_LEN
#else
#define __TFTP_TASK_NAME_LENGTH_ 	(16)
#endif

/* 链表局部任务id起始编号 */
#define __TFTP_TASK_ID_START_ 		(1)

/* 任务detach状态 */
#define __TFTP_TASK_DETACHED_ PTHREAD_CREATE_DETACHED
#define __TFTP_TASK_ATTACHED_ PTHREAD_CREATE_JOINABLE

#define __TFTP_TASK_NAME_SHELL_		"tftpShellTask"
#define __TFTP_TASK_NAME_MAIN_		"tftpMainTask"
#define __TFTP_TASK_NAME_SERVER_	"tftpServerTask"

typedef INT64 tftpTid_t;

typedef struct tftpTaskInfo_s{
	CHAR _name[__TFTP_TASK_NAME_LENGTH_];		/* 任务名 */
	INT64 _tid;			/* 任务ID */
	INT32 _stackSize;	/* 任务栈大小 */
	INT32 _detachState;	/* 分离属性 */
	VOID * (*_deal_function)(VOID *);	/* 任务处理函数 */
}tftpTaskInfo_t;

typedef struct tftpTaskInfoList_s{
	INT32 _taskNum;						/* 线程链表的任务个数 */
	INT32 _taskId;						/* 链表中的任务编号 */
	tftpTaskInfo_t _taskInfo;			/* 存放任务信息 */
	struct tftpTaskInfoList_s * _next;	/* 指向下一个节点 */
	struct tftpTaskInfoList_s * _pre;	/* 指向上一个节点 */
}tftpTaskInfoList_t;
 
/* 名字的长度最大为15字节，且应该以'\0'结尾 */
#define tftp_task_set_name(name)   prctl(PR_SET_NAME, name, 0, 0, 0)

//char tname[16];
#define tftp_task_get_name(name)   prctl(PR_GET_NAME, name)

EXTERN tftpReturnValue_t tftp_task_module_init(VOID);
EXTERN tftpReturnValue_t tftp_task_create_init(tftpTaskInfo_t * taskInfo);
EXTERN tftpReturnValue_t tftp_task_destroy(tftpTid_t tid);
EXTERN tftpTid_t tftp_task_get_tid(VOID);
EXTERN INT32 tftp_task_get_info(INT32 taskId,tftpTaskInfo_t * taskInfo);
EXTERN INT32 tftp_task_get_info_by_tid(tftpTid_t tid, tftpTaskInfo_t * taskInfo);
EXTERN INT32 tftp_task_get_info_by_name(CHAR * taskName, tftpTaskInfo_t * taskInfo);
#endif