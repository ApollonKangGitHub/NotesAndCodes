#ifndef __TFTP_SHELL_H__
#define __TFTP_SHELL_H__

#include <tftpType.h>

#define __TFTP_SHELL_VERSION_	"tftp Shell1.0"

/* shell线程资源栈大小 */
#define __TFTP_SHELL_THREAD_STACK_SIZE_		(0x100000)	

/* shell输入输出缓冲区大小 */
#define __TFTP_SHELL_BUFFER_LEN_MAX_		(128)

EXTERN INT32 tftp_shell_module_init(VOID);

#endif /* __TFTP_SHELL_H_ */
