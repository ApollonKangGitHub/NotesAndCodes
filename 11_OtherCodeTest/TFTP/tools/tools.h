#ifndef __TFTP_TOOLS_H_
#define __TFTP_TOOLS_H_

#include <tftpType.h>

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

#endif
