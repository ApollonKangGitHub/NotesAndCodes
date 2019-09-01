#include <tftpType.h>
#include <tftpPack.h>
#include <tftpLog.h>

#include <tftpPublic.h>

EXTERN tftpPackOperCode_t tftp_pack_oper_para_get(CONST CHAR * operator)
{
	tftpPackOperCode_t opcode = tftp_Pack_OperCode_Max;

	if (NULL == operator) {
		opcode = tftp_Pack_OperCode_Max;
	}
	else if ((0 == strcasecmp(operator, "get")) 
		|| (0 == strcasecmp(operator, "download"))) {
		opcode = tftp_Pack_OperCode_Rrq;
	} 
	else if ((0 == strcasecmp(operator, "put")) 
		|| (0 == strcasecmp(operator, "upload"))) {
		opcode = tftp_Pack_OperCode_Wrq;
	}
	else {
		opcode = tftp_Pack_OperCode_Max;
	}

	return opcode;
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
	CHAR fieldBuf[32] = {0};
	CHAR strBuf[__TFTP_REQ_PACK_BUF_LEN_] = {0};
	
	/* 封装opcode */
	((UINT16 *)p)[0] = (opcode == tftp_Pack_OperCode_Rrq ) \
			? __TFTP_OPCODE_RRQ_ 
			: __TFTP_OPCODE_WRQ_;

	p += 2;
	
	/* 封装选项和扩展选项 */
	len += tftp_sprint(p + len, "%s%c%s%c",  filename, '\0', mode, '\0');
	memset(fieldBuf, 0, sizeof(fieldBuf));
	len += tftp_sprint(p + len, "%s%c%s%c", __TFTP_OPTION_TSIZE_, '\0', uitoa(fileSize, fieldBuf), '\0');
	memset(fieldBuf, 0, sizeof(fieldBuf));
	len += tftp_sprint(p + len, "%s%c%s%c", __TFTP_OPTION_TIMEOUT_, '\0', uitoa(timeout, fieldBuf), '\0');
	memset(fieldBuf, 0, sizeof(fieldBuf));
	len += tftp_sprint(p + len, "%s%c%s%c", __TFTP_OPTION_BIKSIZE_, '\0', uitoa(blksize, fieldBuf), '\0');
	memset(fieldBuf, 0, sizeof(fieldBuf));
	len += tftp_sprint(p + len, "%s%c%s%c", __TFTP_OPTION_BPID_, '\0', uitoa(bpid, fieldBuf), '\0');
	
	if (len < 0) {
		TFTP_LOGERR("packet error,return:%d", len);
		return -1;
	}

	len += 2;
#if 0	
	TFTP_LOGNOR("packet request success,return:%d", len);
	
	while(index < len) {
		tftp_sprint(strBuf + index, "%c", (UINT8)buf[index] > 0x20 ? (UINT8)buf[index] : '-');
		index++;
	}
	tftp_print("\r\nsend:%s", strBuf);
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

