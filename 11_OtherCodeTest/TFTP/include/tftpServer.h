#ifndef __TFTP_SERVER_H__
#define __TFTP_SERVER_H__

#include <tftpType.h>
#include <tftpSem.h>
#include <tftpPublic.h>

#define __TFTP_FILE_EOF_					(EOF)
#define __TFTP_SERVER_TASK_STACK_SIZE_		(0x400000)
#define __TFTP_CLIENT_TASK_STACK_SIZE_		(0x100000)
#define __TFTP_SERVER_SOCKET_UDP_PORT_		(69)
#define __TFTP_SERVER_IP_ADDR_				(INADDR_ANY)
/* 
 * 通信端口建议：
 * 美国IANA建议使用49152~65535
 * Linux 32768~61000
 * Windows 1025~5000
 */
#define __TFTP_CLIENT_SOCKET_UDP_PORT_MIN_	(55555)
#define __TFTP_CLIENT_SOCKET_UDP_PORT_MAX_	(59999)

typedef enum tftpErroCode_e
{
	tftp_ErrCode_NotFound 		= 0,	/* Not defined, see error message (if any). */
	tftp_ErrCode_FileNotFound 	= 1,	/* File not found. */
	tftp_ErrCode_AccViolate 	= 2,	/* Access violation */
	tftp_ErrCode_DiskFull		= 3,	/* Disk full or allocation exceeded. */
	tftp_ErrCode_IllegalOper	= 4,	/* Illegal TFTP operation. */
	tftp_ErrCode_UnknownId  	= 5,	/* Unknown transfer ID. */
	tftp_ErrCode_FileExist 		= 6,	/* File already exists. */
	tftp_ErrCode_NoSuchUser		= 7,	/* No such user. */
	tftp_ErrCode_Invalid		= 8		/* last invalid error code, please. */
}tftpErrCode_t;

#define __TFTP_FILENAME_STR_LEN_  	(64)	
#define __TFTP_TASK_POOL_MIN_		(5)		/* 线程池最少线程数目 */
#define __TFTP_TASK_POOL_MAX_		(20)	/* 线程池最多线程数目 */

typedef struct tftpSocketInfo_s
{
	INT32 _sockId;								/* 与客户端建立连接的sockId */
	CHAR _fileName[__TFTP_FILENAME_STR_LEN_];	/* 请求报文中的文件名 */
	UINT16 _opcode;								/* 请求报文中的操作符 */
	INT32 _fileFd;			/* 文件描述符 */
	UINT32 _bpId;			/* 请求报文中的断点块号，支持断点续传 */
	UINT32 _tSize;			/* 请求报文中的文件大小 */
	UINT16 _blkSize;		/* 块大小 */
	UINT16 _timeout;		/* 超时重传时间，支持超时重传 */
	struct sockaddr_in _cliAddr;				/* 客户端相关连接信息 */
}tftpSocketInfo_t;

/* 线程池节点结构，可构建静态/动态线程池，选择复合结构线程池 */
typedef struct tftpTaskPool_s
{
	 VOLATILE BOOL _busy;			/* 标志线程是否空闲 */
	 tftpPid_t _tid;				/* 线程tid */
	 tftpSem_t * _syncLock;			/* 主线程与通信线程之间的同步信号量 */
	 UINT32 _port;					/* 线程任务通信端口号 */
	 tftpSocketInfo_t _cliInfo;		/* 客户端相关通信信息 */
}tftpTaskPool_t;

/* 线程池结构 */
typedef struct tftpTaskPoolList_s
{
	tftpTaskPool_t _taskNode;
	struct tftpTaskPoolList_s * _next;
	struct tftpTaskPoolList_s * _pre;
}tftpTaskPoolList_t;
EXTERN tftpReturnValue_t tftp_server_module_init(VOID);

#endif /* __TFTP_SERVER_H__ */
