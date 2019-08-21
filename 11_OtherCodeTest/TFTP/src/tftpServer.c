#include <tftpServer.h>
#include <tftpType.h>
#include <tftpSem.h>
#include <tftpLog.h>
#include <tftpSocket.h>

#include <tftpPublic.h>

/* 在Server初始化时赋值为TRUE，Server结束时赋值为FALSE */
LOCAL BOOL gServerRun = FALSE;
tftpTaskPoolList_t * gTaskPoolHead = NULL;
tftpTaskPoolList_t * gTaskPoolTail = NULL;
INT32 gListenSocket = 0;

/*
 * FunctionName:
 *     tftp_task_pool_cli_sem_create
 * Description:
 *     线程池通信子任务互斥信号量初始化
 * Notes:
 *     
 */
LOCAL tftpReturnValue_t tftp_task_pool_cli_sem_create(VOID)
{

}

/*
 * FunctionName:
 *     tftp_client_connect_handle
 * Description:
 *     子线程处理客户端连接的执行函数
 * Notes:
 *     
 */
VOID * tftp_client_connect_handle(VOID * arg)
{

}

/*
 * FunctionName:
 *     tftp_task_pool_init
 * Description:
 *     线程池初始化
 * Notes:
 *     
 */
LOCAL tftpReturnValue_t tftp_task_pool_init(VOID)
{
	INT32 taskIndex = 0;
	CHAR strClientName[__TFTP_TASK_NAME_LENGTH_] = {0};
	CHAR strCliIndex[3] = {0};
	tftpTaskInfo_t clientTask;
	
	/* 先创建线程池最小保证线程个数 */
	for (taskIndex = 0; taskIndex < __TFTP_TASK_POOL_MIN_; taskIndex++) {
		memset(&clientTask, 0, sizeof(tftpTaskInfo_t));
		memset(strClientName, 0, sizeof(strClientName));
		memset(strCliIndex, 0, sizeof(strCliIndex));
		
		clientTask._pid = 0;
		clientTask._tid = 0;
		clientTask._taskStructid = 0;
		clientTask._deal_function = tftp_client_connect_handle;
		clientTask._stackSize = __TFTP_CLIENT_TASK_STACK_SIZE_;
		clientTask._detachState = __TFTP_TASK_DETACHED_;

		strcat(strClientName, __TFTP_TASK_NAME_CLIENT_);
		strcat(strClientName, uitoa(taskIndex + 1, strCliIndex));
		strncpy(clientTask._name, strClientName, __TFTP_TASK_NAME_LENGTH_);

		/* 初始化client任务 */
		tftp_task_create_init(&clientTask);
	}
	
	return tftp_ret_Ok;
}

/*
 * FunctionName:
 *     tftp_task_pool_sem_init
 * Description:
 *     线程池读写互斥信号量初始化
 * Notes:
 *     
 */
LOCAL tftpReturnValue_t tftp_task_pool_sem_init(VOID)
{

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

VOID * tftp_server_task_deal(VOID * argv)
{
	while (gServerRun) {
		sleep(1);
	}
}

/*
 * FunctionName:
 *     tftp_server_task_init
 * Description:
 *     server主任务创建，负责监听套接字、管理线程池、处理通信等
 * Notes:
 *     
 */
LOCAL INT32 tftp_server_task_init(VOID)
{
	tftpTaskInfo_t serverTask;
	memset(&serverTask, 0, sizeof(tftpTaskInfo_t));

	serverTask._pid = 0;
	serverTask._tid = 0;
	serverTask._taskStructid = 0;
	serverTask._deal_function = tftp_server_task_deal;
	serverTask._stackSize = __TFTP_SERVER_TASK_STACK_SIZE_;
	serverTask._detachState = __TFTP_TASK_DETACHED_;
	strncpy(serverTask._name, __TFTP_TASK_NAME_SERVER_, __TFTP_TASK_NAME_LENGTH_);

	gServerRun = TRUE;

	/* 初始化server任务 */
	tftp_task_create_init(&serverTask);

	return tftp_ret_Ok;
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

	/* 初始化主线程用于监听连接的socket */
	TFTP_IF_ERROR_RET(tftp_server_listen_socket_init());

	/* 创建Server线程 */
	TFTP_IF_ERROR_RET(tftp_server_task_init());

	/* 初始化子线程线程池 */
	TFTP_IF_ERROR_RET(tftp_task_pool_init());

	TFTP_IF_ERROR_RET(tftp_task_pool_sem_init());
}


