#ifndef __TFTP_PACK_H__
#define __TFTP_PACK_H__

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
