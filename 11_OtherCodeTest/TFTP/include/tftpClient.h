#ifndef __TFTP_CLIENT_H__
#define __TFTP_CLIENT_H__

#include <tftpType.h>
#include <tftpPack.h>
#include <tftpPublic.h>

typedef struct tftpClientInfo_s {
	struct sockaddr_in _serAddr;
	struct sockaddr_in _cliAddr;
	CHAR _filePath[__TFTP_FILE_PATH_LEN_];
	CHAR _clientPath[__TFTP_FILE_PATH_LEN_];
	INT32 _socketFd;
	INT32 _fileFd;
	tftpPacktReq_t _reqPack;
}tftpClientInfo_t;

EXTERN tftpReturnValue_t tftp_client_module_init(VOID);

#endif /* __TFTP_CLIENT_H__ */
