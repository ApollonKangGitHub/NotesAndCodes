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

typedef pthread_t tftpTaskStruct_t;
typedef pid_t tftpPid_t;
typedef pid_t tftpTaskId_t;

typedef struct tftpTaskInfo_s{
	CHAR _name[__TFTP_TASK_NAME_LENGTH_];		/* 任务名 */
	tftpTaskStruct_t _taskStructid;	/* 任务结构体地址 */
	tftpPid_t _pid;			/* pid */
	tftpPid_t _tid;			/* tid */
	INT32 _stackSize;		/* 任务栈大小 */
	INT32 _detachState;		/* 分离属性 */
	VOID * (*_deal_function)(VOID *);	/* 任务处理函数 */
}tftpTaskInfo_t;

/* pthread_t * 指向的结构体 */
typedef struct tftpTaskFake_s{
	void * nothing[90];
	tftpPid_t _tid;
	tftpPid_t _pid;
}tftpTaskFake_t;

/* 任务信息保存链表结构节点 */
typedef struct tftpTaskInfoList_s{
	INT32 _taskNum;						/* 线程链表的任务个数 */
	tftpTaskId_t _taskId;				/* 链表中的任务编号 */
	tftpTaskInfo_t _taskInfo;			/* 存放任务信息 */
	struct tftpTaskInfoList_s * _next;	/* 指向下一个节点 */
	struct tftpTaskInfoList_s * _pre;	/* 指向上一个节点 */
}tftpTaskInfoList_t;

/* extern声明，解决编译告警 */
extern int pthread_setname_np(pthread_t thread, const char *name);
extern int pthread_getname_np(pthread_t thread, char *name, size_t len);

#define tftp_task_set_name(tid,name) 			pthread_setname_np(tid,name)
#define tftp_task_get_name(tid,pName,len)		pthread_getname_np(tid,pName,len)
#define tftp_task_get_tid()   					syscall(SYS_gettid)
#define tftp_task_get_pid()						getpid()
#define tftp_task_get_structId()				pthread_self()

EXTERN VOID tftp_task_list_display(VOID);
EXTERN tftpReturnValue_t tftp_task_module_init(VOID);
EXTERN tftpReturnValue_t tftp_task_create_init(tftpTaskInfo_t * taskInfo);
EXTERN tftpReturnValue_t tftp_task_destroy(tftpTaskStruct_t tid);
EXTERN tftpPid_t tftp_task_get_pid_by_structId(tftpTaskStruct_t tid);
EXTERN tftpPid_t tftp_task_get_tid_by_structId(tftpTaskStruct_t tstructId);
EXTERN tftpTaskId_t tftp_task_get_info_by_structId(tftpTaskStruct_t tid, tftpTaskInfo_t * taskInfo);
EXTERN tftpTaskId_t tftp_task_get_info_by_name(CHAR * taskName, tftpTaskInfo_t * taskInfo);
#endif