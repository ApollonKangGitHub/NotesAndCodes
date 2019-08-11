#ifndef __TFTP_SERVER_H__
#define __TFTP_SERVER_H__

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

#endif /* __TFTP_SERVER_H__ */
