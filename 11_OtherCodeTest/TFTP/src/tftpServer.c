#include <tftpServer.h>
#include <tftpType.h>
#include <tftpSem.h>
#include <tftpLog.h>
#include <tftpSocket.h>
#include <tftpShell.h>

#include <tftpPublic.h>

/* 在Server初始化时赋值为TRUE，Server结束时赋值为FALSE */
LOCAL BOOL gServerRun = FALSE;
tftpTaskPoolList_t * gTaskPoolHead = NULL;
tftpTaskPoolList_t * gTaskPoolTail = NULL;
INT32 gListenSocket = 0;
LOCAL tftpSem_t * gSemPool;

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
			tftp_print("\r\n----commucation child task name:%s----", taskInfo._name);
			tftp_print("\r\n\t%-16s:%u", "client IP", ntohl(pTaskNode->_cliInfo._cliAddr.sin_addr.s_addr));
			tftp_print("\r\n\t%-16s:%d", "client UDP port", ntohs(pTaskNode->_cliInfo._cliAddr.sin_port));
			tftp_print("\r\n\t%-16s:%d", "socket fd", pTaskNode->_cliInfo._sockId);
			tftp_print("\r\n\t%-16s:%s", "file Name", pTaskNode->_cliInfo._fileName);
			tftp_print("\r\n\t%-16s:%d", "file fd", pTaskNode->_cliInfo._fileFd);
			tftp_print("\r\n\t%-16s:%u", "file size", pTaskNode->_cliInfo._tSize);
			tftp_print("\r\n\t%-16s:%u", "block size", pTaskNode->_cliInfo._blkSize);
			tftp_print("\r\n\t%-16s:%u", "break point id", pTaskNode->_cliInfo._bpId);
			tftp_print("\r\n\t%-16s:%u", "timout", pTaskNode->_cliInfo._timeout);
			tftp_print("\r\n\t%-16s:%u", "opcode", pTaskNode->_cliInfo._opcode);
			tftp_print("\r\n\t%-16s:%u", "task bind port", pTaskNode->_port);
			tftp_print("\r\n\t%-16s:%u", "task tid", pTaskNode->_tid);
			tftp_print("\r\n\t%-16s:%s", "task busy status", pTaskNode->_busy ? "BUSY" : "FREE");
			tftp_print("\r\n\t%-16s:%p", "sync lock", pTaskNode->_syncLock);
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
	tftpPid_t tid,
	UINT16 port
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
	pPoolNode->_taskNode._port = port;
	
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
	while (gServerRun) {
		/* 子线程阻塞等待同步信号量 */

		/* 处理连接请求 */

		/* 处理完毕后释放信号量，清空线程信息 */
	}

}

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
	INT32 connfd = -1;
	struct sockaddr_in cliaddr;
	tftpTaskPool_t * pFind = NULL;
	CHAR buf[__TFTP_RECV_BUF_LEN_] = {0};
	INT32 rv = 0;
	
	memset(&cliaddr, 0, sizeof(struct sockaddr_in));
	while (gServerRun) {
		TFTP_LOGDBG(tftp_dbgSwitch_server, "tftp server wait client connect...");

		/* 从线程池中find一个空闲的子线程*/
		pFind = tftp_server_find_free_task();
		TFTP_LOGDBG(tftp_dbgSwitch_server, \
			"get free task = %p, tid=%d", pFind, pFind ? pFind->_tid : -1);
		
		/* 阻塞recv UDP请求，有空闲子线程则，处理，否则不处理，只记录日志 */
		if (pFind) {
			/* 接收UDP请求信息 */
			rv = tftp_socket_recv(gListenSocket, buf, __TFTP_RECV_BUF_LEN_, &cliaddr);
			TFTP_LOGDBG(tftp_dbgSwitch_server, \
				"socket recvfrom fd = %d return %s(%d)", gListenSocket, tftp_err_msg(rv), rv);

			/* 对子线程的结构信息做初始化信息同步 */
			memcpy(&pFind->_cliInfo._cliAddr, &cliaddr, sizeof(cliaddr));			
		
			/* 释放同步信号量，唤醒子线程处理链接 */
			tftp_sem_post(pFind->_syncLock);	
		}
		else {
			TFTP_LOGWARN("Too many connect for tftp server, do not any deal!");
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
LOCAL tftpReturnValue_t tftp_server_listen_socket_init(VOID)
{
	struct sockaddr_in addr;

	TFTP_LOGDBG(tftp_dbgSwitch_server, "tftp server task listen socket create");
	
	memset(&addr, 0, sizeof(addr));
	
	addr.sin_family = AF_INET;
	addr.sin_port = htons(__TFTP_SERVER_SOCKET_UDP_PORT_);
	addr.sin_addr.s_addr = __TFTP_SERVER_IP_ADDR_;
	
	gListenSocket = tftp_socket_create(&addr);
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
	tftpReturnValue_t ret = tftp_ret_Error;
	tftpSemInfo_t semInfo;
		
	TFTP_LOGDBG(tftp_dbgSwitch_server, "tftp server task pool operator sem init");
	
	memset(&semInfo, 0, sizeof(tftpSemInfo_t));

	semInfo._semTask = 0;
	semInfo._waitForever = TRUE;
	semInfo._status = tftp_semStatus_post;		
	semInfo._pshared = tftp_semShared_thread;
	memcpy(semInfo._semName, __TFTP_SEM_NAME_POOL_, __TFTP_SEM_NAME_LENGTH_);

	ret = tftp_sem_create_init(&semInfo);
	if (tftp_ret_Ok != ret) {
		TFTP_LOGERR("create sem for task pool operator fail, return %s(%d)!", tftp_err_msg(ret), ret);
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
	tftpReturnValue_t ret = tftp_ret_Error;
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

	ret = tftp_sem_create_init(&semInfo);
	if (tftp_ret_Ok != ret) {
		TFTP_LOGERR("create sem for task pool child task fail, return %s(%d)!", tftp_err_msg(ret), ret);
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
	tftpReturnValue_t ret = tftp_ret_Error;

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
	ret = tftp_task_create_init(&clientTask);
	if (ret != tftp_ret_Ok) {
		TFTP_LOGERR("create task for task pool child task fail, return %s(%d)!", tftp_err_msg(ret), ret);
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
	tftpPid_t tid = 0;
	
	TFTP_LOGDBG(tftp_dbgSwitch_server, "tftp server task pool init");

	/* 先创建线程池最小保证线程个数 */
	for (taskIndex = 0; taskIndex < __TFTP_TASK_POOL_MIN_; taskIndex++) {
		/* 为子线程创建同步信号量 */
		TFTP_IF_ERROR_RET(tftp_server_task_pool_sem_create_init(taskIndex, &clientSem));
		
		/* 依次创建子线程 */
		TFTP_IF_ERROR_RET(tftp_server_task_pool_task_create_init(taskIndex, &clientTask));

		/* 根据返回的structID获取线程tid */
		tid = tftp_task_get_tid_by_structId(clientTask._taskStructid);

		/* 创建线程池节点，将线程信息和信号量存储到线程池节点中 */
		pChildNode = tftp_server_task_pool_node_create(clientSem, tid, \
						taskIndex + __TFTP_CLIENT_SOCKET_UDP_PORT_MIN_);
		if (NULL == pChildNode) {
			TFTP_LOGERR("create node for task pool child task fail, return NULL!");
			return tftp_ret_Error;
		}

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
	if (0 == strcmp(argv[1], "enable")) {
		if (gServerRun) {
			TFTP_LOGWARN("TFTP server is running already!");
			return;
		}
		
		/* 初始化主线程用于监听连接的socket */
		TFTP_IF_ERROR_RET(tftp_server_listen_socket_init());

		/* 初始化子线程线程池 */
		TFTP_IF_ERROR_RET(tftp_server_task_pool_init());

		/* 创建线程池结构访问的信号量 */
		TFTP_IF_ERROR_RET(tftp_server_pool_operator_sem());

		/* 创建Server线程 */
		TFTP_IF_ERROR_RET(tftp_server_task_init());
		TFTP_LOGNOR("TFTP server is start!");
	}
	else if (0 == strcmp(argv[1], "disable")) {
		TFTP_LOGWARN("TFTP server is over!");
	}
}

/*
 * FunctionName:
 *     tftp_server_cmd_ip_set
 * Description:
 *     设置tftp server ip地址，默认为INADDR_ANY
 * Notes:
 *     
 */
LOCAL VOID tftp_server_cmd_ip_set(INT32 argc, CHAR * argv[])
{
	tftp_print("\r\nset ip address:%s", argv[2]);
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
			"__STRING__{enable or disable}");

	tftp_shell_cmd_register((tftp_cmd_deal_fun)tftp_server_cmd_ip_set, 
		__TFTP_CMD_NORMAL_ | __TFTP_CMD_DYN_,
		"tftpserverip{tftp server ip address operator}"
			"set{set tftp server ip address}"
			 	"__IPADDR__{string of ip address(eg:192.168.1.100)}");
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
	TFTP_LOGNOR("tftp server module init......");

	/* 初始化display、server注册等命令 */
	tftp_server_shell_command_init();

	/* 打开配置文件，获取服务器可下载文件路径 */
}


