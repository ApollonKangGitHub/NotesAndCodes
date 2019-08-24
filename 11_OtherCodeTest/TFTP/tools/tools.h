#ifndef __TFTP_TOOLS_H_
#define __TFTP_TOOLS_H_

#include <tftpType.h>

EXTERN CHAR * uitoa(UINT32 value, CHAR * str);
EXTERN UINT32 atoui(CONST CHAR * str);
EXTERN CHAR * uitoxa(UINT32 value, CHAR * str);
EXTERN CHAR * clear_more_space(CHAR * str);


#endif
