#include <tftpServer.h>
#include <tftpType.h>
#include <tftpSem.h>
#include <tftpLog.h>
#include <tftpSocket.h>
#include <tftpShell.h>
#include <tftpPack.h>

#include <tftpPublic.h>

/* 在Server初始化时赋值为TRUE，Server结束时赋值为FALSE */
LOCAL BOOL gServerRun = FALSE;
tftpTaskPoolList_t * gTaskPoolHead = NULL;
tftpTaskPoolList_t * gTaskPoolTail = NULL;
INT32 gListenSocket = 0;
LOCAL tftpSem_t * gSemPool;
LOCAL CHAR gServerPath[__TFTP_FILE_PATH_LEN_] = {"/home/Krj/NoteAndCodes/11_OtherCodeTest/TFTP/server/"};

EXTERN VOID md5_algroithm(CHAR CONST * file, UINT8 * result);

/*
 * FunctionName:
 *     tftp_server_cmd_display_task_pool
 * Description:
 *     显示task pool信息，可全部显示或显示指定tid的task信息
 * Notes:
 *     
 */
EXTERN tftpReturnValue_t tftp_server_cmd_display_task_pool(INT32 argc, CHAR * argv[])
{
	tftpTaskPoolList_t * pTemp = gTaskPoolHead;
	tftpTaskPool_t * pTaskNode = NULL;
	tftpTaskInfo_t taskInfo;
	tftpSocketInfo_t * pClient = NULL;
	tftpPacktReq_t * pReq = NULL;
	tftpTaskId_t taskId = 0;
	tftpPid_t tid = 0;
		
	TFTP_LOGDBG(tftp_dbgSwitch_server, "tftp task pool display, argc=%d", argc);

	tid = atoi(argv[3]);
	
	tftp_print("\r\n-----------------------------------------------------------------");
	tftp_print("\r\n---------------------- TFTP TASK POOL INFO ----------------------");
	
	while (pTemp) {
		pTaskNode = &pTemp->_taskNode;
		memset(&taskInfo, 0, sizeof(taskInfo));

		/* 获取线程taskInfo信息 */
		taskId = tftp_task_get_info_by_tid(pTaskNode->_tid, &taskInfo);
		if (taskId < 0) {
			TFTP_LOGERR("tftp get task info fail, tid=%d, return taskId=%d", pTaskNode->_tid, taskId);
			return tftp_ret_Error;
		}

		if((tid == pTaskNode->_tid) || (tid == __TFTP_TID_ALL_)) {
			pClient = &(pTaskNode->_cliInfo);
			pReq = &(pClient->_reqInfo);
				
			tftp_print("\r\n----commucation child task name:%s----", taskInfo._name);
			tftp_print("\r\n\t%-24s:%s", "client IP", pClient->_cliIpAddr);
			tftp_print("\r\n\t%-24s:%d", "client UDP port", pClient->_cliPort);
			tftp_print("\r\n\t%-24s:%u", "client opcode", pReq->_opcode);
			tftp_print("\r\n\t%-24s:%s", "client file Name", pReq->_fileName);
			tftp_print("\r\n\t%-24s:%d", "client file fd", pTaskNode->_fileFd);
			tftp_print("\r\n\t%-24s:%u", "client file size", pReq->_tSize);
			tftp_print("\r\n\t%-24s:%u", "client block size", pReq->_blkSize);
			tftp_print("\r\n\t%-24s:%u", "client break point id", pReq->_bpId);
			tftp_print("\r\n\t%-24s:%u", "client timout", pReq->_timeout);
			tftp_print("\r\n\t%-24s:%u", "client tmfreq", pReq->_tmfreq);
			tftp_print("\r\n\t%-24s:%d", "task socket fd", pTaskNode->_sockfd);
			tftp_print("\r\n\t%-24s:%d", "task udp port", pTaskNode->_port);
			tftp_print("\r\n\t%-24s:%u", "task tid", pTaskNode->_tid);
			tftp_print("\r\n\t%-24s:%s", "task busy status", pTaskNode->_busy ? "BUSY" : "FREE");
			tftp_print("\r\n\t%-24s:%p", "task sync lock", pTaskNode->_syncLock);
		}
		if (tid == pTaskNode->_tid) {
			break;
		}
		pTemp = pTemp->_next;
	}
	tftp_print("\r\n-----------------------------------------------------------------");

	return tftp_ret_Ok;
}

/*
 * FunctionName:
 *     tftp_server_task_pool_node_create
 * Description:
 *     线程池通信子任务链表信息节点创建
 * Notes:
 *     
 */
LOCAL tftpTaskPoolList_t * tftp_server_task_pool_node_create
(
	tftpSem_t * sem, 
	tftpPid_t tid
)
{
	tftpTaskPoolList_t * pPoolNode = NULL;

	TFTP_LOGDBG(tftp_dbgSwitch_server, "tftp server task pool create node, tid=%d", tid);
	
	pPoolNode = malloc(sizeof(tftpTaskPoolList_t));
	if (NULL == pPoolNode) {
		TFTP_LOGERR("Error tftp pool node info malloc, pPoolNode=%p!", pPoolNode);
		return NULL;	
	}

	pPoolNode->_next = pPoolNode->_pre = NULL;
	pPoolNode->_taskNode._tid = tid;
	pPoolNode->_taskNode._syncLock = sem;
	pPoolNode->_taskNode._busy = FALSE;
	pPoolNode->_taskNode._sockfd = -1;
	pPoolNode->_taskNode._fileFd = -1;
	pPoolNode->_taskNode._port = __TFTP_SERVER_TASK_POOL_UDP_PORT_START_ + (tid % __TFTP_SERVER_TASK_POOL_UDP_PORT_RAND_);
	pPoolNode->_taskNode._cliInfo._cliPort = 0;
	pPoolNode->_taskNode._cliInfo._cliIpAddr[0] = '\0';
	
	return pPoolNode;
}

/*
 * FunctionName:
 *     tftp_server_task_pool_node_insert
 * Description:
 *     线程池通信子任务链表信息节点插入链表
 * Notes:
 *     
 */
LOCAL tftpReturnValue_t tftp_server_task_pool_node_insert
(
	tftpTaskPoolList_t * pNode
)
{
	if (NULL == pNode) {
		return tftp_ret_Null;
	}

	if(NULL == gTaskPoolHead) {
		pNode->_pre = pNode->_next = NULL;
		gTaskPoolHead = gTaskPoolTail = pNode;
	}
	else {
		gTaskPoolTail->_next = pNode;
		pNode->_pre = gTaskPoolTail;
		pNode->_next = NULL;
		gTaskPoolTail = pNode;
	}
	
	return tftp_ret_Ok;
}

LOCAL tftpTaskPool_t * tftp_server_get_client_info_bytid(tftpPid_t tid)
{
	tftpTaskPoolList_t * pFind = gTaskPoolHead;

	while (pFind) {
		if (tid == pFind->_taskNode._tid) {
			return &(pFind->_taskNode);
		}
		pFind = pFind->_next;
	}	
	
	return NULL;
}
 
tftpSemInfo_t * tftp_server_find_task_sem(tftpPid_t tid)
{
	IN tftpSem_t * semId= NULL;
	OUT tftpSemInfo_t * pSemInfo = NULL;
	tftpTaskPoolList_t * find = NULL;
	
	/* 找到smeid，根据semid获取semInfo */
	for (find = gTaskPoolHead; find; find = find->_next) {
		if (tid == find->_taskNode._tid) {
			semId = find->_taskNode._syncLock;
			break;
		}
	}
	
	pSemInfo = tftp_sem_info_node_find(semId, &pSemInfo);
	if (NULL == pSemInfo) {
		TFTP_LOGERR("find sem for server task pool fail");
		return NULL;
	}
	
	return pSemInfo;
}

/*
 * FunctionName:
 *     tftp_server_client_req_check
 * Description:
 *     客户端请求检查
 * Notes:
 *     
 */
LOCAL tftpReturnValue_t tftp_server_client_req_check(tftpSocketInfo_t * cliReqInfo)
{
	tftpPacktReq_t * reqInfo = NULL;
	CHAR bufModeTemp[__TFTP_TRAN_MODE_LEN_] = {0};

	if (NULL == cliReqInfo) {
		return tftp_ret_Null;
	}
	
	reqInfo = &cliReqInfo->_reqInfo;
	reqInfo->_oack_opts = 0;

	/* 请求opcode检查 */
	if ((reqInfo->_opcode != tftp_Pack_OperCode_Wrq) 
		&& (reqInfo->_opcode != tftp_Pack_OperCode_Rrq)) {
		goto tftp_req_not_support_return;
	}
	
	/* 模式检查 */
	(VOID)tftp_pack_get_tranfer_mode(reqInfo->_pMode, bufModeTemp, &(reqInfo->_mode));
	if (reqInfo->_mode > tftp_Pack_Mode_mail || reqInfo->_mode < tftp_Pack_Mode_netascii) {
		goto tftp_req_not_support_return;
	}
	
	/* timeout检查不符合规范则回复一个默认timeout给客户端 */
	if ((reqInfo->_timeout > __TFTP_TIMEOUT_MAX_)
		|| (reqInfo->_timeout < __TFTP_TIMEOUT_MIN_)) {
		reqInfo->_timeout = __TFTP_TIMEOUT_DEFAULT_;
	}
	reqInfo->_oack_opts++;
		
	/* timeout frequence不符合范围，则返回一个默认值给客户端 */
	if ((reqInfo->_tmfreq > __TFTP_TMFREQ_MAX_)
		|| (reqInfo->_tmfreq < __TFTP_TMFREQ_MIN_)) {
		reqInfo->_tmfreq = __TFTP_TMFREQ_DEFAULT_;
	}
	reqInfo->_oack_opts++;
	
	/* 块大小检查，必须有该选项以匹配数据传输报文大小 */
	if ((reqInfo->_blkSize < __TFTP_BLKSIZE_128_BYTES_) 
		|| (reqInfo->_blkSize > __TFTP_BLKSIZE_8192_BYTES_)) {
		reqInfo->_blkSize = __TFTP_DEFAULT_BLKSIZE_;
	}
	reqInfo->_oack_opts++;

	/* tszie检查，必须有改选项，以确定磁盘余量 */
	if (reqInfo->_options._opt_tsize) {
		if ((reqInfo->_tSize > __TFTP_TSIZE_MAX_) 
			|| (reqInfo->_mode < __TFTP_TSIZE_MIN_)) {
			goto tftp_req_not_support_return;
		}
		reqInfo->_oack_opts++;
	}
	else {
		goto tftp_req_not_support_return;
	}

	/* bpid检查 */
	if (reqInfo->_options._opt_bpid) {
		if ((reqInfo->_bpId > __TFTP_BLKID_MAX_) 
			|| (reqInfo->_mode < __TFTP_BLKID_MIN_)) {
			goto tftp_req_not_support_return;
		}
		reqInfo->_oack_opts++;
	}

	/* 服务器不支持上传mail模式 */
	if ((tftp_Pack_Mode_mail == reqInfo->_mode)
		&& (tftp_Pack_OperCode_Wrq == reqInfo->_opcode)) {
		goto tftp_req_not_support_return;
	}
		
	return tftp_ret_Ok;
	
tftp_req_not_support_return:
	TFTP_LOGWARN("client tftp request invalid\r\n Client connect:"
			"ip:%s, port:%d, file:%s, mode:%s, blksize:%d, timeout:%d, tmfreq:%d, bpid:%d",
			inet_ntoa(cliReqInfo->_cliAddr.sin_addr),
			ntohs(cliReqInfo->_cliAddr.sin_port),
			reqInfo->_fileName ? reqInfo->_fileName  : "NULL",
			reqInfo->_pMode ? reqInfo->_pMode : "NULL",
			reqInfo->_blkSize,
			reqInfo->_timeout,
			reqInfo->_tmfreq,
			reqInfo->_bpId);
	
	return tftp_ret_NotSupport;
}

/*
 * FunctionName:
 *     tftp_server_rrq_file_init
 * Description:
 *     读请求文件初始化（存在判断、大小获取、文件打开）
 * Notes:
 *     
 */
LOCAL tftpReturnValue_t tftp_server_rrq_file_init(tftpTaskPool_t * pClient)
{
	UINT64 tsize = 0;
	INT32 fd = 0;
		
	/* 获取文件全路径 */
	memcpy(pClient->_filePath, gServerPath, strlen(gServerPath));
	strcat(pClient->_filePath, pClient->_cliInfo._reqInfo._fileName);

	/* 判断文件是否存在 */
	if (!isfileExist(pClient->_filePath))
	{
		TFTP_LOGWARN("client:%s download file %s is not exist", \
			pClient->_cliInfo._cliIpAddr, pClient->_filePath);
		return tftp_ret_NotFound;
	}

	/* 获取文件大小 */
	tsize = fileSize(pClient->_filePath);
	pClient->_cliInfo._reqInfo._tSize = tsize;
	
	/* 打开文件 */
	fd = tftp_open(pClient->_filePath, O_RDONLY);
	if (fd < 0) {
		TFTP_LOGERR("file %s open fail, errno:%d!", \
			pClient->_cliInfo._cliIpAddr, pClient->_filePath, errno);		
		tftp_perror("\r\nopen fail reason is");
		return tftp_ret_Error;
	}
	pClient->_fileFd = fd;
	pClient->_cliInfo._reqInfo._options._opt_tsize = 1;
	
	return tftp_ret_Ok;
}


/*
 * FunctionName:
 *     tftp_server_client_rrq_hanle
 * Description:
 *     读请求（下载）处理
 * Notes:
 *     
 */
LOCAL tftpReturnValue_t tftp_server_client_rrq_hanle
(
	tftpTaskPool_t * pClient
)
{
	INT32 sendLen = 0;
	INT32 recvLen = 0;
	INT32 readLen = 0;
	UINT16 ack = 0;
	UINT16 blkid = 0;
	CHAR errMsg[__TFTP_ERR_PACK_MAX_LEN_] = {0};
	UINT8 * sendBuf = NULL;
	INT32 sockFd = pClient->_sockfd;
	tftpReturnValue_t tftpRet = tftp_ret_Ok;
	UINT8 recvBuf[__TFTP_ERR_PACK_MAX_LEN_] = {0};
	tftpPacktReq_t * pReqInfo = &pClient->_cliInfo._reqInfo;
	tftpSocketInfo_t * pCliInfo = &pClient->_cliInfo;
	struct sockaddr_in * pCliAddr = &pClient->_cliInfo._cliAddr;
	INT32 blksize = pClient->_cliInfo._reqInfo._blkSize;
	
	/* 根据blksize申请内存 */
	sendBuf = malloc(blksize + __TFTP_DATA_SHIFT_);
	if (NULL == sendBuf) {
		TFTP_LOGERR("For client %s malloc send memry size:%d fail!", pCliInfo->_cliIpAddr, blksize);
		return tftp_ret_Null;
	}

	/* 下载文件则先获取文件大小，打开文件等 */
	tftpRet = tftp_server_rrq_file_init(pClient);
	if (TFTP_FAILURE(tftpRet)) {
		/* 文件没找到或者打开出错等 */
		if (tftp_ret_NotFound == tftpRet) {
			tftp_sprint(errMsg, "%s<%s>", __TFTP_ERR_FILENOTFOUED_, pReqInfo->_fileName);
			sendLen = (INT32)tftp_pack_error(sendBuf, tftp_Pack_ErrCode_AccViolate, errMsg);
		}
		else {
			tftp_sprint(errMsg, "%s<%s>", __TFTP_ERR_NOTDEFINE_, pReqInfo->_fileName);
			sendLen = (INT32)tftp_pack_error(sendBuf, tftp_Pack_ErrCode_AccViolate, errMsg);
		}
		goto tftp_rrq_err_send_ret;
	}	
	else if (pReqInfo->_tSize > __TFTP_TSIZE_MAX_) {
		/* 文件大于1G则不支持传输 */
		tftp_sprint(errMsg, "%s<%d>", __TFTP_ERR_NOTDEFINE_FILE_TOO_LARGE_, pReqInfo->_tSize);
		sendLen = (INT32)tftp_pack_error(sendBuf, tftp_Pack_ErrCode_AccViolate, errMsg);
		goto tftp_rrq_err_send_ret;
	}

	/* 回复OACK */
	sendLen = tftp_pack_oack(sendBuf, pReqInfo);
	tftp_socket_send(sockFd, sendBuf, sendLen, pCliAddr);

	/* 等待ACK/ERR和发送DATA */
	while (TRUE) {
		(VOID)memset(recvBuf, 0, __TFTP_ERR_PACK_MAX_LEN_);
		(VOID)memset(sendBuf, 0, blksize + __TFTP_DATA_SHIFT_);

		/* 接收客户端ACK/ERROR报文 */
		recvLen = tftp_socket_recv(sockFd, recvBuf, __TFTP_ERR_PACK_MAX_LEN_, pCliAddr);
		if (recvLen < 0) {
			return tftp_ret_Error;
		}
		
		switch (TFTP_GET_OPCODE(recvBuf)) {
			case __TFTP_OPCODE_ACK_:
				ack = TFTP_GET_ACK(recvBuf);
				/* 计算ACK,支持块ID复用 */
				if (blkid != ack) {
					tftp_sprint(errMsg, "%s<ack tid:%d, blkid:%d>", __TFTP_ERR_UNKNOWNTD_, ack, blkid);
					sendLen = (INT32)tftp_pack_error(sendBuf, tftp_Pack_ErrCode_UnknownId, errMsg);					
					goto tftp_rrq_err_send_ret;
				}
				blkid++;
				
				/* 读取文件 */
				readLen = tftp_read(pClient->_fileFd, sendBuf + __TFTP_DATA_SHIFT_, blksize);
				if (readLen < 0) {
					tftp_sprint(errMsg, "%s<%s>", __TFTP_ERR_NOTDEFINE_FILE_READ_FAIL_, pReqInfo->_fileName);
					sendLen = (INT32)tftp_pack_error(sendBuf, tftp_Pack_ErrCode_AccViolate, errMsg);
					goto tftp_rrq_err_send_ret;
				}
				
				/* 封装DATA数据包 */
				sendLen = readLen + (INT32)tftp_pack_data(sendBuf, blkid);
				
				/* 发送数据,并根据发送的报文大小小于blksize判断结束 */
				tftp_socket_send(sockFd, sendBuf, sendLen, pCliAddr);
				if (readLen < blksize) {
					goto tftp_rrq_ok_ret;
				}
				break;
			case __TFTP_OPCODE_ERR_:
				TFTP_LOGERR("Get client error code(%d) message(%s)", TFTP_GET_ERRCODE(recvBuf), TFTP_GET_ERRMSG(recvBuf));
				goto tftp_rrq_err_ret;
			default:
				goto tftp_rrq_err_ret;
		}
	}
tftp_rrq_ok_ret:
	TFTP_LOGNOR("client %s download file <%s> success!", pCliInfo->_cliIpAddr, pReqInfo->_fileName);
	return tftp_ret_Ok;
	
tftp_rrq_err_send_ret:
	/* 出错发送ERROR code */
	(VOID)tftp_socket_send(sockFd, sendBuf, sendLen, pCliAddr);
tftp_rrq_err_ret:
	return tftp_ret_Error;
}

/*
 * FunctionName:
 *     tftp_server_client_wrq_hanle
 * Description:
 *     写请求（上传）处理
 * Notes:
 *     
 */
LOCAL tftpReturnValue_t tftp_server_client_wrq_hanle
(
	tftpTaskPool_t * pClient
)
{
	return tftp_ret_Ok;
}

/*
 * FunctionName:
 *     tftp_server_client_resource_reset
 * Description:
 *     子线程通信相关的客户端资源清空
 * Notes:
 *     
 */
LOCAL VOID tftp_server_client_resource_reset(tftpTaskPool_t * pClient)
{
	UINT8 md5Result[64] = {0};
	
	if (pClient->_sockfd > 0) {
		tftp_close(pClient->_sockfd);
		pClient->_sockfd = -1;
	}
	if (pClient->_fileFd > 0) {
		tftp_close(pClient->_fileFd);
		pClient->_fileFd = -1;
	}
	
	(VOID)md5_algroithm(pClient->_filePath, md5Result);
	TFTP_LOGNOTE("file %s md5sum is %s",  pClient->_cliInfo._reqInfo._fileName, md5Result);	

	memset(&pClient->_cliInfo, 0, sizeof(pClient->_cliInfo));

	return;
}

/*
 * FunctionName:
 *     tftp_server_client_connect_handle
 * Description:
 *     子线程处理客户端连接的执行函数
 * Notes:
 *     
 */
VOID * tftp_server_client_connect_handle(VOID * arg)
{
	tftpPid_t tid = 0;
	struct sockaddr_in sockAddr;
	tftpTaskPool_t * pClient = NULL;
	tftpSemInfo_t * pSem = NULL;
	tftpReturnValue_t tftpRet = tftp_ret_Error;
	UINT8 errBuf[128] = {0};
	INT32 sendLen = 0;
	INT32 ret = 0;
	
	while (initSucces && gServerRun) {
		tid = tftp_task_get_tid();

		/* 获取信号量 */
		pSem = tftp_server_find_task_sem(tid);
		if (NULL == pSem) {
			TFTP_LOGERR("Error find task sync lock");
			return NULL;
		}

		/* 子线程阻塞等待同步信号量 */
		tftp_sem_wait(pSem);
		
		/* 根据线程tid获取线程信息 */
		pClient = tftp_server_get_client_info_bytid(tid);
		if (NULL == pClient) {
			TFTP_LOGERR("task pool information eror, not find task:%d", tid);
		}

		/* 为子线程创建socket，获取socket信息 */
		sockAddr.sin_family = AF_INET;
		sockAddr.sin_port = htons(pClient->_port);
		sockAddr.sin_addr.s_addr = htonl(__TFTP_SOCKET_SERVER_IP_ANY_ADDR_);
		pClient->_sockfd =	tftp_socket_create(&sockAddr, TRUE);
		if (pClient->_sockfd < 0) {
			goto tftp_child_task_over;
		}

		TFTP_LOGNOR("client %s req deal start!", pClient->_cliInfo._cliIpAddr);
			
		/* 处理连接请求...,检查请求报文基本格式 */	
		tftpRet = tftp_server_client_req_check(&pClient->_cliInfo);
		if (TFTP_FAILURE(tftpRet)) {
			/* 请求参数有错误参数，发送错误报文给客户端，错误类型为操作无效 */
			sendLen = (INT32)tftp_pack_error(errBuf, tftp_Pack_ErrCode_AccViolate, __TFTP_ERR_ILLEGALOPER_);
			(VOID)tftp_socket_send(pClient->_sockfd, errBuf, sendLen, &(pClient->_cliInfo._cliAddr));
			goto tftp_child_task_over;
		}
		
		/* 处理读请求 */
		if (__TFTP_OPCODE_RRQ_ == pClient->_cliInfo._reqInfo._opcode) {
			tftpRet = tftp_server_client_rrq_hanle(pClient);
			if (TFTP_FAILURE(tftpRet)) {
				goto tftp_child_task_over;
			}
		}
		/* 处理写请求 */
		else {
			tftpRet = tftp_server_client_wrq_hanle(pClient);
			if (TFTP_FAILURE(tftpRet)) {
				goto tftp_child_task_over;
			}
		}
		
		TFTP_LOGNOR("client %s req deal success!", pClient->_cliInfo._cliIpAddr);
		
tftp_child_task_over:
		/* 释放资源 */
		tftp_server_client_resource_reset(pClient);
		
		/* 线程忙状态修改 */
		pClient->_busy = FALSE;
	}

}

/*
 * FunctionName:
 *     tftp_server_find_free_task
 * Description:
 *     在客户端请求到来时寻找空闲线程
 * Notes:
 *     
 */
LOCAL tftpTaskPool_t * tftp_server_find_free_task(VOID)
{
	tftpTaskPoolList_t * pFind = gTaskPoolHead;

	while (pFind) {
		if (FALSE == pFind->_taskNode._busy) {
			pFind->_taskNode._busy = TRUE;
			return &(pFind->_taskNode);
		}
		pFind = pFind->_next;
	}

	/* 没找到，并且线程池没有达到最大限度，则创建新线程，之后考虑实现 */
	return NULL;
}

/*
 * FunctionName:
 *     tftp_server_task_handle
 * Description:
 *     server主任务处理函数
 * Notes:
 *     
 */
VOID * tftp_server_task_handle(VOID * argv)
{
	INT32 rv = 0;
	INT32 connfd = -1;
	struct sockaddr_in cliaddr;
	INT32 recvLen = 0;
	tftpTaskPool_t * pFind = NULL;
	CHAR buf[__TFTP_RECV_BUF_LEN_] = {0};
	tftpTaskInfo_t taskInfo;
	
	memset(&cliaddr, 0, sizeof(struct sockaddr_in));
	while (initSucces && gServerRun) {
		TFTP_LOGDBG(tftp_dbgSwitch_server, "tftp server wait client connect...");

		/* 从线程池中find一个空闲的子线程*/
		pFind = tftp_server_find_free_task();
		
		/* 阻塞recv UDP请求，有空闲子线程则处理，否则不处理，只记录日志 */
		if (pFind) {
			memset(&taskInfo, 0, sizeof(taskInfo));
			tftp_task_get_info_by_tid(pFind->_tid, &taskInfo);
			TFTP_LOGNOR("get free task:%s, tid=%d", taskInfo._name, pFind->_tid);
			
			/* 接收UDP请求信息 */
			memset(buf, 0, __TFTP_RECV_BUF_LEN_);
			recvLen = tftp_socket_recv(gListenSocket, buf, __TFTP_RECV_BUF_LEN_ - 1, &cliaddr);
			TFTP_LOGDBG(tftp_dbgSwitch_server, "socket recvfrom fd = %d, recv len = %d", gListenSocket, recvLen);
			if (recvLen >= __TFTP_REQ_PACK_BUF_LEN_ || recvLen < 0) {
				TFTP_LOGWARN("Error client %s request, recv length=%d", inet_ntoa(cliaddr.sin_addr), recvLen);
				pFind->_busy = FALSE;
				continue;
			}
			
			/* 对子线程的结构信息做初始化信息同步 */
			memcpy(&pFind->_cliInfo._cliAddr, &cliaddr, sizeof(cliaddr));			
			pFind->_cliInfo._cliPort = ntohs(cliaddr.sin_port);
			memcpy(pFind->_cliInfo._cliIpAddr, inet_ntoa(cliaddr.sin_addr), __TFTP_IP_ADDR_LEN_);
			/* 解析请求并将请求信息同步给子线程进行处理 */
			memset(&pFind->_cliInfo._reqInfo, 0, sizeof(pFind->_cliInfo._reqInfo));
			tftp_unpack_req(buf, recvLen, &pFind->_cliInfo._reqInfo);

			/* 释放同步信号量，唤醒子线程处理请求 */
			tftp_sem_post(pFind->_syncLock);	
		}
		else {
			TFTP_LOGWARN("Too many connect for tftp server, do not any deal!");
			sleep(60);
		}
	}
}

/*
 * FunctionName:
 *     tftp_server_listen_socket_init
 * Description:
 *     监听套接字创建初始化接口
 * Notes:
 *     
 */
LOCAL tftpReturnValue_t tftp_server_listen_socket_init(CHAR * ipaddr)
{
	struct sockaddr_in addr;

	TFTP_LOGDBG(tftp_dbgSwitch_server, "tftp server task listen socket create");
	
	memset(&addr, 0, sizeof(addr));
	
	addr.sin_family = AF_INET;
	addr.sin_port = htons(__TFTP_SOCKET_SERVER_UDP_PORT_);
	addr.sin_addr.s_addr = inet_addr(ipaddr);
	
	gListenSocket = tftp_socket_create(&addr, TRUE);
	if (gListenSocket < 0) {
		TFTP_LOGERR("create server socket fail!");
		return tftp_ret_Error;
	}

	return tftp_ret_Ok;
}

/*
 * FunctionName:
 *     tftp_server_pool_operator_sem
 * Description:
 *     线程池操作信号量创建
 * Notes:
 *     
 */
LOCAL tftpReturnValue_t tftp_server_pool_operator_sem(VOID)
{
	tftpReturnValue_t tftpRet = tftp_ret_Error;
	tftpSemInfo_t semInfo;
		
	TFTP_LOGDBG(tftp_dbgSwitch_server, "tftp server task pool operator sem init");
	
	memset(&semInfo, 0, sizeof(tftpSemInfo_t));

	semInfo._semTask = 0;
	semInfo._waitForever = TRUE;
	semInfo._status = tftp_semStatus_post;		
	semInfo._pshared = tftp_semShared_thread;
	memcpy(semInfo._semName, __TFTP_SEM_NAME_POOL_, __TFTP_SEM_NAME_LENGTH_);

	tftpRet = tftp_sem_create_init(&semInfo);
	if (TFTP_FAILURE(tftpRet)) {
		TFTP_LOGERR("create sem for task pool operator fail, return %s(%d)!", \
			tftp_err_msg(tftpRet), tftpRet);
		return tftp_ret_Error;
	}
	else{
		gSemPool = semInfo._semId;
	}
	return tftp_ret_Ok;
}

/*
 * FunctionName:
 *     tftp_server_task_init
 * Description:
 *     server主任务创建，负责监听套接字、管理线程池、处理通信等
 * Notes:
 *     
 */
LOCAL tftpReturnValue_t tftp_server_task_init(VOID)
{
	tftpTaskInfo_t serverTask;
	memset(&serverTask, 0, sizeof(tftpTaskInfo_t));
	
	TFTP_LOGDBG(tftp_dbgSwitch_server, "tftp server task create init");

	serverTask._pid = 0;
	serverTask._tid = 0;
	serverTask._taskStructid = 0;
	serverTask._deal_function = tftp_server_task_handle;
	serverTask._stackSize = __TFTP_SERVER_TASK_STACK_SIZE_;
	serverTask._detachState = __TFTP_TASK_DETACHED_;
	memcpy(serverTask._name, __TFTP_TASK_NAME_SERVER_, __TFTP_TASK_NAME_LENGTH_);

	gServerRun = TRUE;

	/* 初始化server任务 */
	tftp_task_create_init(&serverTask);

	return tftp_ret_Ok;
}

/*
 * FunctionName:
 *     tftp_server_task_pool_sem_create_init
 * Description:
 *     线程池读写互斥信号量初始化
 * Notes:
 *     
 */
LOCAL tftpReturnValue_t tftp_server_task_pool_sem_create_init
(
	INT32 childTaskId, 
	tftpSem_t ** pSem
)
{
	tftpReturnValue_t tftpRet = tftp_ret_Error;
	tftpSemInfo_t semInfo;
	CHAR strSemName[__TFTP_SEM_NAME_LENGTH_] = {0};
	CHAR strCliIndex[3] = {0};
		
	TFTP_LOGDBG(tftp_dbgSwitch_server, "tftp server task pool sem init");
	
	memset(&semInfo, 0, sizeof(tftpSemInfo_t));
	memset(strSemName, 0, sizeof(strSemName));
	memset(strCliIndex, 0, sizeof(strCliIndex));

	semInfo._semTask = 0;
	semInfo._waitForever = TRUE;
	/*
	 * 线程同步信号量，初始化为占用，由主线程释放，子线程开始执行 
     * 子线程执行完毕后，重新置为占用，之后再由主线程释放
	 */
	semInfo._status = tftp_semStatus_wait;		
	semInfo._pshared = tftp_semShared_thread;

	/* 指定信号量名字 */
	strcat(strSemName, __TFTP_SEM_NAME_CHILD_);
	strcat(strSemName, uitoa(childTaskId, strCliIndex));
	memcpy(semInfo._semName, strSemName, __TFTP_SEM_NAME_LENGTH_);

	tftpRet = tftp_sem_create_init(&semInfo);
	if (TFTP_FAILURE(tftpRet)) {
		TFTP_LOGERR("create sem for task pool child task fail, return %s(%d)!", \
			tftp_err_msg(tftpRet), tftpRet);
		return tftp_ret_Error;
	}
	else{
		/* malloc创建的sem内存地址，用指针传出去 */
		*pSem = semInfo._semId;
	}
	return tftp_ret_Ok;
}


/*
 * FunctionName:
 *     tftp_server_task_pool_task_create_init
 * Description:
 *     线程池任务创建初始化
 * Notes:
 *     
 */
LOCAL tftpReturnValue_t tftp_server_task_pool_task_create_init
(
	INT32 childTaskId,
	tftpTaskInfo_t * pClientTask
)
{
	CHAR strClientName[__TFTP_TASK_NAME_LENGTH_] = {0};
	CHAR strCliIndex[3] = {0};
	tftpTaskInfo_t clientTask;
	tftpReturnValue_t tftpRet = tftp_ret_Error;

	TFTP_LOGDBG(tftp_dbgSwitch_server, "tftp server task pool task init");

	memset(&clientTask, 0, sizeof(tftpTaskInfo_t));
	memset(strClientName, 0, sizeof(strClientName));
	memset(strCliIndex, 0, sizeof(strCliIndex));
	
	clientTask._pid = 0;
	clientTask._tid = 0;
	clientTask._taskStructid = 0;
	clientTask._deal_function = tftp_server_client_connect_handle;
	clientTask._stackSize = __TFTP_CLIENT_TASK_STACK_SIZE_;
	clientTask._detachState = __TFTP_TASK_DETACHED_;
	
	strcat(strClientName, __TFTP_TASK_NAME_CLIENT_);
	strcat(strClientName, uitoa(childTaskId, strCliIndex));
	memcpy(clientTask._name, strClientName, __TFTP_TASK_NAME_LENGTH_);
	
	/* 初始化client任务 */
	tftpRet = tftp_task_create_init(&clientTask);
	if (TFTP_FAILURE(tftpRet)) {
		TFTP_LOGERR("create task for task pool child task fail, return %s(%d)!", \
			tftp_err_msg(tftpRet), tftpRet);
		return tftp_ret_Error;
	}
	
	(VOID)memcpy(pClientTask, &clientTask, sizeof(tftpTaskInfo_t));
	
	return tftp_ret_Ok;
}

/*
 * FunctionName:
 *     tftp_server_task_pool_init
 * Description:
 *     线程池初始化
 * Notes:
 *     
 */
LOCAL tftpReturnValue_t tftp_server_task_pool_init(VOID)
{
	INT32 taskIndex = 0;
	tftpSem_t * clientSem = NULL;
	tftpTaskInfo_t clientTask;
	tftpTaskPoolList_t * pChildNode = NULL;
	tftpReturnValue_t tftpRet = tftp_ret_Ok;
	tftpPid_t tid = 0;
	
	TFTP_LOGDBG(tftp_dbgSwitch_server, "tftp server task pool init");

	/* 先创建线程池最小保证线程个数 */
	for (taskIndex = 0; taskIndex < __TFTP_TASK_POOL_MIN_; taskIndex++) {
		/* 为子线程创建同步信号量 */
		tftpRet = tftp_server_task_pool_sem_create_init(taskIndex, &clientSem);
		if (TFTP_FAILURE(tftpRet)) {
			TFTP_IF_ERROR(tftpRet);
			return tftp_ret_Error;
		}
		
		/* 依次创建子线程 */
		tftpRet = tftp_server_task_pool_task_create_init(taskIndex, &clientTask);
		if (TFTP_FAILURE(tftpRet)) {
			TFTP_IF_ERROR(tftpRet);
			return tftp_ret_Error;
		}

		/* 根据返回的structID获取线程tid */
		tid = tftp_task_get_tid_by_structId(clientTask._taskStructid);

		/* 创建线程池节点，将线程信息和信号量存储到线程池节点中 */
		pChildNode = tftp_server_task_pool_node_create(clientSem, tid);
		if (NULL == pChildNode) {
			TFTP_LOGERR("create node for task pool child task fail, return NULL!");
			return tftp_ret_Error;
		}

		/* 将线程所属tid保存到sem结构链表中去 */
		(VOID)tftp_sem_save_tid(clientSem, tid);
		
		/* 将节点插入线程池 */
		tftp_server_task_pool_node_insert(pChildNode);
	}
	
	return tftp_ret_Ok;
}


/*
 * FunctionName:
 *     tftp_server_cmd_enable_handle
 * Description:
 *     tftpserver启动/关闭的命令执行函数
 * Notes:
 *     
 */
LOCAL VOID tftp_server_cmd_enable_handle(INT32 argc, CHAR * argv[])
{
	tftpReturnValue_t tftpRet = tftp_ret_Error;
	
	if (0 == strcasecmp(argv[1], "enable")) {
		if (gServerRun) {
			TFTP_LOGWARN("TFTP server is running already!");
			return;
		}
	
		/* 0、服务器配置初始化,在config目录下的server.cfg文件中
		 * 在启动server之前需要保证server配置齐全
		 */
		//tftp_server_config_init();
	
		/* 1、初始化主线程用于监听连接的socket */
		tftpRet = tftp_server_listen_socket_init(argv[2]);
		if (TFTP_FAILURE(tftpRet)) {
			TFTP_IF_ERROR(tftpRet);
			return;
		}
		
		/* 2、初始化子线程线程池 */
		tftpRet = tftp_server_task_pool_init();
		if (TFTP_FAILURE(tftpRet)) {
			TFTP_IF_ERROR(tftpRet);
			return;
		}

		/* 3、创建线程池结构访问的信号量 */
		tftpRet = tftp_server_pool_operator_sem();
		if (TFTP_FAILURE(tftpRet)) {
			TFTP_IF_ERROR(tftpRet);
			return;
		}

		/* 4、创建Server线程 */
		tftpRet = tftp_server_task_init();
		if (TFTP_FAILURE(tftpRet)) {
			TFTP_IF_ERROR(tftpRet);
			return;
		}
		
		TFTP_LOGNOR("TFTP server is start!");
	}
	else if (0 == strcasecmp(argv[1], "disable")) {
		TFTP_LOGWARN("TFTP server is over!");
	}
}

/*
 * FunctionName:
 *     tftp_server_shell_command_init
 * Description:
 *     线程池display的shell命令初始化
 *     tftpserver启动/关闭的
 * Notes:
 *     
 */
LOCAL VOID tftp_server_shell_command_init(VOID)
{
	TFTP_LOGDBG(tftp_dbgSwitch_server, "tftp server module shell command register");

	tftp_shell_cmd_register((tftp_cmd_deal_fun)tftp_server_cmd_display_task_pool, 
		__TFTP_CMD_HIDE_,
		"taskpool{commuication child task pool information display}"
			"display{display some information}"
				"taskTid{display with tid}"
					"__INT32__{task tid(-1 is all)}");

	tftp_shell_cmd_register((tftp_cmd_deal_fun)tftp_server_cmd_enable_handle, 
		__TFTP_CMD_NORMAL_ | __TFTP_CMD_DYN_,
		"tftpserver{tftp server enable/disable}"
			"__STRING__{enable or disable}"
			"__IPADDR__{server ip address}");
}

/*
 * FunctionName:
 *     tftp_server_module_init
 * Description:
 *     server模块初始化接口
 * Notes:
 *     
 */
EXTERN tftpReturnValue_t tftp_server_module_init(VOID)
{
	TFTP_LOGDBG(tftp_dbgSwitch_server, "tftp server module init......");

	/* 初始化display、server注册等命令 */
	tftp_server_shell_command_init();

	/* 打开配置文件，获取服务器可下载文件路径 */
}


