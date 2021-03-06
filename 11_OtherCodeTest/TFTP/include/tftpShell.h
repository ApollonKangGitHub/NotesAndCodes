/*
 * File: tftpShell.h
 * Function: 
 *     tftp服务器、客户端、基础模块相关命令注册与解析
 *     命令行获取、执行的任务模块
 * Time: 2019-10-6 11:09:20
 * Statement: 
 *     本程序仅可作学习交流之用，可在学习为目的的基础上任意传播
 *     未经授权不可以任何形式商用，凡是有通过非免费手段获取到该代码
 *     均可邮件联系，已达到净化学习交流环境的目的
 * Author: Kangruojin
 * Mail: mailbox_krj@163.com
 * CSDN: Apollon_krj
 * GITHUB: ApollonKangGitHub
 *
 */

#ifndef __TFTP_SHELL_H__
#define __TFTP_SHELL_H__

#include <tftpType.h>

#define __TFTP_SHELL_VERSION_	"tftp Shell1.0"

/* 
 * shell线程资源栈大小，线程栈设置稍大，
 * 防止局部命令行解析的线程栈变量过大导致段错误
 */
#define __TFTP_SHELL_TASK_STACK_SIZE_		(0x200000)	

/* 命令最大长度 */
#define __TFTP_SHELL_CMD_MAX_LEN_ 			(1U << 5)

/* 一条命令argc最大值 */
#define __TFTP_SHELL_CMD_MAX_NUM_			(1U << 5)

/* 命令注册的字符串最大长度 */
#define __TFTP_CMD_REG_STR_LEN_				(1U << 11)

/* shell输入输出缓冲区大小 */
#define __TFTP_SHELL_BUFFER_LEN_MAX_		(__TFTP_SHELL_CMD_MAX_LEN_ * __TFTP_SHELL_CMD_MAX_NUM_)

typedef UINT32  tftpCmdAbil_t;

#define __TFTP_CMD_NORMAL_		(1U << 0)
#define __TFTP_CMD_HIDE_		(1U << 1)
#define __TFTP_CMD_DYN_			(1U << 2)

typedef VOID (*tftp_cmd_deal_fun)(INT32 argc, CHAR * argv[]);

typedef enum tftpCmdType_e
{
	tftpCmdType_cmd,
	tftpCmdType_str,
	tftpCmdType_int32,
	tftpCmdType_uint32,
	tftpCmdType_hex,
	tftpCmdType_ip,
	tftpCmdType_unknown,
	tftpCmdType_max
}tftpCmdType_t;

/* CMD默认是指令而非参数，该宏正常注册用不到 */
#define __TFTP_CMD_CMD_		"__CMD__"
#define __TFTP_CMD_STR_		"__STRING__"
#define __TFTP_CMD_INT_		"__INT32__"
#define __TFTP_CMD_UINT_	"__UINT32__"
#define __TFTP_CMD_HEX_		"__HEX32__"
#define __TFTP_CMD_IP_		"__IPADDR__"

typedef struct tftpCmdInfo_s
{
	CHAR * _cmdStr;			/* 命令字符串 */
	CHAR * _cmdDescr;		/* 命令描述 */
	tftpCmdType_t _type;		/* 命令类型 */
}tftpCmdInfo_t;

typedef struct tftpShellCmd_s
{
	tftpCmdInfo_t _info[__TFTP_SHELL_CMD_MAX_NUM_];
}tftpShellCmd_t;

typedef struct tftpShellList_s
{
	INT32 _cmdArgc;
	tftpShellCmd_t _cmdArgv;
	tftpCmdAbil_t _status;		/* 命令的能力、属性状态 */
	tftp_cmd_deal_fun _dealFun;	/* 命令的执行函数 */
	struct tftpShellList_s * _pre;
	struct tftpShellList_s * _next;
}tftpShellList_t;

EXTERN INT32 tftp_shell_module_init(VOID);
EXTERN tftpReturnValue_t tftp_shell_cmd_register
(
	tftp_cmd_deal_fun function, 
	tftpCmdAbil_t ability,
	CHAR * cmd_str
);
EXTERN INT32 tftp_shell_wait_for_string(CHAR * str, INT32 strLen);

#endif /* __TFTP_SHELL_H_ */
