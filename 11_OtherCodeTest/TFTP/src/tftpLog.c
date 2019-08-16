#include <tftpLog.h>
#include <tftpType.h>

#include <tftpPublic.h>

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

LOCAL FILE * gLogFile[tftp_logLevel_Max] = {NULL};
LOCAL CHAR * gLogFilePath[tftp_logLevel_Max] = {
	"/dev/stdin",
	"./logFile/tftpNormal.log",
	"./logFile/tftpDebug.log",
	"./logFile/tftpNote.log",
	"./logFile/tftpWarn.log",
	"./logFile/tftpError.log",
};
	
LOCAL INT32 tftp_log_level_print_format
(
	FILE * file, 
	CONST CHAR * filePath, 
	CONST CHAR * format, 
	va_list argv
) 
{
	INT32 ret = tftp_ret_Ok; 

	ret |= tftp_vfprint (file, format, argv);
	if (ret < 0) { 
		tftp_print ("\r\nTFTP-LOG:log to %s return is error(%d)", filePath, ret); 
		return tftp_ret_Error; 
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
	IN tftpLogAbil ability,
	IN CHAR * format,
	IN ...
)
{
	INT32 ret;
	tftpLogLevel_t level = tftp_logLevel_Shell;
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

	for (level = tftp_logLevel_Shell; level < tftp_logLevel_Max; level++) {
		if (_TEST_TRUE(&ability, level)) {
			if (gLogFile[level]) {
				/* 打印到对应文件 */
				va_start (argList, format);
				(VOID)tftp_log_level_print_format(gLogFile[level],\
							gLogFilePath[level], pFormatAll, argList);
				va_end (argList);
			}
			else {
				tftp_print("\r\nlog file %s is not open or not exist, file pointer=%p!", 
					gLogFilePath[level], gLogFile[level]);
			}
		}
	}
	
   	return tftp_ret_Ok;
}

LOCAL INT32 tftp_log_to_file_init()
{
	INT32 i = 0;
	FILE * fp = NULL;

	gLogFile[tftp_logLevel_Shell] = __TFTP_STDOUT_;
	for (i = tftp_logLevel_Normal; i < tftp_logLevel_Max; i++) {
		fp = fopen(gLogFilePath[i], "ab+");
		if (NULL == fp) {
			tftp_print("\r\nError to open file:%s!", gLogFilePath[i]);
			exit(EXIT_FAILURE);
		}

		gLogFile[i] = fp;
	}

	return tftp_ret_Ok;
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

LOCAL INT32 tftp_log_debug_switch_init(VOID)
{
	__SET_BIT(gDbgSwitchFlg, tftp_dbgSwitch_task, FALSE);
	__SET_BIT(gDbgSwitchFlg, tftp_dbgSwitch_server, FALSE);
	__SET_BIT(gDbgSwitchFlg, tftp_dbgSwitch_client, FALSE);
	__SET_BIT(gDbgSwitchFlg, tftp_dbgSwitch_shell, FALSE);
	__SET_BIT(gDbgSwitchFlg, tftp_dbgSwitch_sem, FALSE);
	__SET_BIT(gDbgSwitchFlg, tftp_dbgSwitch_send, FALSE);
	__SET_BIT(gDbgSwitchFlg, tftp_dbgSwitch_recv, FALSE);
	__SET_BIT(gDbgSwitchFlg, tftp_dbgSwitch_other, FALSE);
}

EXTERN INT32 tftp_log_module_init(VOID)
{
	/* 初始化日志文件描述符 */
	tftp_log_to_file_init();
	
	/* 初始化debug打印开关 */
	tftp_log_debug_switch_init();
}


