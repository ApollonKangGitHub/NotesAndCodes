#include <tftpLog.h>
#include <tftpType.h>
#include <tftpShell.h>
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

/* 日志文件描述符以及对应的文件路径 */
LOCAL FILE * gLogFile[tftp_logLevel_Max] = {NULL};
LOCAL CHAR * gLogFilePath[tftp_logLevel_Max] = {
	"/dev/stdin",
	"./logFile/tftpNormal.log",
	"./logFile/tftpDebug.log",
	"./logFile/tftpNote.log",
	"./logFile/tftpWarn.log",
	"./logFile/tftpError.log"
};

/* debug开关字符串 */
LOCAL CHAR * gSwitchStr[tftp_dbgSwitch_max] = {
	"task",
	"server",
	"client",
	"shell",
	"sem",
	"send",
	"recv",
	"pack",
	"other"
};

/*
 * FunctionName:
 *     tftp_log_level_print_format
 * Description:
 *     日志打印时，传入具体的文件描述符格和format格式，进行写文件操作
 * Notes:
 *     
 */
LOCAL INT32 tftp_log_level_print_format
(
	IN FILE * file, 
	IN CONST CHAR * filePath, 
	IN CONST CHAR * format, 
	IN va_list argv
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

/*
 * FunctionName:
 *     tftp_log_time_get
 * Description:
 *     获取打印某条日志时的时间并转换为传出字符串
 * Notes:
 *     
 */
LOCAL CHAR * tftp_log_time_get(OUT CHAR * date)
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

/*
 * FunctionName:
 *     tftp_log_level_print
 * Description:
 *     日志打印格式化函数，包括打印级别确定到目标文件确定
 * Notes:
 *     
 */
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
				/* 刷新到文件中去 */
				tftp_fflush(gLogFile[level]);
			}
			else {
				tftp_print("\r\nlog file %s is not open or not exist, file pointer=%p!", 
					gLogFilePath[level], gLogFile[level]);
			}
		}
	}
	
   	return tftp_ret_Ok;
}

/*
 * FunctionName:
 *     tftp_log_to_file_init
 * Description:
 *     初始化时，由模块初始化流程调用，打开所有模块日志文件
 * Notes:
 *     shell输出，直接使用已经打开的stdout无需再次open
 */
LOCAL INT32 tftp_log_to_file_init(VOID)
{
	INT32 i = 0;
	FILE * fp = NULL;

	gLogFile[tftp_logLevel_Shell] = __TFTP_STDOUT_;
	for (i = tftp_logLevel_Normal; i < tftp_logLevel_Max; i++) {
		fp = fopen(gLogFilePath[i], "ab+");
		if (NULL == fp) {
			tftp_print("\r\nError to open file:%s!", gLogFilePath[i]);
			tftp_perror("open fail reason is");
			exit(EXIT_FAILURE);
		}

		gLogFile[i] = fp;
	}

	return tftp_ret_Ok;
}

/*
 * FunctionName:
 *     tftp_log_debug_control
 * Description:
 *     tftp日志模块对外提供debug开关控制接口，TRUE为打开相应
 *     debug开关，FALSE为关闭相应dbgSw开关
 * Notes:
 *     
 */
EXTERN VOID tftp_log_debug_control
(
	IN tftpDbgSwitch_t dbgSw,
	IN BOOL openFlg
)
{
	__SET_BIT(gDbgSwitchFlg, dbgSw, openFlg);
	return;
}

/*
 * FunctionName:
 *     tftp_log_debug_switch_init
 * Description:
 *     tftp日志模块debug开关初始化设置，默认全部关闭
 * Notes:
 *     
 */
LOCAL INT32 tftp_log_debug_switch_init(VOID)
{
	__SET_BIT(gDbgSwitchFlg, tftp_dbgSwitch_task, FALSE);
	__SET_BIT(gDbgSwitchFlg, tftp_dbgSwitch_server, FALSE);
	__SET_BIT(gDbgSwitchFlg, tftp_dbgSwitch_client, FALSE);
	__SET_BIT(gDbgSwitchFlg, tftp_dbgSwitch_shell, FALSE);
	__SET_BIT(gDbgSwitchFlg, tftp_dbgSwitch_sem, FALSE);
	__SET_BIT(gDbgSwitchFlg, tftp_dbgSwitch_send, FALSE);
	__SET_BIT(gDbgSwitchFlg, tftp_dbgSwitch_recv, FALSE);
	__SET_BIT(gDbgSwitchFlg, tftp_dbgSwitch_pack, FALSE);
	__SET_BIT(gDbgSwitchFlg, tftp_dbgSwitch_other, FALSE);
}

LOCAL VOID tftp_log_cmd_debug_switch(INT32 argc, CHAR * argv[])
{
	BOOL open = FALSE;
	tftpDbgSwitch_t sw = tftp_dbgSwitch_max;

	sw = (tftpDbgSwitch_t)(atoui(argv[2]));

	if (sw >= tftp_dbgSwitch_max) {
		tftp_print("\r\ninvalid operator parmeter:switch(%d),operator(%s)", sw, argv[3]);
		return;
	}

	if (0 == strcasecmp(argv[3], "open")) {
		open = TRUE;
	}
	else if (0 == strcasecmp(argv[3], "close")) {
		open = FALSE;
	}
	else {
		tftp_print("\r\ninvalid operator parmeter:switch(%s),operator(%s)", \
			gSwitchStr[sw], argv[3]);
		return;
	}
	
	tftp_log_debug_control(sw, open);
	tftp_print("\r\n%s debug switch %s", gSwitchStr[sw], argv[3]);
}

LOCAL VOID tftp_log_command_init(VOID)
{	
	tftp_shell_cmd_register((tftp_cmd_deal_fun)tftp_log_cmd_debug_switch, 
	__TFTP_CMD_NORMAL_ | __TFTP_CMD_DYN_,
		"tftplog{tftp log}"
			"debug{debug switch open or close}"
				"__UINT32__{switch choose[eg:"
					"\n\t\t\t\t\t->(0)task"
					"\n\t\t\t\t\t->(1)server"
					"\n\t\t\t\t\t->(2)client"
					"\n\t\t\t\t\t->(3)shell"
					"\n\t\t\t\t\t->(4)sem"
					"\n\t\t\t\t\t->(5)send"
					"\n\t\t\t\t\t->(6)recv"
					"\n\t\t\t\t\t->(7)pack"
					"\n\t\t\t\t\t->(8)other]}"
					"__STRING__{open/close}");
}

/*
 * FunctionName:
 *     tftp_log_module_init
 * Description:
 *     tftp日志模块初始化函数，由主线程初始化时统一调用
 * Notes:
 *     
 */
EXTERN INT32 tftp_log_module_init(VOID)
{
	/* 初始化日志文件描述符 */
	tftp_log_to_file_init();
	
	/* 初始化debug打印开关 */
	tftp_log_debug_switch_init();

	/* 注册log debug开关的命令 */
	tftp_log_command_init();
}


