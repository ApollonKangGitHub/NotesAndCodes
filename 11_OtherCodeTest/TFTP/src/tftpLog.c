#include <tftpLog.h>
#include <tftpType.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <time.h>

UINT8 gDbgSwitchFlg[TFTP_DBG_SWITCH_NUMBER_MAX];

/* tm_wday, Day of the week (0-6, Sunday = 0) */
LOCAL CHAR * gWeekStr[] = {
	"Sunday",
	"Monday",
	"Tuesday",
	"Wednesday",
	"Thursday",
	"Friday",
	"Saturday"
};
	
LOCAL FILE * gLogFile = NULL;
LOCAL FILE * gLogShell = (FILE *)(NULL);

LOCAL INT32 tftp_log_level_print_format
(
	FILE * file, 
	BOOL flag, 
	CONST CHAR * format, 
	va_list argv
) 
{
	INT32 ret = tftp_ret_Ok; 

	if (flag) { 
    	ret |= tftp_vfprint (file, format, argv);
		if (ret < 0) { 
			tftp_print ("\r\nTFTP-LOG:log to %s return is error(%d)", 
				(file == gLogFile) ? "logFile" : "shell", ret); 
			return tftp_ret_Error; 
		} 
	} 

	return ret;
}

LOCAL CHAR * tftp_log_time_get(CHAR * date)
{
    time_t timeStamp;
    struct tm tmStruct;
	
    (VOID)time (&timeStamp);					/* 获取时间戳 */
    (VOID)localtime_r (&timeStamp, &tmStruct);	/* 时间戳转换为时间结构 */

	/* 1970-01-01 00:00:00 +0000 (UTC). */
	tftp_sprint(date, "%04d-%02d-%02d %02d:%02d:%02d(UTC)[%s]",
		tmStruct.tm_year + 1970, 
		tmStruct.tm_mon + 1, 
		tmStruct.tm_mday,
		tmStruct.tm_hour,
		tmStruct.tm_min,
		tmStruct.tm_sec,		
		gWeekStr[tmStruct.tm_wday]);

	return date;
}

EXTERN INT32 tftp_log_level_print
(
	IN CHAR * colorStr,
	IN tftpRecordFlag_t recordFlag,
	IN CHAR * format,
	IN ...
)
{
	INT32 ret;
	BOOL fileFlg = FALSE;
	BOOL shellFlg = FALSE;
	va_list argList;

	CHAR * pStart = colorStr;
	CHAR * pFormat = format;
	CHAR * pEnd = __COLOR_NORMAL_;
	CHAR pDateTime[64] = {0};
	CHAR pFormatAll[__TFTP_FORMAT_BUF_MAX_] = {'\r', '\n', '\0'};

	/* 获取当前时间 */
	(VOID)tftp_log_time_get(pDateTime);

	/* 格式化 */
	(VOID)strncat(pFormatAll, pStart, strlen(pStart));			/* 格式化输出颜色指定 */
	(VOID)strncat(pFormatAll, pDateTime, strlen(pDateTime));	/* 格式化输出日期时间获取 */
	(VOID)strncat(pFormatAll, pFormat, strlen(pFormat));		/* 格式化输出level + 原始format */
	(VOID)strncat(pFormatAll, pEnd, strlen(pEnd));				/* 格式化输出颜色reset */
	
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

	/* 打印到文件 */
	va_start (argList, format);
	(VOID)tftp_log_level_print_format(gLogFile, fileFlg, pFormatAll, argList);
	va_end (argList);

	/* 打印到shell */
	va_start (argList, format);
	(VOID)tftp_log_level_print_format(gLogShell, shellFlg, pFormatAll, argList);
	va_end (argList);
	
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

EXTERN VOID tftp_log_debug_control
(
	tftpDbgSwitch_t dbgSw,
	BOOL openFlg
)
{
	__SET_BIT(gDbgSwitchFlg, dbgSw, openFlg);

	return;
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


