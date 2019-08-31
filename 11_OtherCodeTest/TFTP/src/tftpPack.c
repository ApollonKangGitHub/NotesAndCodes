#include <tftpType.h>
#include <tftpPack.h>
#include <tftpLog.h>

#include <tftpPublic.h>

EXTERN tftpPackOperCode_t tftp_pack_oper_para_get(CONST CHAR * operator)
{
	if (NULL == operator) {
		return tftp_Pack_OperCode_Max;
	}
	if ((0 == strcmp(operator, "get")) 
		|| (0 == strcmp(operator, "download"))) {
		return tftp_Pack_OperCode_Rrq;
	} 
	else if ((0 == strcmp(operator, "put")) 
		|| (0 == strcmp(operator, "upload"))) {
		return tftp_Pack_OperCode_Wrq;
	}
	else {
		return tftp_Pack_OperCode_Max;
	}
}

EXTERN UINT16 tftp_pack_req
(
	UINT8 * buf, 
	tftpPackOperCode_t opcode,
	CONST CHAR * filename,
	CONST CHAR * mode,
	UINT32 fileSize,
	UINT32 timeout,
	UINT32 blksize,
	UINT16 bpid,	/* 自定义扩展选项 */
	...				
)
{
	UINT8 * p = buf;
	UINT16 len  = 0;
	UINT16 index = 0;
	CHAR strBuf[1024] = {0};
	
	/* 封装opcode */
	((UINT16 *)p)[0] = (opcode == tftp_Pack_OperCode_Rrq ) \
			? __TFTP_OPCODE_RRQ_ 
			: __TFTP_OPCODE_WRQ_;

	p += 2;
	
	/* 封装选项和扩展选项 */
	len = tftp_sprint(p, "%s%c%s%c"  "%s%c%d%c"  "%s%c%d%c"  "%s%c%d%c"  "%s%c%d%c", \
			filename, 				'\0', mode, 			'\0', \
			__TFTP_OPTION_TSIZE_, 	'\0', htons(fileSize), 	'\0', \
			__TFTP_OPTION_TIMEOUT_, '\0', htons(timeout), 	'\0', \
			__TFTP_OPTION_BIKSIZE_, '\0', htons(blksize), 	'\0', \
			__TFTP_OPTION_BPID_, 	'\0', htons(bpid), 		'\0');
	
	if (len < 0) {
		TFTP_LOGERR("packet error,return:%d", len);
		return -1;
	}

	len += 2;
#if 1	
	TFTP_LOGNOR("packet request success,return:%d", len);
	
	while(index < len) {
		tftp_sprint(strBuf + index, "%c", (UINT8)buf[index] > 0x20 ? (UINT8)buf[index] : '-');
		index++;
	}
	TFTP_LOGDBG(tftp_dbgSwitch_pack, "%s", strBuf);
#endif

	return len;
}

EXTERN UINT16 tftp_pack_ack(UINT8 * buf, UINT16 id)
{

}

EXTERN UINT16 tftp_pack_oack(UINT8 * buf, UINT16 id)
{

}

EXTERN UINT16 tftp_pack_data(UINT8 * buf, UINT16 id)
{

}

EXTERN UINT16 tftp_pack_error(UINT8 * buf)
{

}

