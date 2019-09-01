#ifndef __TFTP_CLIENT_H__
#define __TFTP_CLIENT_H__

#include <tftpType.h>
#include <tftpPack.h>
#include <tftpPublic.h>

typedef struct tftpClientInfo_s {
	struct sockaddr_in _serAddr;
	struct sockaddr_in _cliAddr;
	tftpPackOperCode_t _opcode;
	tftpPackMode_t _mode;
	CHAR * _pMode;
	CHAR * _fileName;
	CHAR * _filePath;
	CHAR * _clientPath;
	UINT16 _timeout;
	UINT16 _blksize;
	UINT16 _bpid;
	INT32 _socketFd;
	INT32 _fileFd;
	UINT32 _fileSize;
}tftpClientInfo_t;

EXTERN tftpReturnValue_t tftp_client_module_init(VOID);

#endif /* __TFTP_CLIENT_H__ */
