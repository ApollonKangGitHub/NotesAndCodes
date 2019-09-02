#ifndef __TFTP_SERVER_H__
#define __TFTP_SERVER_H__

#include <tftpType.h>
#include <tftpSem.h>
#include <tftpPublic.h>
#include <tftpPack.h>

#define __TFTP_TID_ALL_						(-1)
#define __TFTP_FILE_EOF_					(EOF)
#define __TFTP_SERVER_TASK_STACK_SIZE_		(0x400000)
#define __TFTP_CLIENT_TASK_STACK_SIZE_		(0x100000)

#define __TFTP_FILENAME_STR_LEN_  	(128)	
#define __TFTP_TASK_POOL_MIN_		(10)	/* 线程池最少线程数目 */
#define __TFTP_TASK_POOL_MAX_		(20)	/* 线程池最多线程数目 */

typedef struct tftpSocketInfo_s
{
	INT32 _sockId;								/* 与客户端建立连接的sockId */
	CHAR _fileName[__TFTP_FILENAME_STR_LEN_];	/* 请求报文中的文件名 */
	UINT16 _opcode;								/* 请求报文中的操作符 */
	CHAR _pMode[__TFTP_MODE_MAX_];				/* 文件传输模式 */
	tftpPackMode_t _mode;						/* 文件传输模式枚举 */
	UINT32 _tSize;			/* 请求报文中的文件大小 */
	UINT16 _bpId;			/* 请求报文中的断点块号，支持断点续传 */
	UINT16 _blkSize;		/* 块大小 */
	UINT16 _times;			/* 超时重传次数 */
	UINT16 _timeout;		/* 超时重传时间，支持超时重传 */
	struct sockaddr_in _cliAddr;				/* 客户端相关连接信息 */
}tftpSocketInfo_t;

/* 线程池节点结构，可构建静态/动态线程池，选择复合结构线程池 */
typedef struct tftpTaskPool_s
{
	VOLATILE BOOL _busy;			/* 标志线程是否空闲 */
	tftpPid_t _tid;					/* 线程tid，与同步信号量一一对应 */
	tftpSem_t * _syncLock;			/* 主线程与通信线程之间的同步信号量 */
	INT32 _sockfd;					/* 通信的socket fd */
	UINT32 _port;					/* 线程任务通信端口号 */
	INT32 _fileFd;					/* 文件描述符 */
	tftpSocketInfo_t _cliInfo;		/* 客户端相关通信信息 */
}tftpTaskPool_t;

/* 线程池结构 */
typedef struct tftpTaskPoolList_s
{
	tftpTaskPool_t _taskNode;
	struct tftpTaskPoolList_s * _next;
	struct tftpTaskPoolList_s * _pre;
}tftpTaskPoolList_t;

#if 0
#define LINK_SYNC_LOCK(tid, semInfo) \
		
#define LINK_SYNC_UNLOCK(tid, semInfo) 
#endif

EXTERN tftpReturnValue_t tftp_server_module_init(VOID);
EXTERN tftpReturnValue_t tftp_cmd_del_task_pool(INT32 argc, CHAR * argv);

#endif /* __TFTP_SERVER_H__ */
