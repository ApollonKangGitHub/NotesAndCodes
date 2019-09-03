#ifndef __TFTP_PACK_H__
#define __TFTP_PACK_H__


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
#define __TFTP_DEFAULT_BLKSIZE_			(512)	/* default blksize is 512Bytes */

#define __TFTP_BPID_MAX_				(0xFFFF)
#define __TFTP_BPID_MIN_				(0x1)

#define __TFTP_TSIZE_MAX_				(0xFFFFFFFF)
#define __TFTP_TSIZE_MIN_				(0x1)

#define __TFTP_REQ_PACK_BUF_LEN_		(1024)

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
	tftp_Pack_ErrCode_NotFound 		= 0,	/* Not defined, see error message (if any). */
	tftp_Pack_ErrCode_FileNotFound 	= 1,	/* File not found. */
	tftp_Pack_ErrCode_AccViolate 	= 2,	/* Access violation */
	tftp_Pack_ErrCode_DiskFull		= 3,	/* Disk full or allocation exceeded. */
	tftp_Pack_ErrCode_IllegalOper	= 4,	/* Illegal TFTP operation. */
	tftp_Pack_ErrCode_UnknownId  	= 5,	/* Unknown transfer ID. */
	tftp_Pack_ErrCode_FileExist 	= 6,	/* File already exists. */
	tftp_Pack_ErrCode_NoSuchUser	= 7,	/* No such user. */
	tftp_Pack_ErrCode_Invalid		= 8		/* last invalid error code, please. */
}tftpPackErrCode_t;

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

EXTERN tftpPackOperCode_t tftp_pack_oper_para_get(CONST CHAR * operator);
EXTERN VOID tftp_pack_get_tranfer_mode
(
	CHAR * pMode, 
	CHAR * pSaveMode, 
	tftpPackMode_t * mode
);

EXTERN UINT16 tftp_pack_req
(
	UINT8 * buf,
	tftpPacktReq_t * reqPack
);

EXTERN tftpReturnValue_t tftp_unpack_req
(
	UINT8 * buf, 
	INT32 bufLen,	
	tftpPacktReq_t * reqPack
);


#endif /* __TFTP_PACK_H__ */
