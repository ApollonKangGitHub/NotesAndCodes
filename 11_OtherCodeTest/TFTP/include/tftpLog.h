#ifndef __TFTP_LOG_H__
#define __TFTP_LOG_H__

#include <tftpType.h>
#include <stdarg.h>

/* Log级别 */
typedef enum tftpLogLevel_e
{
	tftp_logLevel_Normal = 0,
	tftp_logLevel_Debug,	
	tftp_logLevel_Note,
	tftp_logLevel_Warning,
	tftp_logLevel_Error,
	tftp_logLevel_Max		/* last, Please */
}tftpLogLevel_t;

/* Log输出位置 */
typedef enum tftpRecordPos_e
{
	tftp_recordPos_toLogFile = 0,
	tftp_recordPos_toShell,
	tftp_recordPos_toAll,
	tftp_recordPos_Max		/* last, Please */
}tftpRecordFlag_t;

/* debug开关类型 */
typedef enum tftpDbgSwitch_e
{
	tftp_dbgSwitch_task = 0,
	tftp_dbgSwitch_Server,
	tftp_dbgSwitch_Client,
	tftp_dbgSwitch_Shell,
	tftp_dbgSwitch_send,
	tftp_dbgSwitch_recv,
	tftp_dbgSwitch_Other,
	tftp_dbgSwitch_max		/* last, Please */
}tftpDbgSwitch_t;
	
/* debug开关 */
typedef enum tftpDebugControl_e
{
	tftp_debugControl_off = 0,
	tftp_debugControl_on,
	tftp_debugControl_max
}tftpDebugControl_t;	
	
/******************************************************************************
 * printf()的颜色格式:\033[{attr1};{attr2};...{attrn}m
 * 以\033即Esc的ASCII开始，跟随n个属性，以m结尾
 * eg:\033[32;41m
 * attr属性取值：
 * 0：重置所有属性；1：高亮/加粗；2：暗淡；4：下滑线；5：闪烁；6：反转；8：隐藏
 * 30～37为前景色，40～47为背景色，依次是：
 * 黑	红 绿 黄 蓝 紫 青 白
 * 30	31	32	33	34	35	36	37
 * 40	41	42	43	44	45	46	47
 * ****************************************************************************/
#define __COLOR_NORMAL_			"\033[0m"

#define __COLOR_RED_			"\033[1;31m"
#define __COLOR_GREEN_			"\033[1;32m"
#define __COLOR_YELLOW_			"\033[1;33m"
#define __COLOR_BLUE_			"\033[1;34m"
#define __COLOR_PURPLE_			"\033[1;35m"
#define __COLOR_INDIGO_			"\033[1;36m"

/* Log信息前缀 */
#define __TFTP_LOG_DBG_			"%%%% TFTP-DEBUG :"
#define __TFTP_LOG_NOTE_		"%%%% TFTP-NOTE  :"
#define __TFTP_LOG_WARN_		"%%%% TFTP-WARN  :"
#define __TFTP_LOG_ERR_			"%%%% TFTP-ERROR :"
#define __TFTP_LOG_NOR_			"%%%% TFTP-NORMAL:"

#define __TFTP_LOF_FILE_PATH_ 	"./logFile/tftp.log"

/* 标准文件定义 */
#define __TFTP_STDIN_ 			(stdin)
#define __TFTP_STDOUT_ 			(stdout)
#define __TFTP_STDERR_ 			(stderr)

/* print信息格式化字符串最大长度 */
#define __TFTP_FORMAT_BUF_MAX_ 	(1024)

/* 参数格式化，函数调用 */
#define __TFTP_LOGLEVEL_PRINT(col, lev, rec, fmt, ...) \
	do{ \
		tftp_log_level_print(col, rec, lev""fmt, ##__VA_ARGS__); \
	}while(0)

/* Log打印宏函数级别区分与参数指定 */
#define _TFTP_LOGLEVEL(level, recordFlag, format, ...) \
	do{ \
		switch(level){ \
			case tftp_logLevel_Debug: \
				__TFTP_LOGLEVEL_PRINT(__COLOR_INDIGO_, __TFTP_LOG_DBG_, \
					recordFlag, format, ##__VA_ARGS__); \
					break; \
			case tftp_logLevel_Note: \
				__TFTP_LOGLEVEL_PRINT(__COLOR_GREEN_, __TFTP_LOG_NOTE_, \
					recordFlag, format, ##__VA_ARGS__); \
				break; \
			case tftp_logLevel_Warning: \
				__TFTP_LOGLEVEL_PRINT(__COLOR_YELLOW_, __TFTP_LOG_WARN_, \
					recordFlag, format, ##__VA_ARGS__); \
				break; \
			case tftp_logLevel_Error: \
				__TFTP_LOGLEVEL_PRINT(__COLOR_RED_, __TFTP_LOG_ERR_, \
					recordFlag, format, ##__VA_ARGS__); \
				break; \
			case tftp_logLevel_Normal: \
			case tftp_logLevel_Max: \
			default: \
				__TFTP_LOGLEVEL_PRINT(__COLOR_NORMAL_, __TFTP_LOG_NOR_, \
					recordFlag, format, ##__VA_ARGS__); \
				break; \
		} \
	}while(0)

/* 打印Normal信息，直接调用该宏 */	
#define TFTP_LOGNOR(format, ...) \
	do{\
		_TFTP_LOGLEVEL(tftp_logLevel_Normal, \
			tftp_recordPos_toShell, format, ##__VA_ARGS__); \
	}while(0)

/* 打印Debug信息，直接调用该宏 */	
#define TFTP_LOGDBG(switch, format, ...) \
	do{\
		if(_TEST_TRUE(gDbgSwitchFlg, switch)){\
			_TFTP_LOGLEVEL(tftp_logLevel_Debug, \
				tftp_recordPos_toShell, format, ##__VA_ARGS__); \
		}\
	}while(0)
/* 打印Notes信息，直接调用该宏 */			
#define TFTP_LOGNOTE(format, ...) \
	do{\
		_TFTP_LOGLEVEL(tftp_logLevel_Note, \
			tftp_recordPos_toAll, format, ##__VA_ARGS__); \
	}while(0)
/* 打印Warning信息，直接调用该宏 */			
#define TFTP_LOGWARN(format, ...) \
	do{\
		_TFTP_LOGLEVEL(tftp_logLevel_Warning, \
			tftp_recordPos_toAll, format, ##__VA_ARGS__); \
	}while(0)
/* 打印Error信息，直接调用该宏 */				
#define TFTP_LOGERR(format, ...) \
	do{\
		_TFTP_LOGLEVEL(tftp_logLevel_Error, \
			tftp_recordPos_toAll, format, ##__VA_ARGS__); \
	}while(0)

#define TFTP_DBG_SWITCH_NUMBER_MAX (tftp_dbgSwitch_max / 8) 
EXTERN UINT8 gDbgSwitchFlg[TFTP_DBG_SWITCH_NUMBER_MAX];

EXTERN INT32 tftp_log_level_print
(
	IN CHAR * colorStr,
	IN tftpRecordFlag_t recordFlag,
	IN CHAR * format,
	IN ...
);

EXTERN INT32 tftp_log_init(VOID);
EXTERN VOID tftp_log_debug_control
(
	tftpDbgSwitch_t dbgSw,
	tftpDebugControl_t openFlg
);

#endif /* TFTP_LOG_H__ */
