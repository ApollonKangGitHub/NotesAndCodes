#include <tftpClient.h>
#include <tftpType.h>
#include <tftpSem.h>
#include <tftpSocket.h>
#include <tftpLog.h>
#include <tftpShell.h>
#include <tftpPack.h>

#include <tftpPublic.h>

/* 全局资源 */
LOCAL UINT8 gSendBuf[__TFTP_SEND_BUF_LEN_] = {0};
LOCAL UINT8 gRecvBuf[__TFTP_RECV_BUF_LEN_] = {0};

/* 客户端通信传输相关信息结构 */
LOCAL tftpClientInfo_t gCliTranInfo;

EXTERN VOID md5_algroithm(CHAR CONST * file, UINT8 * result);

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
	INT32 recvLen = 0;
	
	while (TRUE) {
		recvLen = tftp_socket_recv(gCliTranInfo._socketFd, gRecvBuf, __TFTP_RECV_BUF_LEN_, &gCliTranInfo._serAddr);
		break;

	}
	return tftp_ret_Ok;
}
LOCAL tftpReturnValue_t tftp_client_oack_check
(
	tftpPacktReq_t * pRecvInfo, 
	CHAR * errMsg
)
{
	tftpReturnValue_t tftpRet = tftp_ret_Ok;
	CHAR errMsgTemp[__TFTP_ERR_PACK_MAX_LEN_] = {0};

	if (__TFTP_OPCODE_ERR_ == pRecvInfo->_opcode) {
		TFTP_LOGERR("recv error code(%d), error message:%s", TFTP_GET_ERRCODE(gRecvBuf), TFTP_GET_ERRMSG(gRecvBuf));
		tftpRet = tftp_ret_NotSupport;
		goto ack_check_ret;
	}
	else if (__TFTP_OPCODE_OACK_ != pRecvInfo->_opcode) {
		tftp_sprint(errMsgTemp, "%s<%d>, not have recv oack, waiting...", __TFTP_ERR_NOTDEFINE_OPCODE_INVALID_, pRecvInfo->_opcode);
		tftpRet = tftp_ret_Error;
		goto ack_check_ret;
	}

	/* 选项检查 */
	if (pRecvInfo->_options._opt_blksize) {
		if (pRecvInfo->_blkSize > __TFTP_BLKSIZE_8192_BYTES_
			|| pRecvInfo->_blkSize  < __TFTP_BLKSIZE_128_BYTES_) {
			tftp_sprint(errMsgTemp, "%s<%d>", __TFTP_ERR_NOTDEFINE_BLKSIZE_INVALID_, pRecvInfo->_blkSize);
			tftpRet = tftp_ret_Error;
			goto ack_check_ret;		
		}
	}
	else if (pRecvInfo->_options._opt_tsize) {
		if (pRecvInfo->_tSize > __TFTP_TSIZE_MAX_
			|| pRecvInfo->_tSize < __TFTP_TSIZE_MIN_) {
			tftp_sprint(errMsgTemp, "%s<%d>", __TFTP_ERR_NOTDEFINE_FILE_TOO_LARGE_, pRecvInfo->_tSize);
			tftpRet = tftp_ret_Error;
			goto ack_check_ret; 	
		}
	}
	else if (pRecvInfo->_options._opt_bpid) {
		if (pRecvInfo->_bpId < __TFTP_BLKID_MIN_
			|| pRecvInfo->_bpId > __TFTP_BLKID_MAX_) {
			tftp_sprint(errMsgTemp, "%s<%d>", __TFTP_ERR_NOTDEFINE_BPID_INVALID_, pRecvInfo->_bpId);
			tftpRet = tftp_ret_Error;
			goto ack_check_ret; 
		}
	}
	else if (pRecvInfo->_options._opt_timout) {
		if (pRecvInfo->_timeout < __TFTP_TIMEOUT_MIN_
			|| pRecvInfo->_timeout > __TFTP_TIMEOUT_MAX_) {
			tftp_sprint(errMsgTemp, "%s<%d>", __TFTP_ERR_NOTDEFINE_TIMEOUT_INVALID_, pRecvInfo->_timeout);
			tftpRet = tftp_ret_Error;
			goto ack_check_ret; 
		}
	}
	else if (pRecvInfo->_options._opt_tmfreq) {
		if (pRecvInfo->_tmfreq < __TFTP_TMFREQ_MIN_
			|| pRecvInfo->_tmfreq > __TFTP_TMFREQ_MAX_) {
			tftp_sprint(errMsgTemp, "%s<%d>", __TFTP_ERR_NOTDEFINE_TMFREQ_INVALID_, pRecvInfo->_tmfreq);
			tftpRet = tftp_ret_Error;
			goto ack_check_ret; 
		}
	}

ack_check_ret:
	memcpy(errMsg, errMsgTemp, __TFTP_ERR_PACK_MAX_LEN_);
	return tftpRet;
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
	INT32 recvLen = 0;
	INT32 sendLen = 0;
	INT32 readLen = 0;
	UINT16 ack = 0;
	UINT16 blkid = 0;
	UINT32 curSize = 0;
	BOOL progressBarFirst = TRUE;
	tftpReturnValue_t tftpRet = tftp_ret_Ok;
	INT32 sockfd = gCliTranInfo._socketFd;
	CHAR errMsg[__TFTP_ERR_PACK_MAX_LEN_] = {0};
	struct sockaddr_in * pSerAddr = &gCliTranInfo._serAddr;
	tftpPacktReq_t recvInfo = gCliTranInfo._reqPack;

	/* 接收客户端OACK/ERROR报文 */
	recvLen = tftp_socket_recv(sockfd, gRecvBuf, __TFTP_RECV_BUF_LEN_, pSerAddr);
	if (recvLen < 0) {
		TFTP_LOGERR("Recv server information error, errno=%d!", errno);
		tftp_perror("recv fail reason is");
		goto tftp_upload_err_ret;
	}
	
	/* 对于OACK解析 */
	tftpRet = tftp_unpack_oack(gRecvBuf, recvLen, &recvInfo);
	if (TFTP_FAILURE(tftpRet)) {
		TFTP_IF_ERROR(tftpRet);
		goto tftp_upload_err_ret;
	}
	/* OACK有效性检查 */
	tftpRet = tftp_client_oack_check(&recvInfo, errMsg);
	if (TFTP_FAILURE(tftpRet)) {
		if (tftp_ret_Error == tftpRet) {
			goto tftp_upload_err_send_ret;
		}
		else {
			goto tftp_upload_err_ret;
		}
	}

	blkid = 1;
	while (TRUE) {
		(VOID)memset(gRecvBuf, 0, __TFTP_RECV_BUF_LEN_);
		(VOID)memset(gSendBuf, 0, __TFTP_SEND_BUF_LEN_);
		/* 读取文件 */
		readLen = tftp_read(gCliTranInfo._fileFd, gSendBuf + __TFTP_DATA_SHIFT_, recvInfo._blkSize);
		if (readLen < 0) {
			tftp_sprint(errMsg, "%s<%s>", __TFTP_ERR_NOTDEFINE_FILE_READ_FAIL_, recvInfo._fileName);
			sendLen = (INT32)tftp_pack_error(gSendBuf, tftp_Pack_ErrCode_AccViolate, errMsg);
			goto tftp_upload_err_send_ret;
		}		

		/* 进度条 */
		curSize += readLen;
		progressBar(recvInfo._tSize, curSize, progressBarFirst);
		progressBarFirst = FALSE;
		
		/* 封装DATA数据包 */
		sendLen = readLen + (INT32)tftp_pack_data(gSendBuf, blkid);
		
		/* 发送数据 */
		tftp_socket_send(sockfd, gSendBuf, sendLen, pSerAddr);

		/* 接收ACK/ERROR数据 */
		recvLen = tftp_socket_recv(sockfd, gRecvBuf, __TFTP_RECV_BUF_LEN_, pSerAddr);
		if (recvLen < 0) {
			TFTP_LOGERR("Recv server information error, errno=%d!", errno);
			tftp_perror("recv fail reason is");
			goto tftp_upload_err_ret;
		}
		
		switch (TFTP_GET_OPCODE(gRecvBuf)) {
			case __TFTP_OPCODE_ACK_:
				ack = TFTP_GET_ACK(gRecvBuf);

				/* ACK判断 */
				if (ack != blkid) {
					tftp_sprint(errMsg, "%s<ack tid:%d, blkid:%d>", __TFTP_ERR_UNKNOWNTD_, ack, blkid);
					sendLen = (INT32)tftp_pack_error(gSendBuf, tftp_Pack_ErrCode_UnknownId, errMsg); 				
					goto tftp_upload_err_send_ret;
				}

				/* 根据发送的报文大小小于blksize判断结束 */
				if (readLen < recvInfo._blkSize) {
					goto tftp_upload_ok_ret;
				}	
				blkid++;
				break;
			case __TFTP_OPCODE_ERR_:
				TFTP_LOGERR("recv error code(%d), error message:%s", TFTP_GET_ERRCODE(gRecvBuf), TFTP_GET_ERRMSG(gRecvBuf));
				goto tftp_upload_err_ret;
			default:
				tftp_sprint(errMsg, "%s(%d), not have recv ack, waiting...", __TFTP_ERR_NOTDEFINE_OPCODE_INVALID_, recvInfo._opcode);
				sendLen = (INT32)tftp_pack_error(gSendBuf, tftp_Pack_ErrCode_AccViolate, errMsg);
				goto tftp_upload_err_send_ret;
		}
	}
tftp_upload_ok_ret:
	return tftp_ret_Ok;

tftp_upload_err_send_ret:
	/* 出错发送ERROR code */
	(VOID)tftp_socket_send(sockfd, gSendBuf, sendLen, pSerAddr);

tftp_upload_err_ret:
	return tftp_ret_Error;
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
	INT32 len = 0;
	tftpReturnValue_t ret = tftp_ret_Ok;

	/* 记录文件名，补全文件名绝对路径 */
	len = strlen(fileName);
	memcpy(gCliTranInfo._reqPack._fileName, fileName, len);
	len = strlen(gCliTranInfo._filePath);
	memset(gCliTranInfo._filePath, 0, len);
	len = strlen(gCliTranInfo._clientPath);
	memcpy(gCliTranInfo._filePath, gCliTranInfo._clientPath, len);
	len = strlen(gCliTranInfo._reqPack._fileName);
	strncat((CHAR*)(gCliTranInfo._filePath), gCliTranInfo._reqPack._fileName, len);

	/* 判断文件是否存在 */
	exist = isfileExist((CONST CHAR * )gCliTranInfo._filePath);
	
	/* 根据操作决定返回值 */
	if (exist && (tftp_Pack_OperCode_Rrq == gCliTranInfo._reqPack._opcode)) {
		ret = tftp_ret_Exist;
	}
	else if (!exist && (tftp_Pack_OperCode_Wrq == gCliTranInfo._reqPack._opcode)) {
		ret =  tftp_ret_NotFound;
	}
	else {
		/* 打开文件 */
		gCliTranInfo._fileFd = tftp_open(gCliTranInfo._filePath, O_RDONLY);
		if (gCliTranInfo._fileFd < 0) {
			TFTP_LOGERR("open file %s fail, errno=%d", gCliTranInfo._filePath, errno);
			tftp_perror("open file fail reason is");
			return tftp_ret_Error;
		}
		ret =  tftp_ret_Ok;
	}
	
	return ret;
}

LOCAL UINT32 tftp_cilent_get_file_size(CONST char * filePath)
{
	if (tftp_Pack_OperCode_Rrq == gCliTranInfo._reqPack._opcode) {
		/* 下载，文件大小为0 */
		return 0;				
	}
	else {
		/* 上传，文件大小为实际文件大小 */
		return (UINT32)fileSize(filePath);		
	}
}

LOCAL UINT16 tftp_client_get_timeout(CONST CHAR * pTimeout)
{
	UINT16 timeout = 0;
	if (NULL == pTimeout) {
		timeout = __TFTP_TIMEOUT_DEFAULT_;
	}
	else {
		timeout = (UINT16)atoui(pTimeout);
	}

	/* Valid values range between "1" and "255" seconds,inclusive */
	if (timeout > 255 || timeout < 1) {
		TFTP_LOGWARN("invalid timeout:%d(s), set default:%d(s)", timeout, __TFTP_TIMEOUT_DEFAULT_);
		timeout = __TFTP_TIMEOUT_DEFAULT_;
	}

	return timeout;
}

LOCAL UINT16 tftp_client_get_tmfreq(CONST CHAR * pTmFreq)
{
	UINT16 tmfreq = 0;
	if (NULL == pTmFreq) {
		tmfreq = __TFTP_TMFREQ_DEFAULT_;
	}
	else {
		tmfreq = (UINT16)atoui(pTmFreq);
	}

	if (tmfreq > __TFTP_TMFREQ_MAX_ || tmfreq < __TFTP_TMFREQ_MIN_) {
		TFTP_LOGWARN("invalid timeout frequency:%d, set default:%d", tmfreq, __TFTP_TMFREQ_DEFAULT_);
		tmfreq = __TFTP_TMFREQ_DEFAULT_;
	}

	return tmfreq;
}

LOCAL UINT16 tftp_client_get_blksize(CONST CHAR * pBlksize)
{
	UINT16 blksize = 0;
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
		case __TFTP_BLKSIZE_8192_BYTES_:
			break;
		default:
			TFTP_LOGWARN("invalid block size:%d(Bytes), set default:%d(Bytes)", blksize, __TFTP_DEFAULT_BLKSIZE_);
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

LOCAL tftpReturnValue_t tftp_client_tranfer_info_init(INT32 argc, CHAR * argv[])
{
	tftpReturnValue_t tftpRet = tftp_ret_Ok;
	INT32 ret = 0;
	
	CHAR * pOperator = argv[1];
	CHAR * pIpaddr = argv[3];
	CHAR * pFilename = argv[5];
	CHAR * pMode = argv[7];
	CHAR * pBlksize = argv[9];
	CHAR * pTimeout = argv[11];
	CHAR * pTmFreq = argv[13];
	
	TFTP_LOGDBG(tftp_dbgSwitch_client, \
		"operator:%s, ipaddr:%s, filename:%s, blksize:%d, timeout:%d", \
			pOperator, pIpaddr, pFilename, pBlksize, pTimeout);

	/* 1、操作类型获取 */
	gCliTranInfo._reqPack._opcode = tftp_pack_oper_para_get(pOperator);
	if (tftp_Pack_OperCode_Max == gCliTranInfo._reqPack._opcode) {
		TFTP_LOGERR("Invalid operator for %s!", pOperator);
		return tftp_ret_Error;
	}
	
	/* 2、客户端socket初始化和服务器socket结构初始化 */
	tftpRet = tftp_client_socket_init(pIpaddr);
	if (TFTP_FAILURE(tftpRet)) {
		return tftpRet;
	}

	/* 3、文件名获取与操作有效判断 */
	tftpRet = tftp_client_oper_valid(pFilename);
	if (tftp_ret_Ok != tftpRet) {
		TFTP_LOGERR("file %s %s, Can't do this operator!", pFilename, tftp_err_msg(tftpRet));
		return tftpRet;
	}

	/* 4、请求报文参数获取 */
	tftp_pack_get_tranfer_mode(pMode, gCliTranInfo._reqPack._pMode, &gCliTranInfo._reqPack._mode);
	gCliTranInfo._reqPack._blkSize = tftp_client_get_blksize(pBlksize);
	gCliTranInfo._reqPack._tSize = tftp_cilent_get_file_size((CONST CHAR *)(&gCliTranInfo._filePath));
	gCliTranInfo._reqPack._bpId = tftp_client_get_bpid(pFilename);
	gCliTranInfo._reqPack._timeout = tftp_client_get_timeout(pTimeout);
	gCliTranInfo._reqPack._tmfreq = tftp_client_get_tmfreq(pTmFreq);
	
	/* 5、可扩展选项有效标志，当前命令行选项参数都为有效 */
	gCliTranInfo._reqPack._options._opt_blksize = 1;
	gCliTranInfo._reqPack._options._opt_bpid = 1;
	gCliTranInfo._reqPack._options._opt_tmfreq = 1;
	gCliTranInfo._reqPack._options._opt_timout = 1;
	gCliTranInfo._reqPack._options._opt_tsize = 1;
	gCliTranInfo._reqPack._options._opt_other = 0;

	return tftp_ret_Ok;
}

LOCAL tftpReturnValue_t tftp_client_config_init(VOID)
{
	memcpy(gCliTranInfo._clientPath, "/home/Krj/NoteAndCodes/11_OtherCodeTest/TFTP/client/", __TFTP_FILE_PATH_LEN_);
}

/*
 * FunctionName:
 *     tftp_client_info_reset
 * Description:
 *     数据结构清空
 *     
 * Notes:
 *     
 */
LOCAL VOID tftp_client_info_reset(VOID)
{
	UINT8 md5Result[64] = {0};
	time_t timeStampStart = 0;
	time_t timeStampEnd = 0;
	time_t useTime = 0;
	
	if (gCliTranInfo._fileFd > 0) {
		tftp_close(gCliTranInfo._fileFd);
		gCliTranInfo._fileFd = -1;
	}
	if (gCliTranInfo._socketFd > 0) {
		tftp_close(gCliTranInfo._socketFd);
		gCliTranInfo._socketFd = -1;
	}
	
	/* 计算文件md5值 */
	PRINT_GREEN("\r\nfile %s md5sum is calcing...",  gCliTranInfo._filePath);
	tftp_fflush(__TFTP_STDOUT_);

	/* 获取MD5计算开始时间戳 */
	(VOID)time (&timeStampStart);

	/* 开始计算 */
	(VOID)md5_algroithm(gCliTranInfo._filePath, md5Result);
	PRINT_GREEN("\r\nfile %s md5sum calc success hash result is %s",  gCliTranInfo._filePath, md5Result);

	/* 获取结束时间戳 */
	(VOID)time (&timeStampEnd);

	/* 计算MD5计算耗时 */
	useTime = timeStampEnd - timeStampStart;
	PRINT_GREEN("\r\nMD5 calc use time:%lus", useTime);
	
	memset(&gCliTranInfo._cliAddr, 0, sizeof(gCliTranInfo._cliAddr));
	memset(&gCliTranInfo._serAddr, 0, sizeof(gCliTranInfo._serAddr));
	memset(gCliTranInfo._filePath, 0, sizeof(gCliTranInfo._filePath));
	memset(&gCliTranInfo._reqPack, 0, sizeof(gCliTranInfo._reqPack));

	return;
}

/*
 * FunctionName:
 *     tftp_client_cmd_handle
 * Description:
 *     tftpclient下载/上传命令解析处理函数
 * Notes:
 *     
 */
LOCAL VOID tftp_client_cmd_handle(INT32 argc, CHAR * argv[])
{
	tftp_print("\r\ntftp client start!!!");
	tftpReturnValue_t tftpRet = tftp_ret_Ok;
	time_t timeStampStart = 0;
	time_t timeStampEnd = 0;
	time_t useTime = 0;
	INT32 sendLen = 0;
	INT32 recvLen = 0;
	INT32 ret = 0;
	FLOAT speed = 0;
	
	/*
	 * 0、客户端配置初始化,客户端配置文件在config目录下的client.cfg文件中
	 * 在启动客户端，执行客户端uload/download命令之前需要保证基本配置齐全
	 */
	tftp_client_config_init();

	/* 1、参数解析、初始化信息 */
	tftpRet = tftp_client_tranfer_info_init(argc, argv);
	if (tftpRet != tftp_ret_Ok) {
		TFTP_IF_ERROR(tftpRet);
		return;
	}
	
	/* 2、请求报文封装 */
	sendLen = tftp_pack_req(gSendBuf, &gCliTranInfo._reqPack);

	/* 3、发送请求到服务器 */
	ret = tftp_socket_send(gCliTranInfo._socketFd, gSendBuf, sendLen, &gCliTranInfo._serAddr);

	/* 获取传输前时间戳 */
	(VOID)time (&timeStampStart);

	/* 4、处理服务器响应 */
	if (tftp_Pack_OperCode_Rrq == gCliTranInfo._reqPack._opcode) {
		tftpRet = tftp_client_pack_deal_download();
	} 
	else if (tftp_Pack_OperCode_Wrq == gCliTranInfo._reqPack._opcode) {
		tftpRet = tftp_client_pack_deal_upload();
	}
	
	/* 获取结束时间戳 */
	(VOID)time (&timeStampEnd);

	/* 计算耗时和速率 */
	useTime = timeStampEnd - timeStampStart;
	speed = (float)gCliTranInfo._reqPack._tSize / __MB_CELL_;
	PRINT_GREEN("\r\nfile transfer use time:%lus, speed:%.2fMB/s", useTime, useTime ? (speed / useTime) : speed);
	
	/* 5、传输完毕重新初始化相关传输资源 */
	tftp_client_info_reset();
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
			"tftpclient{tftp client}"
			"__STRING__{upload(put) or download(get)}"
				"serverip{server ip address}"
				"__IPADDR__{ip address(eg:192.168.1.100)}"
					"file{file name for get/put}"
					"__STRING__{string of file name without path}"
						"mode{mode of the file transfer}"
						"__STRING__{transfer mode:netascii/octet/mail}"
							"blocksize{translation blockszie(Bytes) everytimes}"
							"__UINT32__{128/256/512/1024/1428/2048/4096 Bytes, default 512}"
								"timeout{DATA/ACK timeout second}"
								"__UINT32__{0 is default 60 s}"
									"tmfreq{DATA/ACK timeout retransmission frequency}"
									"__UINT32__{0 is default 5 times}");
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
	TFTP_LOGDBG(tftp_dbgSwitch_client, "tftp client module init...");

	/* 注册客户端相关操作命令 */
	tftp_client_command_init();
}


