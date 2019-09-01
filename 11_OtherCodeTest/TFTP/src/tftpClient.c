#include <tftpClient.h>
#include <tftpType.h>
#include <tftpSem.h>
#include <tftpSocket.h>
#include <tftpLog.h>
#include <tftpShell.h>
#include <tftpPack.h>

#include <tftpPublic.h>

/* 全局资源 */
LOCAL CHAR gSendBuf[__TFTP_SEND_BUG_LEN_] = {0};
LOCAL CHAR gRecvBuf[__TFTP_RECV_BUF_LEN_] = {0};
LOCAL CHAR * gFileName[__TFTP_FILE_NAME_LEN_] = {0};
LOCAL CHAR * gClientPath[__TFTP_FILE_PATH_LEN_] = {0};
LOCAL CHAR * gClientFile[__TFTP_FILE_PATH_LEN_] = {0};

/* 客户端通信传输相关信息结构 */
LOCAL tftpClientInfo_t gCliTranInfo;

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
	memset(&gCliTranInfo._serAddr, 0, sizeof(gCliTranInfo._serAddr));
	gCliTranInfo._serAddr.sin_family = AF_INET;
	gCliTranInfo._serAddr.sin_port = htons(__TFTP_SOCKET_SERVER_UDP_PORT_);
	gCliTranInfo._serAddr.sin_addr.s_addr = inet_addr(ipaddr);

	/* 客户端socket创建 */
	gCliTranInfo._socketFd = tftp_socket_create(&gCliTranInfo._cliAddr, FALSE);	
	if (gCliTranInfo._socketFd < 0) {
		TFTP_LOGERR("create client socket fail, return:%d", gCliTranInfo._socketFd);
		return tftp_ret_Error;
	}
	
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
LOCAL tftpReturnValue_t tftp_client_pack_deal_download()
{

	while (TRUE) {
		break;
	}
}

/*
 * FunctionName:
 *     tftp_client_pack_deal_upload
 * Description:
 *     tftpclient上传报文交互
 * Notes:
 *     
 */
LOCAL tftpReturnValue_t tftp_client_pack_deal_upload()
{
	while (TRUE) {
		/* 等待ACK/OACK */
		break;
	}

}

/*
 * FunctionName:
 *     tftp_client_oper_valid
 * Description:
 *     操作有效性判断
 * Notes:
 *     
 */
LOCAL tftpReturnValue_t tftp_client_oper_valid(CONST char * fileName)
{
	BOOL exist = FALSE;
	tftpReturnValue_t ret = tftp_ret_Ok;

	/* 初始化 */
	gCliTranInfo._fileName = (CHAR *)gFileName;
	gCliTranInfo._filePath = (CHAR *)gClientFile;
	gCliTranInfo._clientPath = (CHAR *)gClientPath;
	
	memcpy(gCliTranInfo._fileName, fileName, strlen(fileName));
	memset(gCliTranInfo._filePath, 0, strlen(gCliTranInfo._filePath));
	memcpy(gCliTranInfo._filePath,
			gCliTranInfo._clientPath, 
			strlen(gCliTranInfo._clientPath));
	
	strncat((CHAR*)(gCliTranInfo._filePath),
			gCliTranInfo._fileName, 
			strlen(gCliTranInfo._fileName));
	
	/* 判断文件是否存在 */
	exist = isfileExist((CONST CHAR * )gCliTranInfo._filePath);
	
	/* 根据操作决定返回值 */
	if (exist && (tftp_Pack_OperCode_Rrq == gCliTranInfo._opcode)) {
		ret = tftp_ret_Exist;
	}
	else if (!exist && (tftp_Pack_OperCode_Wrq == gCliTranInfo._opcode)) {
		ret =  tftp_ret_NotFound;
	}
	else {
		ret =  tftp_ret_Ok;
	}
	
	return ret;
}

LOCAL UINT32 tftp_cilent_get_file_size(CONST char * filePath)
{
	if (tftp_Pack_OperCode_Rrq == gCliTranInfo._opcode) {
		/* 下载，文件大小为0 */
		return 0;				
	}
	else {
		/* 上传，文件大小为实际文件大小 */
		return (UINT32)fileSize(filePath);		
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
		case __TFTP_BLKSIZE_1428_BYTES_:
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
	UINT16 bpid = 0;
	/* 最大断点块号为65535，获取断点块号文件 */
	
	/* 无断点传输，即断点块号为0 */
	return bpid;
}

/*
 * FunctionName:
 *     tftp_client_cmd_handle
 * Description:
 *     tftpclient下载/上传命令
 * Notes:
 *     
 */
LOCAL CHAR * tftp_client_get_tranfer_mode(CHAR  * pMode, tftpPackMode_t * mode)
{
	if (0 == strcasecmp(pMode, __TFTP_MODE_NETASCII_)) {
		*mode = tftp_Pack_Mode_netascii;
		return pMode;
	}
	else if (0 == strcasecmp(pMode, __TFTP_MODE_OCTET_)) {
		*mode = tftp_Pack_Mode_octet;
		return pMode;
	}
	else if (0 == strcasecmp(pMode, __TFTP_MODE_MAIL_)) {
		*mode = tftp_Pack_Mode_mail;
		return pMode;
	}
	else {
		tftp_print("invalid mode:%s, set default:%s", pMode, __TFTP_MODE_OCTET_);
		*mode = tftp_Pack_Mode_octet;
		return __TFTP_MODE_OCTET_;
	}
}

LOCAL tftpReturnValue_t tftp_client_tranfer_info_init(INT32 argc, CHAR * argv[])
{
	tftpReturnValue_t tftpRet = tftp_ret_Ok;
	socklen_t addrLen = 0;
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
	gCliTranInfo._opcode = tftp_pack_oper_para_get(pOperator);
	if (tftp_Pack_OperCode_Max == gCliTranInfo._opcode) {
		tftp_print("\r\nInvalid operator for %s!", pOperator);
		return tftp_ret_Error;
	}
	
	/* 2、客户端socket初始化和服务器socket结构初始化 */
	tftpRet = tftp_client_socket_init(pIpaddr);
	if (tftp_ret_Ok != tftpRet) {
		TFTP_IF_ERROR(tftpRet);
		return tftpRet;
	}

	/* 3、文件名获取与操作有效判断 */
	tftpRet = tftp_client_oper_valid(pFilename);
	if (tftp_ret_Ok != tftpRet) {
		tftp_print("\r\nfile %s %s, Can't do this operator!", pFilename, tftp_err_msg(tftpRet));
		return tftpRet;
	}

	/* 4、请求报文参数获取 */
	gCliTranInfo._pMode = tftp_client_get_tranfer_mode(pMode, &gCliTranInfo._mode);
	gCliTranInfo._timeout = tftp_client_get_timeout(pTimeout);
	gCliTranInfo._blksize = tftp_client_get_blksize(pBlksize);
	gCliTranInfo._fileSize = tftp_cilent_get_file_size((CONST CHAR *)(&gCliTranInfo._opcode));
	gCliTranInfo._bpid = tftp_client_get_bpid(pFilename);

	/* 5、客户端socket结构信息获取保存 */
	addrLen = sizeof(gCliTranInfo._cliAddr);
	ret = getsockname(gCliTranInfo._socketFd, (struct sockaddr *)&gCliTranInfo._cliAddr, &addrLen);
	if (ret < 0) {
		TFTP_LOGERR("get client socket name fail, return %d, socketfd=%d, socketLen=%d", \
			ret, gCliTranInfo._socketFd, addrLen);
		return tftp_ret_Error;
	}
	
	return tftp_ret_Ok;
}


/*
 * FunctionName:
 *     tftp_client_cmd_handle
 * Description:
 *     tftpclient下载/上传命令解析处理函数
 *     example：tftpclient get serverip 127.0.110.1 file test.txt mode octet blocksize 1024 timeout 10 
 * Notes:
 *     
 */
LOCAL VOID tftp_client_cmd_handle(INT32 argc, CHAR * argv[])
{
	tftp_print("\r\ntftp client start!!!");
	tftpReturnValue_t tftpRet = tftp_ret_Ok;
	INT32 sendLen = 0;
	INT32 recvLen = 0;
	INT32 ret = 0;

	/* 1、参数解析、初始化信息 */
	tftpRet = tftp_client_tranfer_info_init(argc, argv);
	if (tftpRet != tftp_ret_Ok) {
		TFTP_IF_ERROR(tftpRet);
		return;
	}
	
	/* 2、请求报文封装 */
	sendLen = tftp_pack_req(gSendBuf, \
				gCliTranInfo._opcode, \
				gCliTranInfo._fileName, \
				gCliTranInfo._pMode, \
				gCliTranInfo._fileSize, \
				gCliTranInfo._timeout, \
				gCliTranInfo._blksize, \
				gCliTranInfo._bpid);
	
	/* 3、发送请求到服务器 */
	ret = tftp_socket_send(gCliTranInfo._socketFd, gSendBuf, sendLen, &gCliTranInfo._serAddr);

	/* 4、处理服务器响应 */
	if (tftp_Pack_OperCode_Rrq == gCliTranInfo._opcode) {
		tftpRet = tftp_client_pack_deal_download();
	} 
	else if (tftp_Pack_OperCode_Wrq == gCliTranInfo._opcode) {
		tftpRet = tftp_client_pack_deal_upload();
	}

	/* 5、传输完毕销毁相关传输资源 */
	close(gCliTranInfo._socketFd);
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
							"__UINT32__{128/256/512/1024/1428/2048/4096 Bytes, default is 512}"
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


