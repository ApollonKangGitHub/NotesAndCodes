/*
 * FileName:OvertimeTable.h
 * Author:Kangruojin
 * Time:2019年5月19日14:16:37
 * Version:1.0
 * Description:基于文件の格式化信息计算加班时长
 */

#ifndef _OVER_TIME_TABLE_CALC_H_
#define _OVER_TIME_TABLE_CALC_H_

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>


#define FALSE 	(0)
#define TRUE 	(1)
#define ERROR 	(-1)
#define OK 		(0)
#define IN
#define OUT

#define BOOL 	int
#define UINT32 	unsigned int
#define UINT16 	unsigned short
#define UINT8 	unsigned char
#define CHAR 	char
#define INT32 	int
#define DOUBLE 	double
#define VOID 	void
#define STATIC 	static
#define CONST const


#define OVER_TIME_TABLE_BUFFER 	1024
#define DAY_INFO_BUFFER 		32

#define ONE_DAY_BEGIN_TIME				(0)
#define MORNING_BEGIN_TIME				(8*60+30)
#define MORNING_REBOUND_TIME_15_MIN		(15)
#define MORNING_REBOUND_TIME_30_MIN		(30)
#define MORNING_REBOUND_TIME_15			(MORNING_BEGIN_TIME + MORNING_REBOUND_TIME_15_MIN)
#define MORNING_REBOUND_TIME_30			(MORNING_BEGIN_TIME + MORNING_REBOUND_TIME_30_MIN)
#define MORNING_REBOUND_TIME			(9*60)		/* 考勤可弹回 */
#define NOON_SLEEP_BEGIN_TIME			(12*60)
#define NOON_SLEEP_END_TIME				(13*60+30)	
#define AFTERNOON_SLEEP_BEGIN_TIME		(18*60)
#define FATERNOON_SLEEP_END_TIME		(18*60+45)	
#define FATERNOON_SLEEP_END_TIME_15		(FATERNOON_SLEEP_END_TIME + MORNING_REBOUND_TIME_15_MIN)
#define FATERNOON_SLEEP_END_TIME_30		(FATERNOON_SLEEP_END_TIME + MORNING_REBOUND_TIME_30_MIN)
#define OVERTIME_EFFECT_BEGIN_TIME		(20*60+30)

#define SLEEP_TIME_NOON			(NOON_SLEEP_END_TIME - NOON_SLEEP_BEGIN_TIME)
#define SLEEP_TIME_AFTERNOON	(FATERNOON_SLEEP_END_TIME - AFTERNOON_SLEEP_BEGIN_TIME)
#define SLEEP_TIME_TWICE		(SLEEP_TIME_NOON + SLEEP_TIME_AFTERNOON)
#define NORMAL_WORKING_MINUTES	(AFTERNOON_SLEEP_BEGIN_TIME - MORNING_BEGIN_TIME - SLEEP_TIME_NOON)

typedef enum week{
	weekError = 0,
	weekMonday = 1,
	weekTuesday,	
	weekWednesday,
	weekThursday,
	weekFriday,
	weekSaturday,
	weekSunday,
	weekInvalid /* last please */
}WEEK;

typedef struct day_time_info{
	UINT32 dayIndex;			/* 该天是该月第几天（从1开始） */
	UINT32 sleepTime;			/* 非加班/上班时间（茶歇午休等） */
	UINT32 startTimeStamp;		/* 上班时间时间戳(基于00:00:00) */
	UINT32 endTimeStamp;		/* 下班时间时间戳(基于00:00:00) */
	UINT32 minutes;				/* 该天加班分钟数 */
	DOUBLE hours;				/* 该天小时数 */
	UINT32 reboundTime;			/* 弹回时长 */
	BOOL leaveFlag;				/* 迟到不可弹回时的请假（调休）标志 */
	BOOL holidayFlag;			/* 该天是假日标志 */
	BOOL adjustFlag;			/* 该天是非周内，但是属于节假日调休加班即正常上班 */
	BOOL exceptionFlag;			/* 异常标志 */
	WEEK week;					/* 该天是周几 */
}DAYINFO;

#define ONE_MONTH_MAX_DAYS 31
typedef struct over_time_ifo{
	UINT32 overtimeDay;		/* 加班天数 */
	UINT32 totalMinutes;	/* 总加班时长（分钟） */
	DOUBLE totalHours;		/* 总加班时长（小时） */
	DAYINFO day[ONE_MONTH_MAX_DAYS];
}OVERTIEINFO;

#define DAYINFO_ASSIGNMENT_FROM_BUFFER(pstr, info, delim, save, dst, oper, multiple){\
		CHAR * ptr = NULL;\
		pstr = strtok_r(info, delim, save);\
		if(pstr){\
			dst oper multiple*atoi(pstr);\
			if(gInfoDbgFlag){\
				ptr = get_str_elements(#dst, '>');\
				printf("%s:%d ", ptr, atoi(pstr));\
			}\
		}\
	}

#define FUN_DBG_END_STR		"END\n"
#define FUN_DBG_START_STR	"SATRT\n"
#define OVERTIME_FUNCTION_DBG(str){\
	if(gFunDbgFlag){\
		printf("\n%%OVERTIME-FUN-DBG:%s-%d-%s", __FUNCTION__, __LINE__, str);\
	}\
}

STATIC CHAR * get_str_elements(CHAR *str, CHAR flag);
STATIC VOID calc_month_overtime_all_days(OVERTIEINFO * overtimeInfo);
STATIC UINT8 get_format_char_number(CHAR * src, char format);
STATIC VOID calc_over_time(IN INT32 fdi, OUT INT32 fdo);
STATIC VOID reset_day_info(DAYINFO * dayInfo);
STATIC VOID reset_overtime_Info(OVERTIEINFO * overtimeInfo);
STATIC VOID get_day_info_from_dayInfoBuffer( CHAR * dayInfoStr, DAYINFO * dayInfo);
STATIC CHAR * get_day_info_from_overtimeTable(CHAR * src, CHAR * dst);
STATIC INT32 add_dayInfo_to_overtimeInfo(OVERTIEINFO * overtimeInfo, DAYINFO * dayInfo);
STATIC VOID save_overtime_info(OVERTIEINFO * overtimeInfo, INT32 fd);
STATIC VOID calc_day_overtime_info_from_base_info(DAYINFO * dayInfo);

#endif /* _OVER_TIME_TABLE_CALC_H_ */

