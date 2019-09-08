#ifndef __TFTP_TOOLS_H_
#define __TFTP_TOOLS_H_

#include <tftpType.h>

#define MAX_STR_LEN 	101	
#define SIZE_BIT_KB		10		/* 单位为KB */

#define _PROGRESS_BAR_BLACK				"\033[30m"
#define _PROGRESS_BAR_RED				"\033[31m"
#define _PROGRESS_BAR_GREEN				"\033[32m"
#define _PROGRESS_BAR_BLUE				"\033[34m"
#define _PROGRESS_BAR_RESET				"\r\033[0m"
#define PRINT_RED(format, ...)       		printf(_PROGRESS_BAR_RED""format""_PROGRESS_BAR_RESET, ##__VA_ARGS__)
#define PRINT_GREEN(format, ...)   			printf(_PROGRESS_BAR_BLUE""format""_PROGRESS_BAR_RESET, ##__VA_ARGS__)  
#define PRINT_YELLOW(format, ...)   		printf(_PROGRESS_BAR_GREEN""format""_PROGRESS_BAR_RESET, ##__VA_ARGS__) 
#define PRINT_BLACK(format, ...)			printf(_PROGRESS_BAR_BLACK""format""_PROGRESS_BAR_RESET, ##__VA_ARGS__) 

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
EXTERN VOID progressBar(UINT32 fileSize, UINT32 curSize);

#endif
