#include <tftpClient.h>
#include <tftpType.h>
#include <tftpSem.h>
#include <tftpSocket.h>
#include <tftpLog.h>
#include <tftpShell.h>
#include <tftpPack.h>

#include <tftpPublic.h>

LOCAL INT32 gClientSockfd = 0;
LOCAL CHAR gSendBuf[__TFTP_SEND_BUG_LEN_] = {"Hello server, I love you!"};
LOCAL CHAR gRecvBuf[__TFTP_RECV_BUF_LEN_] = {0};
LOCAL CHAR * gClientPath[__TFTP_FILE_PATH_LEN_] = {0};
struct sockaddr_in gSeraddr;
struct sockaddr_in gCliaddr;

/*
 * FunctionName:
 *     tftp_client_socket_init
 * Description:
 *     客户端通信socket初始化
 * Notes:
 *     
 */
LOCAL tftpReturnValue_t tftp_client_socket_init(CONST CHAR * ipaddr)
{
	/* 初始化服务器地址等信息 */
	memset(&gSeraddr, 0, sizeof(gSeraddr));
	gSeraddr.sin_family = AF_INET;
	gSeraddr.sin_port = htons(__TFTP_SOCKET_SERVER_UDP_PORT_);
	gSeraddr.sin_addr.s_addr = inet_addr(ipaddr);

	/* 客户端socket创建 */
	gClientSockfd = tftp_socket_create(&gCliaddr, FALSE);	
	
	return tftp_ret_Ok;
}

/*
 * FunctionName:
 *     tftp_client_pack_deal_download
 * Description:
 *     tftpclient下载报文交互
 * Notes:
 *     
 */
LOCAL VOID tftp_client_pack_deal_download()
{


}

/*
 * FunctionName:
 *     tftp_client_pack_deal_upload
 * Description:
 *     tftpclient上传报文交互
 * Notes:
 *     
 */
LOCAL VOID tftp_client_pack_deal_upload()
{

}

/*
 * FunctionName:
 *     tftp_client_oper_valid
 * Description:
 *     操作有效性判断
 * Notes:
 *     
 */
LOCAL tftpReturnValue_t tftp_client_oper_valid(CONST char * fileName, tftpPackOperCode_t opcode)
{
	BOOL exist = FALSE;
	
	/* 加上文件绝对路径 */
	strncat((CHAR*)gClientPath, fileName, strlen(fileName));
	
	/* 判断文件是否存在 */
	exist = isfileExist((CONST CHAR * )gClientPath);
	
	/* 根据操作决定返回值 */
	if (exist && (tftp_Pack_OperCode_Rrq == opcode)) {
		return tftp_ret_Exist;
	}
	else if (!exist && (tftp_Pack_OperCode_Wrq == opcode)) {
		return tftp_ret_NotFound;
	}
	else {
		return tftp_ret_Ok;
	}
}

LOCAL UINT32 tftp_cilent_get_file_size(CONST char * filePath, tftpPackOperCode_t opcode)
{
	if (tftp_Pack_OperCode_Rrq == opcode) {
		return 0;				/* 下载，文件大小为0 */
	}
	else {
		return (UINT32)fileSize(filePath);		/* 上传，文件大小为实际文件大小 */
	}
}

LOCAL UINT32 tftp_client_get_timeout(CONST CHAR * pTimeout)
{
	UINT32 timeout = 0;
	if (NULL == pTimeout) {
		timeout = __TFTP_DEFAULT_TIMEOUT_;
	}
	else {
		timeout = atoui(pTimeout);
	}

	/* Valid values range between "1" and "255" seconds,inclusive */
	if (timeout > 255 || timeout < 1) {
		tftp_print("invalid timeout:%d(s), set default:%d(s)", timeout, __TFTP_DEFAULT_TIMEOUT_);
		timeout = __TFTP_DEFAULT_TIMEOUT_;
	}

	return timeout;
}
LOCAL UINT32 tftp_client_get_blksize(CONST CHAR * pBlksize)
{
	UINT32 blksize = 0;
	if (NULL == pBlksize) {
		blksize = __TFTP_DEFAULT_BLKSIZE_;
	}
	else {
		blksize = atoui(pBlksize);
	}

	switch (blksize) {
		case __TFTP_BLKSIZE_128_BYTES_:	
		case __TFTP_BLKSIZE_256_BYTES_:	
		case __TFTP_BLKSIZE_512_BYTES_:	
		case __TFTP_BLKSIZE_1024_BYTES_:	
		case __TFTP_BLKSIZE_2048_BYTES_:	
		case __TFTP_BLKSIZE_4096_BYTES_:	
			break;
		default:
			tftp_print("invalid block size:%d(Bytes), set default:%d(Bytes)", blksize, __TFTP_DEFAULT_BLKSIZE_);
			blksize = __TFTP_DEFAULT_BLKSIZE_;
			break;
	}
	return blksize;
}

/*
 * FunctionName:
 *     tftp_client_get_bpid
 * Description:
 *     根据文件名获取断点块号
 * Notes:
 *     
 */
LOCAL UINT16 tftp_client_get_bpid(CONST CHAR * filename)
{
	/* 最大断点块号为65535 */
	return 0;
}

/*
 * FunctionName:
 *     tftp_client_cmd_handle
 * Description:
 *     tftpclient下载/上传命令
 * Notes:
 *     
 */
LOCAL CHAR * tftp_client_get_tranfer_mode(CHAR  * mode)
{
	if ((0 == strcmp(mode, __TFTP_MODE_NETASCII_))
		|| (0 == strcmp(mode, __TFTP_MODE_OCTET_))
		|| (0 == strcmp(mode, __TFTP_MODE_MAIL_))) {
		return mode;
	}
	else {
		tftp_print("invalid mode:%s, set default:%s", mode, __TFTP_MODE_OCTET_);
		return __TFTP_MODE_OCTET_;
	}
}

/*
 * FunctionName:
 *     tftp_client_cmd_handle
 * Description:
 *     tftpclient下载/上传命令
 * Notes:
 *     
 */
LOCAL VOID tftp_client_cmd_handle(INT32 argc, CHAR * argv[])
{
	tftp_print("\r\ntftp client start!!!");
	tftpPackOperCode_t opcode = tftp_Pack_OperCode_Max;
	tftpReturnValue_t tftpRet = tftp_ret_Ok;
	INT32 sendLen = 0;
	INT32 recvLen = 0;
	UINT32 timeout = 0;
	UINT32 blkSize = 0;
	UINT32 fileSize = 0;
	UINT16 bpid = 0;
	INT32 ret = 0;

	CHAR * pOperator = argv[1];
	CHAR * pIpaddr = argv[3];
	CHAR * pFilename = argv[5];
	CHAR * pMode = argv[7];
	CHAR * pBlksize = argv[9];
	CHAR * pTimeout = argv[11];

	TFTP_LOGDBG(tftp_dbgSwitch_client, \
		"operator:%s, ipaddr:%s, filename:%s, blksize:%d, timeout:%d", \
			pOperator, pIpaddr, pFilename, pBlksize, pTimeout);

	/* 1、操作类型获取 */
	opcode = tftp_pack_oper_para_get(pOperator);
	if (opcode == tftp_Pack_OperCode_Max) {
		tftp_print("\r\nInvalid operator for %s!", pOperator);
		return;
	}
	
	/* 2、客户端socket初始化和服务器socket结构初始化 */
	tftp_client_socket_init(pIpaddr);

	/* 3、文件名获取与操作有效判断 */
	tftpRet = tftp_client_oper_valid(pFilename, opcode);
	if ((tftp_ret_Exist == tftpRet)
		|| (tftp_ret_NotFound == tftpRet)) {
		tftp_print("\r\nfile %s %s, Can't do this operator!", pFilename, tftp_err_msg(tftpRet));
		return;
	}

	/* 4、请求报文参数获取 */
	pMode = tftp_client_get_tranfer_mode(pMode);
	timeout = tftp_client_get_timeout(pTimeout);
	blkSize = tftp_client_get_blksize(pBlksize);
	fileSize = tftp_cilent_get_file_size((CONST CHAR *)gClientPath, opcode);
	bpid = tftp_client_get_bpid(pFilename);
	
	/* 5、请求报文封装 */
	sendLen = tftp_pack_req(gSendBuf, opcode, pFilename, pMode, fileSize, timeout, blkSize, bpid);
	
	/* 6、发送请求到服务器 */
	ret = tftp_socket_send(gClientSockfd, gSendBuf, sendLen, &gSeraddr);

	/* 7、处理服务器响应 */
	if (opcode == tftp_Pack_OperCode_Rrq) {
		tftp_client_pack_deal_download();
	} 
	else if (opcode == tftp_Pack_OperCode_Wrq) {
		tftp_client_pack_deal_upload();
	}
}

/*
 * FunctionName:
 *     tftp_client_command_init
 * Description:
 *     客户端命令注册
 * Notes:
 *     
 */
LOCAL VOID tftp_client_command_init(VOID)
{
	tftp_shell_cmd_register((tftp_cmd_deal_fun)tftp_client_cmd_handle, 
		__TFTP_CMD_NORMAL_ | __TFTP_CMD_DYN_,
			"tftpclient{tftp server enable/disable}"
			"__STRING__{upload(put) or download(get)}"
				"serverip{server ip address}"
				"__IPADDR__{ip address(eg:192.168.1.100)}"
					"file{file name for get/put}"
					"__STRING__{string of file name without path}"
						"mode{mode of the file transfer}"
						"__STRING__{transfer mode:netascii/octet/mail}"
							"blocksize{translation blockszie(Bytes) everytimes}"
							"__UINT32__{128/256/512/1024/2048/4096 Bytes, default is 512}"
								"timeout{DATA/ACK timeout second}"
								"__UINT32__{0 is default 60 s}");
}

/*
 * FunctionName:
 *     tftp_client_module_init
 * Description:
 *     client模块初始化接口
 * Notes:
 *     
 */
EXTERN tftpReturnValue_t tftp_client_module_init(VOID)
{
	/* 注册客户端相关操作命令 */
	tftp_client_command_init();

	/* 打开配置文件，获取客户端下载/上传的文件路径 */
}


