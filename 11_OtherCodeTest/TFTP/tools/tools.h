#ifndef __TFTP_TOOLS_H_
#define __TFTP_TOOLS_H_

#include <tftpType.h>

#define MAX_STR_LEN 	101	
#define SIZE_BIT_KB		10		/* 单位为KB */

/******************************************************************************
 * Time:2018年9月30日13:23:31
 * printf()的颜色格式:\033[{attr1};{attr2};...{attrn}m
 * 以\033即Esc的ASCII开始，跟随n个属性，以m结尾
 * eg:\033[32;41m
 * attr属性取值：
 * 0：重置所有属性；1：高亮/加粗；2：暗淡；4：下滑线；5：闪烁；6：反转；8：隐藏
 * 30～37为前景色，40～47为背景色，依次是：
 * 黑	红	绿	黄	蓝	紫	青	白
 * 30	31 	32 	33	34 	35 	36  37
 * 40	41	42	43	44	45	46	47
 * ****************************************************************************/
#define _PROGRESS_BAR_BLACK					"\033[30;47m"
#define _PROGRESS_BAR_RED					"\033[31;40m"
#define _PROGRESS_BAR_GREEN					"\033[32;40m"
#define _PROGRESS_BAR_YELLOW 				"\033[33;40m"
#define _PROGRESS_BAR_BLUE					"\033[34;40m"
#define __PROGRESS_BAR_PUPRLE				"\033[35;40m"
#define __PROGRESS_BAR_CYAN					"\033[36;40m"
#define __PROGRESS_BAR_WHITE				"\033[37;40m"
#define _PROGRESS_BAR_RESET					"\033[0m"

#define PRINT_BLACK(format, ...)			printf(_PROGRESS_BAR_BLACK""format""_PROGRESS_BAR_RESET, ##__VA_ARGS__) 
#define PRINT_RED(format, ...)       		printf(_PROGRESS_BAR_RED""format""_PROGRESS_BAR_RESET, ##__VA_ARGS__)
#define PRINT_GREEN(format, ...)   			printf(_PROGRESS_BAR_GREEN""format""_PROGRESS_BAR_RESET, ##__VA_ARGS__)  
#define PRINT_YELLOW(format, ...)   		printf(_PROGRESS_BAR_YELLOW""format""_PROGRESS_BAR_RESET, ##__VA_ARGS__) 
#define PRINT_BLUE(format, ...)				printf(_PROGRESS_BAR_BLUE""format""_PROGRESS_BAR_RESET, ##__VA_ARGS__) 
#define PRINT_PUPRLE(format, ...)			printf(__PROGRESS_BAR_PUPRLE""format""_PROGRESS_BAR_RESET, ##__VA_ARGS__) 
#define PRINT_CYAN(format, ...)				printf(__PROGRESS_BAR_CYAN""format""_PROGRESS_BAR_RESET, ##__VA_ARGS__) 
#define PRINT_WHITE(format, ...)			printf(__PROGRESS_BAR_WHITE""format""_PROGRESS_BAR_RESET, ##__VA_ARGS__) 

#define __MB_CELL_	(1U << 20)
#define __KB_CELL_	(1U << 10)

EXTERN CHAR * uitoa(UINT32 value, CHAR * str);
EXTERN UINT32 atoui(CONST CHAR * str);
EXTERN CHAR * uitoxa(UINT32 value, CHAR * str);
EXTERN CHAR * clearMoreSpace(CHAR * str);
EXTERN CONST CHAR * strIpv4Check(CONST CHAR * str);
EXTERN CONST CHAR * strHexCheck(CONST CHAR * str);
EXTERN CONST CHAR * strUint32Check(CONST CHAR * str);
EXTERN CONST CHAR * strInt32Check(CONST CHAR * str);
EXTERN CONST CHAR * strCmdStrCheck(CONST CHAR * str);
EXTERN BOOL isfileExist(CONST CHAR * filename);
EXTERN UINT64 fileSize(CONST CHAR * filename);
EXTERN VOID progressBar(UINT32 fileSize, UINT32 curSize, BOOL first);

#endif
