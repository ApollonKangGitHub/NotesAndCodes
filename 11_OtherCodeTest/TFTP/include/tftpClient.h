#ifndef __TFTP_CLIENT_H__
#define __TFTP_CLIENT_H__

#include <tftpType.h>


#define __TFTP_CLIENT_DEFAULT_SOCKET_UDP_PORT_		(60009)
#define __TFTP_CLIENT_DEFAULT_IP_ADDR_				(INADDR_ANY)

EXTERN tftpReturnValue_t tftp_client_module_init(VOID);


#endif /* __TFTP_CLIENT_H__ */
