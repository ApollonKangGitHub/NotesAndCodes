#include <tftpLog.h>
#include <tftpType.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>

UINT8 gDbgSwitchFlg[TFTP_DBG_SWITCH_NUMBER_MAX];

LOCAL FILE * gLogFile = NULL;
LOCAL FILE * gLogShell = (FILE *)(NULL);

#define TFTP_LOGLEVEL_PRINT_TO_FILE(file, flag, fmt) \
do { \
	va_list arg;\
	INT32 ret = tftp_ret_Ok; \
	va_start (arg, format);\
	if (flag) { \
    	ret |= tftp_vfprint (file, format, arg);\
		if (ret < 0) { \
			tftp_print ("\r\nTFTP-LOG:log to %s return is error(%d)", \
				(file == gLogFile) ? "logFile" : "shell", ret); \
			return tftp_ret_Error; \
		} \
	} \
	va_end (arg);\
}while(0)

INT32 tftp_log_level_print
(
	IN tftpRecordFlag_t recordFlag,
	IN CHAR * format,
	IN ...
)
{
	INT32 ret;
	BOOL fileFlg = FALSE;
	BOOL shellFlg = FALSE;
	va_list pAargv;
	INT32 val1, val2, val3, val4;
	
	switch (recordFlag) {
		case tftp_recordPos_toLogFile:
			fileFlg = TRUE;
			break;
		case tftp_recordPos_toShell:
			shellFlg = TRUE;
			break;
		case tftp_recordPos_toAll:
			fileFlg = TRUE;
			shellFlg = TRUE;
			break;
		default:
			break;
	}

	TFTP_LOGLEVEL_PRINT_TO_FILE(gLogFile, fileFlg, format);
	TFTP_LOGLEVEL_PRINT_TO_FILE(gLogShell, shellFlg, format);
	
   	return tftp_ret_Ok;
}

LOCAL INT32 tftp_log_to_file_init(FILE ** fp, CONST CHAR * path)
{
	if((NULL == fp) || (NULL == path)){
		tftp_print("\r\nError pointer for fp[%p], path:[%p]!", fp, path);
		exit(EXIT_FAILURE);
	}
	
	*fp = fopen(path, "ab+");
	if(NULL == *fp)
	{
		tftp_print("\r\nError to open file:%s!", path);
		exit(EXIT_FAILURE);
	}
	
	return tftp_ret_Ok;
}

LOCAL INT32 tftp_log_debug_switch_init(VOID)
{
	INT32 i = 0;
	for(;i < TFTP_DBG_SWITCH_NUMBER_MAX; i++){
		gDbgSwitchFlg[i] &= 0;
	}
}

EXTERN INT32 tftp_log_init(VOID)
{
	/* 初始化Shell文件描述符 */
	gLogShell = __TFTP_STDOUT_;

	/* 初始化日志文件描述符 */
	tftp_log_to_file_init(&gLogFile, __TFTP_LOF_FILE_PATH_);
	
	/* 初始化debug打印开关 */
	tftp_log_debug_switch_init();
}
