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

/*
 * FunctionName:
 *     tftp_pack_get_tranfer_mode
 * Description:
 *     获取文件传输模式
 * Notes:
 *     
 */
EXTERN VOID tftp_pack_get_tranfer_mode
(
	CHAR * pMode, 
	CHAR * pSaveMode, 
	tftpPackMode_t * mode
)
{
	if (0 == strcasecmp(pMode, __TFTP_MODE_NETASCII_)) {
		*mode = tftp_Pack_Mode_netascii;
		memcpy(pSaveMode, pMode, __TFTP_TRAN_MODE_LEN_);
	}
	else if (0 == strcasecmp(pMode, __TFTP_MODE_OCTET_)) {
		*mode = tftp_Pack_Mode_octet;
		memcpy(pSaveMode, pMode, __TFTP_TRAN_MODE_LEN_);
	}
	else if (0 == strcasecmp(pMode, __TFTP_MODE_MAIL_)) {
		*mode = tftp_Pack_Mode_mail;
		memcpy(pSaveMode, pMode, __TFTP_TRAN_MODE_LEN_);
	}
	else {
		TFTP_LOGWARN("invalid mode:%s, set default:%s", pMode, __TFTP_MODE_OCTET_);
		*mode = tftp_Pack_Mode_octet;
		memcpy(pSaveMode, __TFTP_MODE_OCTET_, __TFTP_TRAN_MODE_LEN_);
	}
	return;
}

EXTERN UINT16 tftp_pack_req
(
	UINT8 * buf,
	tftpPacktReq_t * reqPack
)
{
	UINT8 * p = buf;
	UINT16 len  = 0;
	UINT16 index = 0;
	CHAR fieldBuf[32] = {0};
	CHAR strBuf[__TFTP_REQ_PACK_BUF_LEN_] = {0};
	
	/* 封装opcode */
	((UINT16 *)p)[0] = (reqPack->_opcode == tftp_Pack_OperCode_Rrq ) \
			? htons(__TFTP_OPCODE_RRQ_)
			: htons(__TFTP_OPCODE_WRQ_);

	p += 2;
	
	/* 封装选项（文件名和传输模式） */
	len += tftp_sprint(p + len, "%s%c%s%c", \
			reqPack->_fileName, '\0', reqPack->_pMode, '\0');
	
	/* 封装扩展选项 */
	if (reqPack->_options._opt_tsize) {
		memset(fieldBuf, 0, sizeof(fieldBuf));
		len += tftp_sprint(p + len, "%s%c%s%c", \
				__TFTP_OPTION_TSIZE_, '\0', uitoa(reqPack->_tSize, fieldBuf), '\0');
	}
	if (reqPack->_options._opt_timout) {
		memset(fieldBuf, 0, sizeof(fieldBuf));
		len += tftp_sprint(p + len, "%s%c%s%c", \
				__TFTP_OPTION_TIMEOUT_, '\0', uitoa(reqPack->_timeout, fieldBuf), '\0');
	}
	if (reqPack->_options._opt_tmfreq) {
		memset(fieldBuf, 0, sizeof(fieldBuf));
		len += tftp_sprint(p + len, "%s%c%s%c", \
				__TFTP_OPTION_TMFREQ_, '\0', uitoa(reqPack->_tmfreq, fieldBuf), '\0');
	}	
	if (reqPack->_options._opt_blksize) {
		memset(fieldBuf, 0, sizeof(fieldBuf));
		len += tftp_sprint(p + len, "%s%c%s%c", \
				__TFTP_OPTION_BIKSIZE_, '\0', uitoa(reqPack->_blkSize, fieldBuf), '\0');
	}	
	if (reqPack->_options._opt_bpid) {
		memset(fieldBuf, 0, sizeof(fieldBuf));
		len += tftp_sprint(p + len, "%s%c%s%c", \
				__TFTP_OPTION_BPID_, '\0', uitoa(reqPack->_bpId, fieldBuf), '\0');
	}
	
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

EXTERN tftpReturnValue_t tftp_unpack_req
(
	UINT8 * buf, 
	INT32 bufLen,	
	tftpPacktReq_t * reqPack
)
{
	CHAR reqBuf[__TFTP_REQ_PACK_BUF_LEN_] = {0};
	INT32 strLen = 0;
	INT32 strVlaueLen = 0;
	INT32 index = 0;
	CHAR * subStr = NULL;
	CHAR * subStrValue = NULL;
	CHAR * savePtr = reqBuf;

	memcpy(reqBuf, buf, __TFTP_REQ_PACK_BUF_LEN_);

	/* 取opcode */
	reqPack->_opcode = ntohs(((UINT16 *)savePtr)[0]);
	index += 2;
	savePtr += 2;

	/* 获取文件名 */
	subStr = strtok_r(NULL, "\0", &savePtr);
	strLen = strlen(subStr) + 1;
	strncpy(reqPack->_fileName, subStr, __TFTP_FILENAME_STR_LEN_);
	index += strLen;

	/* 获取传输mode，跳过'\0'符号 */
	savePtr++;
	subStr = strtok_r(NULL, "\0", &savePtr);
	strLen = strlen(subStr) + 1;
	strncpy(reqPack->_pMode, subStr, __TFTP_TRAN_MODE_LEN_);
	index += strLen;

	/* 获取其他扩展选项 */
	while (index < bufLen) {
		/* 获取选项，跳过'\0'符号 */
		savePtr++;
		subStr = strtok_r(NULL, "\0", &savePtr);
		strLen = strlen(subStr) + 1;

		/* 获取选项值，跳过'\0'符号 */
		savePtr++;
		subStrValue = strtok_r(NULL, "\0", &savePtr);
		strVlaueLen = strlen(subStrValue) + 1;
		
		/* 选项解析，选项值赋值 */
		if (0 == strcasecmp(subStr, __TFTP_OPTION_TSIZE_)) {
			reqPack->_tSize = atoui(subStrValue);
			reqPack->_options._opt_tsize = 1;
		}
		else if (0 == strcasecmp(subStr, __TFTP_OPTION_TIMEOUT_)) {
			reqPack->_timeout = (UINT16)atoui(subStrValue);
			reqPack->_options._opt_timout = 1;
		}
		else if (0 == strcasecmp(subStr, __TFTP_OPTION_TMFREQ_)) {
			reqPack->_tmfreq =(UINT16) atoui(subStrValue);
			reqPack->_options._opt_tmfreq = 1;
		}
		else if (0 == strcasecmp(subStr, __TFTP_OPTION_BIKSIZE_)) {
			reqPack->_blkSize = (UINT16)atoui(subStrValue);
			reqPack->_options._opt_blksize = 1;
		}
		else if (0 == strcasecmp(subStr, __TFTP_OPTION_BPID_)) {
			reqPack->_bpId = (UINT16)atoui(subStrValue);
			reqPack->_options._opt_bpid = 1;
		}

		index += (strLen + strVlaueLen);
	}
	
#if 0
	for (index = 0; index < bufLen; index++) {
		if (index % 8 == 0) {
			tftp_print("\r\n");
		}
		tftp_print("0x%02x ", reqBuf[index]);
	}
#endif

	return tftp_ret_Ok;
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

