#ifndef __TFTP_TOOLS_H_
#define __TFTP_TOOLS_H_

#include <tftpType.h>

EXTERN CHAR * uitoa(UINT32 value, CHAR * str);
EXTERN UINT32 atoui(CONST CHAR * str);
EXTERN CHAR * uitoxa(UINT32 value, CHAR * str);
EXTERN CHAR * clear_more_space(CHAR * str);
EXTERN CONST CHAR * str_ipv4_check(CONST CHAR * str);
EXTERN CONST CHAR * str_hex_check(CONST CHAR * str);
EXTERN CONST CHAR * str_uint32_check(CONST CHAR * str);
EXTERN CONST CHAR * str_int32_check(CONST CHAR * str);
EXTERN CONST CHAR * str_cmdstr_check(CONST CHAR * str);

#endif
