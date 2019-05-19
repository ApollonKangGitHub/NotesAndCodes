/*
 * FileName:OvertimeTable.c
 * Author:Kangruojin
 * Time:2019年5月19日14:16:37
 * Version:1.0
 * Description:基于文件の格式化信息计算加班时长
 */
#include "OvertimeTable.h"

#define ARRAY_TITLE_LENGTH		11
#define ARRAY_WEEKSTRING_LENGTH	9	

BOOL gInfoDbgFlag = FALSE;
BOOL gFunDbgFlag = FALSE;
/* 
 * Format of information for everyday:
 * #[day],[week],[startH]:[startM]-[endH]:[endM],<<[adjust],>[Holiday]>\n
 * Examples:
 * #5,7,9:12-20:49,1,\n
 * #17,5,0:00-0:00,\n
 * etc.
 */ 

STATIC CHAR * title[ARRAY_TITLE_LENGTH] = {
	"DayIndex", 
	"Week", 
	"StartStamp", 
	"EndStamp", 
	"Holiday", 
	"SleepTime", 
	"Hours", 
	"Minutes", 
	"Rebound",
	"adjust",
	"Exception"
};

STATIC CHAR * weekString[ARRAY_WEEKSTRING_LENGTH] = {
	"Error",
	"Monday",
	"Tuesday",
	"Wednesday",
	"Thursday",
	"Friday",
	"Saturday",
	"Sunday",
	"Invalid"
};
int main(int argc, char * argv[])
{
	CHAR filei[128] = {0};
	CHAR fileo[128] = {0};

	INT32 fdi = -1;
	INT32 fdo = -1;

	if(argc < 2){
		printf("\nError:The number of parameters error!\nFormat:%s fileName \n", argv[0]);
		exit(EXIT_FAILURE);
	}

	strcpy(filei, argv[1]);
	strcpy(fileo, argv[1]);
	strcat(fileo, ".result");

	fdi = open(filei, O_RDONLY);
	fdo = open(fileo, O_CREAT | O_RDWR | O_TRUNC, 0664);
	if(fdi < 0 || fdo < 0){
		printf("\nOpen file[input file:%s, output file:%s] "
			"or create file failure[fdi:%d,fdo:%d]!\n", filei, fileo, fdi, fdo);
		exit(EXIT_FAILURE);
	}

	(VOID)calc_over_time(fdi, fdo);
	return 0;
}

VOID calc_over_time(IN INT32 fdi,OUT INT32 fdo)
{
	CHAR overtimeTable[OVER_TIME_TABLE_BUFFER] = {0};
	CHAR dayInfoBuff[DAY_INFO_BUFFER] = {0};
	INT32 ret = ERROR;
	UINT8 line = 0;

	DAYINFO dayInfo;
	OVERTIEINFO overtimeInfo;
		
	CHAR * pOverTime = overtimeTable;
	CHAR * saveptr = NULL;

	reset_overtime_Info(&overtimeInfo);
	
	/* 一次性将文件读取到缓冲区 */
	ret = read(fdi, pOverTime, OVER_TIME_TABLE_BUFFER);
	if(ret < 0){
		printf("\nRead file failure!\n");
		exit(EXIT_FAILURE);
	}

	overtimeInfo.overtimeDay = get_format_char_number(pOverTime, '#');
	
	for(line = 0; line < overtimeInfo.overtimeDay; line++){
		memset(dayInfoBuff, 0, DAY_INFO_BUFFER);
		reset_day_info(&dayInfo);
		/* 获取一天的打卡信息,格式为：#day,week,start-end<,holiday>，获取结果不包括'#' */
		pOverTime = get_day_info_from_overtimeTable(pOverTime, dayInfoBuff);

		/* 获取并解析一天的基本信息:dayIndex、week、start、end、flag */
		get_day_info_from_dayInfoBuffer(dayInfoBuff, &dayInfo);

		/* 根据以上基本信息计算其他信息:即实际的一天加班时长计算 */
		calc_day_overtime_info_from_base_info(&dayInfo);

		/* 保存一天的信息到一月的加班信息中去 */
		add_dayInfo_to_overtimeInfo(&overtimeInfo, &dayInfo);
	}
	/* 计算一个月的加班时间（包括周末，但不包括节假日加班和调休加班） */
	calc_month_overtime_all_days(&overtimeInfo);
	/* 保存加班信息到文件中 */
	save_overtime_info(&overtimeInfo, fdo);
	
	if(gInfoDbgFlag){
		/* 加班信息显示在屏幕上 */
		save_overtime_info(&overtimeInfo, 1);
	}
	close(fdi);
	close(fdo);
	
}

VOID calc_month_overtime_all_days(OVERTIEINFO * overtimeInfo)
{
	OVERTIEINFO * pOver = overtimeInfo;
	UINT8 dayIndex = 0;

	pOver->totalMinutes = 0;
	pOver->totalHours = 0;
	while(dayIndex < pOver->overtimeDay){
		/* 
		 * holiday（节假日加班）有计算当天加班时长，但是不计入总的加班时长
 		 * adjust（调休加班）和工作日一样
		 */
		if(!pOver->day[dayIndex].holidayFlag){
			pOver->totalMinutes += pOver->day[dayIndex].minutes;
		}
		dayIndex++;
	}
	pOver->totalHours = (DOUBLE)(pOver->totalMinutes) / 60;
}

UINT8 get_format_char_number(CHAR * src, char format)
{
	UINT8 num = 0;
	while(*src){
		if(*src++ == '#'){
			num++;
		}
	}

	return num;
}

VOID reset_day_info(DAYINFO * dayInfo)
{
	dayInfo->dayIndex = 0;
	dayInfo->week = weekError;
	dayInfo->startTimeStamp = 0;
	dayInfo->endTimeStamp = 0;
	dayInfo->holidayFlag = FALSE;
	dayInfo->adjustFlag = FALSE;
	dayInfo->hours = 0;
	dayInfo->minutes = 0;
	dayInfo->sleepTime = 0;
	dayInfo->exceptionFlag = FALSE;
	dayInfo->reboundTime = 0;
}

VOID reset_overtime_Info(OVERTIEINFO * overtimeInfo)
{
	INT32 i = 0;

	overtimeInfo->overtimeDay = 0;
	overtimeInfo->totalMinutes = 0;
	overtimeInfo->totalHours = 0;
	for(i = 0; i < ONE_MONTH_MAX_DAYS; i++){
		reset_day_info(&overtimeInfo->day[i]);
	}
}

INT32 add_dayInfo_to_overtimeInfo(OVERTIEINFO * overtimeInfo, DAYINFO * dayInfo)
{
	if(dayInfo->dayIndex > ONE_MONTH_MAX_DAYS
		|| !overtimeInfo
		|| !dayInfo){
		return ERROR;
	}
		
	overtimeInfo->day[dayInfo->dayIndex - 1].dayIndex = dayInfo->dayIndex;
	overtimeInfo->day[dayInfo->dayIndex - 1].endTimeStamp = dayInfo->endTimeStamp;
	overtimeInfo->day[dayInfo->dayIndex - 1].holidayFlag = dayInfo->holidayFlag;
	overtimeInfo->day[dayInfo->dayIndex - 1].hours = dayInfo->hours ;
	overtimeInfo->day[dayInfo->dayIndex - 1].minutes = dayInfo->minutes;
	overtimeInfo->day[dayInfo->dayIndex - 1].startTimeStamp = dayInfo->startTimeStamp;
	overtimeInfo->day[dayInfo->dayIndex - 1].week = dayInfo->week;
	overtimeInfo->day[dayInfo->dayIndex - 1].sleepTime = dayInfo->sleepTime;
	overtimeInfo->day[dayInfo->dayIndex - 1].exceptionFlag = dayInfo->exceptionFlag;
	overtimeInfo->day[dayInfo->dayIndex - 1].reboundTime = dayInfo->reboundTime;
	overtimeInfo->day[dayInfo->dayIndex - 1].adjustFlag = dayInfo->adjustFlag;
}
VOID save_overtime_info(OVERTIEINFO * overtimeInfo, INT32 fd)
{
	INT32 i = 0;
	FILE * fp = fdopen(fd, "w+");

	fprintf(fp, "\nTotal overtime minutes:%d [hours:%lf], exclude hoilday and adjust day", 
			overtimeInfo->totalMinutes, overtimeInfo->totalHours);
	fprintf(fp, "\nDetails of each day are shown below:\n");

	fprintf(fp, "\n%8s%10s%16s%12s%12s%12s%10s%12s%12s%10s%12s", \
			title[0], title[1], title[2], title[3], title[4], \
			title[5], title[6], title[7], title[8],title[9], title[10]);

	for(i = 0; i < overtimeInfo->overtimeDay; i++){
		fprintf(fp, "\n%4d%16s%10d%14d%12d%10d%16lf%8d%12d%10d%14s",
			overtimeInfo->day[i].dayIndex,
			weekString[overtimeInfo->day[i].week],
			overtimeInfo->day[i].startTimeStamp,
			overtimeInfo->day[i].endTimeStamp,
			overtimeInfo->day[i].holidayFlag,
			overtimeInfo->day[i].sleepTime,
			overtimeInfo->day[i].hours,
			overtimeInfo->day[i].minutes,
			overtimeInfo->day[i].reboundTime,
			overtimeInfo->day[i].adjustFlag,
			overtimeInfo->day[i].exceptionFlag ? "Exception" : "Normal");
	}

	fprintf(fp, "\n\n");
	fclose(fp);
}
VOID get_day_info_from_dayInfoBuffer(CHAR * dayInfoStr, DAYINFO * dayInfo)
{	
	CHAR * pMove = NULL;
	CHAR * saveptr = NULL;

	reset_day_info(dayInfo);

	if(gInfoDbgFlag){
		printf("\n");
	}
	
	OVERTIME_FUNCTION_DBG(FUN_DBG_START_STR);

	/* 先获取dayIndex,','前为dayIndex */
	DAYINFO_ASSIGNMENT_FROM_BUFFER
		(pMove, dayInfoStr, ",", &saveptr, dayInfo->dayIndex, =, 1);

	/* 再获取week,','前为week */
	DAYINFO_ASSIGNMENT_FROM_BUFFER
		(pMove, NULL, ",", &saveptr ,dayInfo->week, =, 1);

	/* 获取startTimeStamp,':'前为hour,'-'前为minutes */
	DAYINFO_ASSIGNMENT_FROM_BUFFER
		(pMove, NULL, ":", &saveptr, dayInfo->startTimeStamp, =, 60);
	DAYINFO_ASSIGNMENT_FROM_BUFFER
		(pMove, NULL, "-", &saveptr, dayInfo->startTimeStamp, +=, 1);

	/* 获取endTimeStamp,':'前为hour,','前为minutes */
	DAYINFO_ASSIGNMENT_FROM_BUFFER
		(pMove, NULL, ":", &saveptr, dayInfo->endTimeStamp, =, 60);
	DAYINFO_ASSIGNMENT_FROM_BUFFER
		(pMove, NULL, ",", &saveptr, dayInfo->endTimeStamp, +=, 1);

	/* 获取adjustFlag,','之前为adjustFlag */
	DAYINFO_ASSIGNMENT_FROM_BUFFER
		(pMove, NULL, ",", &saveptr, dayInfo->adjustFlag, =, 1);	
	
	/* 获取holidayFlag,'\n'前为获取holidayFlag */
	DAYINFO_ASSIGNMENT_FROM_BUFFER
		(pMove, NULL, "\n", &saveptr, dayInfo->holidayFlag, =, 1);

	OVERTIME_FUNCTION_DBG(FUN_DBG_END_STR);
}

VOID calc_day_overtime_info_from_base_info(DAYINFO * dayInfo)
{
	UINT32 workTimes = 0; 
	UINT32 sleepTimes = 0;
	/* 
	 * 正常工作日同一减去8小时、sleep、rebound三个时间
     * 但是工作的8小时可能和rebound减去的时间重叠而多减
	 */
	UINT32 more = 0;

	OVERTIME_FUNCTION_DBG(FUN_DBG_START_STR);
	
	/* 未打卡或打卡记录还未出，或早上/晚上忘记打卡，
	 * 或进卡时间大于出卡时间，或出卡时间小于早上上班时间，均为异常状态 */
	if(!(dayInfo->startTimeStamp && dayInfo->endTimeStamp) 
		|| (dayInfo->endTimeStamp <= dayInfo->startTimeStamp)
		|| (dayInfo->endTimeStamp <= ONE_DAY_BEGIN_TIME)){
		if(!dayInfo->holidayFlag){
			dayInfo->exceptionFlag = TRUE;
		}
		return;
	}

	if((dayInfo->adjustFlag)		/* 周末但是属于节假日调休,即属于正常上班 */
		|| (!dayInfo->holidayFlag) 	/* 非节假日且在周内 */ 
		&& (dayInfo->week >= weekMonday)
		&& (dayInfo->week <= weekFriday)){
		/* 正常工作时间 */
		workTimes = NORMAL_WORKING_MINUTES;
		/* 进卡时间或出卡时间不正常 */
		if((dayInfo->startTimeStamp > MORNING_REBOUND_TIME)
			|| (dayInfo->endTimeStamp < AFTERNOON_SLEEP_BEGIN_TIME)){
			/* 迟到且不能弹回/早退均为异常 */
			dayInfo->exceptionFlag = TRUE;
			return;
		}
			
		/* 计算弹回时间 */
		if((dayInfo->startTimeStamp > MORNING_BEGIN_TIME)){
			/* 弹回的两个区间 */
			dayInfo->reboundTime = (dayInfo->startTimeStamp > MORNING_REBOUND_TIME_15)
				? (MORNING_REBOUND_TIME_30 - MORNING_BEGIN_TIME)
				: (MORNING_REBOUND_TIME_15 - MORNING_BEGIN_TIME);
		}
		
		/* 计算Sleep时间 */
		if(dayInfo->endTimeStamp > OVERTIME_EFFECT_BEGIN_TIME){
			/* 能够达到加班有效的出卡时间 */
			dayInfo->sleepTime = SLEEP_TIME_TWICE;
		}
		else{
			/* 不能达到加班有效的出卡时间，AFTERNOON_SLEEP_BEGIN_TIME以后均为休息时间 */
			dayInfo->sleepTime = SLEEP_TIME_NOON + dayInfo->endTimeStamp - AFTERNOON_SLEEP_BEGIN_TIME;
		}
	}
	else{
		/* 周末（或节假日加班）workTimes为0，即全为加班时间 */
		workTimes = 0;
		/* 注：此时已经确保进卡时间小于出卡时间 */
		if(dayInfo->startTimeStamp >= NOON_SLEEP_BEGIN_TIME){
			/* 进卡时间和出卡时间同时在中午休息时间 */
			if(dayInfo->endTimeStamp <= NOON_SLEEP_END_TIME){
				dayInfo->exceptionFlag = TRUE;
				return;
			}
			else{
				/* 进卡时间在中午休息时间（或之后） */
				dayInfo->sleepTime = (dayInfo->startTimeStamp <= NOON_SLEEP_END_TIME)
									? (NOON_SLEEP_END_TIME - dayInfo->startTimeStamp)
									: 0;
			}
		}
		else if(dayInfo->endTimeStamp <= NOON_SLEEP_END_TIME){
			/* 出卡时间在中午休息时间（或之前） */
			dayInfo->sleepTime = (dayInfo->endTimeStamp >= NOON_SLEEP_BEGIN_TIME)
								? (dayInfo->endTimeStamp - NOON_SLEEP_BEGIN_TIME)
								: 0;
		}
		else{
			/* 进卡时间在中午休息时间之前并且出卡时间在中午休息时间之后 */
			dayInfo->sleepTime = SLEEP_TIME_NOON;
		}
	}
	more = (dayInfo->reboundTime > 0) ?
		   (dayInfo->startTimeStamp - MORNING_BEGIN_TIME) : (0);

	/* 
	 * 或许多余周内来说，只要早上可弹回或正常，只需要计算下班后
	 * 18:45之后有没有达到加班有效界限并减去弹回时长即可，但是，
     * 为了和周末统一处理，所以用以下计算方式
	 */
	dayInfo->minutes = dayInfo->endTimeStamp 
						- ((dayInfo->startTimeStamp <= MORNING_BEGIN_TIME)
						? MORNING_BEGIN_TIME
						: dayInfo->startTimeStamp)
						- dayInfo->sleepTime 
						- dayInfo->reboundTime
						- workTimes
						+ more;
	
	dayInfo->hours = (DOUBLE)(dayInfo->minutes) / 60;

	if(gInfoDbgFlag){
		printf("\n####dayIndex:%d,endTimeStamp:%d,startTimeStamp:%d, sleepTime:%d"
			"reboundTime:%d, workTimes:%d, minutes:%d, hours:%lf, holidayFlag:%d\n", 
			dayInfo->dayIndex, 
			dayInfo->endTimeStamp, 
			dayInfo->startTimeStamp,
			dayInfo->sleepTime,
			dayInfo->reboundTime,
			workTimes,
			dayInfo->minutes,
			dayInfo->hours,
			dayInfo->holidayFlag);
	}
	
	OVERTIME_FUNCTION_DBG(FUN_DBG_END_STR);
	return;
}
CHAR * get_day_info_from_overtimeTable(CHAR * src, CHAR * dst)
{
	CHAR * pMonth = src;
	CHAR * pDay = dst;
	BOOL startLine = FALSE;

	/* 
	 * 以'#'开始以'\n'结束，从src复制到dst中，不包括'\n'
 	 * 比如：#1,3,8:17-18:04,1\n#2,4,0:00-0:00@,1,1\n    ==> 第一项为"#1,3,8:17-18:04,1\n"
 	 * 表示第1天,周三,AM 8:17进卡,PM 18:04出卡, 是节假日
	 */
	while((*pMonth != '\0') && (*pMonth++ != '#')){
		continue;
	}

	while((*pMonth != '\0') && (*pMonth != '\n')){
		*pDay++ = *pMonth++;
	}
	
	/* 返回NULL表示这是最后一天的信息 */
	if(*pMonth == '\0'){
		return NULL;
	}

	return pMonth;
}

CHAR * get_str_elements(CHAR *str, CHAR flag){
	while(*str){
		if(*str++ == flag){
			break;
		}
	}			
	return str;
}

