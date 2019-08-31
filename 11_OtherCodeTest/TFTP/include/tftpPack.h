#ifndef __TFTP_PACK_H__
#define __TFTP_PACK_H__

/* 操作码，标识报文类型,RFC-1350 */
typedef enum tftpPackOperCode_e
{
	tftp_Pack_OperCode_Rrq 	= 1,		/* Read request (RRQ) */
	tftp_Pack_OperCode_Wrq 	= 2,		/* Write request (WRQ) */
	tftp_Pack_OperCode_Data	= 3,		/* Data (DATA) */
	tftp_Pack_OperCode_Ack 	= 4,		/* Acknowledgment (ACK) */
	tftp_Pack_OperCode_Err 	= 5,		/* Error (ERROR) */
	tftp_Pack_OperCode_Max
}tftpPackOperCode_t;

/* tftp传输模式 */
typedef enum tftpPackMode_e
{
	tftp_Pack_Mode_netascii,			
	tftp_Pack_Mode_octet,				
	tftp_Pack_Mode_mail
};

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


#endif /* __TFTP_PACK_H__ */
