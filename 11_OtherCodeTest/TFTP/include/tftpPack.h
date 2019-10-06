/*
 * File: tftpPack.h
 * Function: 
 *     tftp客户端、服务器公共基础模块部分
 *     用于服务器和客户端的报文封装和解封装处理
 *     以及相关协议字段定义与限制
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

#ifndef __TFTP_PACK_H__
#define __TFTP_PACK_H__

#define __TFTP_RECV_BUF_LEN_ 		(1024 * 9)
#define __TFTP_SEND_BUF_LEN_		(1024 * 9)

#define __TFTP_IP_ADDR_LEN_			(16)

#define __TFTP_FILENAME_STR_LEN_  	(128)	
#define __TFTP_TRAN_MODE_LEN_		(16)
#define __TFTP_FILE_PATH_LEN_		(512)
#define __TFTP_FILE_NAME_LEN_		(128)

#define __TFTP_TIMEOUT_MIN_			(1)
#define __TFTP_TIMEOUT_MAX_			(255)
#define __TFTP_TIMEOUT_DEFAULT_ 	(60)	/* default timeout is 60s */

#define __TFTP_TMFREQ_MIN_			(1)
#define __TFTP_TMFREQ_MAX_			(15)
#define __TFTP_TMFREQ_DEFAULT_		(5)

#define __TFTP_BLKSIZE_128_BYTES_		(128)
#define __TFTP_BLKSIZE_256_BYTES_		(256)
#define __TFTP_BLKSIZE_512_BYTES_		(512)
#define __TFTP_BLKSIZE_1024_BYTES_		(1024)
#define __TFTP_BLKSIZE_1428_BYTES_		(1428)
#define __TFTP_BLKSIZE_2048_BYTES_		(2048)
#define __TFTP_BLKSIZE_4096_BYTES_		(4096)
#define __TFTP_BLKSIZE_8192_BYTES_		(8192)
#define __TFTP_DEFAULT_BLKSIZE_			(512)	/* default blksize is 512Bytes */

#define __TFTP_BLKID_MAX_				(0xFFFF)
#define __TFTP_BLKID_MIN_				(0x1)

#define __TFTP_TSIZE_MAX_				(0x8FFFFFFF)
#define __TFTP_TSIZE_MIN_				(0x1)

#define __TFTP_OPTION_MAX_LEN_ 			(64)
#define __TFTP_REQ_PACK_BUF_LEN_		(1024)

#define __TFTP_ERR_PACK_MAX_LEN_		(256)

/* 操作码，标识报文类型 */
typedef enum tftpPackOperCode_e
{
	tftp_Pack_OperCode_Rrq 	= 1,		/* Read request (RRQ),	RFC-1350 */
	tftp_Pack_OperCode_Wrq 	= 2,		/* Write request (WRQ),	RFC-1350 */
	tftp_Pack_OperCode_Data	= 3,		/* Data (DATA),			RFC-1350 */
	tftp_Pack_OperCode_Ack 	= 4,		/* Acknowledgment (ACK),RFC-1350 */
	tftp_Pack_OperCode_Err 	= 5,		/* Error (ERROR),		RFC-1350 */
	tftp_Pack_OperCode_Oack	= 6,		/* Optinas Ack,			RFC-2347 */
	tftp_Pack_OperCode_Max
}tftpPackOperCode_t;

#define __TFTP_OPCODE_RRQ_		(1u)
#define __TFTP_OPCODE_WRQ_		(2U)
#define __TFTP_OPCODE_DATA_		(3U)
#define __TFTP_OPCODE_ACK_		(4U)
#define __TFTP_OPCODE_ERR_		(5U)
#define __TFTP_OPCODE_OACK_		(6U)

#define __TFTP_OPTION_TSIZE_		"tsize"
#define __TFTP_OPTION_TIMEOUT_		"timeout"
#define __TFTP_OPTION_TMFREQ_		"tmfreq"
#define __TFTP_OPTION_BIKSIZE_		"blksize"
#define __TFTP_OPTION_BPID_			"bpid"

/*
 * 1.octet即八位binary方式为最小单元传输，octet方式传输在接收方不会改变内容，直接存到文件
 * 2.netascii方式传输会改变原有内容，在在保存时会将net的接收信息转换为本地主机格式再存入文件
 *     Unix/Linux操作系统每行结尾只有换行符，即'\n';而Mac系统里则使用回车来代表结尾，即'\r';
 *     Windows则是回车+换行，即"\r\n".那么为了非Windows系统对于多出的'\r'/'\n'不被识别为^M
 *     netascii和octet模式对于send来讲没有区别，只是对recv保存文件会有差异。
 * 3.已经不再被支持，将数据直接返回给用户，而不是保存为文件，对于该版本：下载支持上mail传不支持mail
 */
#define __TFTP_MODE_NETASCII_	"netascii"
#define __TFTP_MODE_OCTET_		"octet"
#define __TFTP_MODE_MAIL_		"mail"

/* tftp传输模式 */
typedef enum tftpPackMode_e
{
	tftp_Pack_Mode_netascii,			
	tftp_Pack_Mode_octet,				
	tftp_Pack_Mode_mail,
	tftp_Pack_Mode_max
}tftpPackMode_t;

/* 错误码，标识错误类型 */
typedef enum tftpPackErroCode_e
{
	tftp_Pack_ErrCode_NotDefined	= 0,	/* Not defined, see error message (if any). */
	tftp_Pack_ErrCode_FileNotFound 	= 1,	/* File not found. */
	tftp_Pack_ErrCode_AccViolate 	= 2,	/* Access violation */
	tftp_Pack_ErrCode_DiskFull		= 3,	/* Disk full or allocation exceeded. */
	tftp_Pack_ErrCode_IllegalOper	= 4,	/* Illegal TFTP operation. */
	tftp_Pack_ErrCode_UnknownId  	= 5,	/* Unknown transfer ID. */
	tftp_Pack_ErrCode_FileExist 	= 6,	/* File already exists. */
	tftp_Pack_ErrCode_NoSuchUser	= 7,	/* No such user. */
	tftp_Pack_ErrCode_Invalid		= 8		/* last invalid error code, please. */
}tftpPackErrCode_t;

#define __TFTP_ERR_NOTDEFINE_						"Unknown error."
#define __TFTP_ERR_NOTDEFINE_FILE_TOO_LARGE_		"Unknown error:file is to large."
#define __TFTP_ERR_NOTDEFINE_FILE_READ_FAIL_		"Unknown error:file read fail."
#define __TFTP_ERR_NOTDEFINE_FILE_WRITE_FAIL_		"Unknown error:file write fail."
#define __TFTP_ERR_NOTDEFINE_OPCODE_INVALID_		"Unknown error:invalid opcode"
#define __TFTP_ERR_NOTDEFINE_BLKSIZE_INVALID_		"Unknown error:invalid blksize"
#define __TFTP_ERR_NOTDEFINE_BPID_INVALID_			"Unknown error:invalid bpid"
#define __TFTP_ERR_NOTDEFINE_TIMEOUT_INVALID_		"Unknown error:invalid timout"
#define __TFTP_ERR_NOTDEFINE_TMFREQ_INVALID_		"Unknown error:invalid tmfreq"
#define __TFTP_ERR_NOTDEFINE_PACK_LEN_ERR_			"Unknown error:not match packet length"

#define __TFTP_ERR_FILENOTFOUED_	"File not found."
#define __TFTP_ERR_ACCVIOLATE_		"Access violation."
#define __TFTP_ERR_DISKFULL_		"Disk full or allocation exceeded."
#define __TFTP_ERR_ILLEGALOPER_		"Illegal TFTP operation."
#define __TFTP_ERR_UNKNOWNTD_		"Unknown transfer ID."
#define __TFTP_ERR_FILEXIST_		"File already exists."
#define __TFTP_ERR_NOSUCHUSER_		"No such user."
#define __TFTP_ERR_INVALID_			"Invalid eeeor code."

#define __TFTP_ERR_MSG_LEN_MAX_		(64)

typedef struct tftpPackOptions_s
{
	UINT8 _opt_tsize:1;
	UINT8 _opt_bpid:1;
	UINT8 _opt_blksize:1;
	UINT8 _opt_timout:1;
	UINT8 _opt_tmfreq:1;
	/* 更多定义根据需求/标准更新 */
	UINT8 _opt_other:1;	
}tftpPackOptions_t;

typedef struct tftpPacktReq_s
{
	UINT16 _opcode;								/* 请求报文中的操作符 */
	UINT16 _oack_opts;							/* 表示请求报文有扩展选项个数 */
	CHAR _fileName[__TFTP_FILENAME_STR_LEN_];	/* 请求报文中的文件名 */
	CHAR _pMode[__TFTP_TRAN_MODE_LEN_];			/* 文件传输模式 */
	tftpPackMode_t _mode;						/* 文件传输模式枚举 */
	tftpPackOptions_t _options;					/* 请求报文选项标志位结构 */
	UINT32 _tSize;			/* 请求报文中的文件大小 */
	UINT16 _bpId;			/* 请求报文中的断点块号，支持断点续传 */
	UINT16 _blkSize;		/* 块大小 */
	UINT16 _timeout;		/* 超时重传时间，支持超时重传 */
	UINT16 _tmfreq;			/* 超时重传次数 */
}tftpPacktReq_t;

#define __TFTP_OPCODE_SHIFT_ 	(0)
#define __TFTP_OPCODE_LEN_		(2)
#define __TFTP_ACK_SHIFT_		(2)
#define __TFTP_ACK_LEN_			(2)
#define __TFTP_ERROCDE_SHIFT_	(2)
#define __TFTP_ERRCODE_LEN_		(2)
#define __TFTP_BLKID_SHIFT		(2)
#define __TFTP_BLKID_LEN_		(2)
#define __TFTP_DATA_SHIFT_		(4)
#define __TFTP_ERRMSG_SHIFT_	(4)

#define TFTP_GET_OPCODE(recvBuf)			(ntohs(((UINT16 *)(recvBuf))[0])) 
#define TFTP_GET_ACK(recvBuf)				(ntohs(((UINT16 *)(recvBuf))[1]))	
#define TFTP_GET_BLKID(recvBuf)				(ntohs(((UINT16 *)(recvBuf))[1]))
#define TFTP_GET_ERRCODE(recvBuf)			(ntohs(((UINT16 *)(recvBuf))[1]))
#define TFTP_GET_ERRMSG(recvBuf)			(((UINT8 *)(recvBuf)) + __TFTP_ERRMSG_SHIFT_)

EXTERN tftpPackOperCode_t tftp_pack_oper_para_get(CONST CHAR * operator);
EXTERN VOID tftp_pack_get_tranfer_mode(CHAR * pMode, CHAR * pSaveMode, tftpPackMode_t * mode);
EXTERN UINT16 tftp_pack_req(UINT8 * buf,tftpPacktReq_t * reqPack);
EXTERN tftpReturnValue_t tftp_unpack_req(UINT8 * buf, INT32 bufLen,	tftpPacktReq_t * reqPack);
EXTERN UINT16 tftp_pack_ack(UINT8 * buf, UINT16 id);
EXTERN UINT16 tftp_pack_oack(UINT8 * buf, tftpPacktReq_t * reqPack);
EXTERN tftpReturnValue_t tftp_unpack_oack(UINT8 * buf, UINT16 recvLen, tftpPacktReq_t * recvPack);
EXTERN UINT16 tftp_pack_error(UINT8 * buf, tftpPackErrCode_t errCode, UINT8 * errMsg);
EXTERN UINT16 tftp_pack_data(UINT8 * buf, UINT16 blkid);


#endif /* __TFTP_PACK_H__ */
