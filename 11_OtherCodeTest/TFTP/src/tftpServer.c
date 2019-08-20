#include <tftpServer.h>
#include <tftpType.h>
#include <tftpSem.h>
#include <tftpLog.h>

#include <tftpPublic.h>

/*
 * FunctionName:
 *     tftp_server_child_task_create
 * Description:
 *     线程池通信子任务创建
 * Notes:
 *     
 */
LOCAL tftpReturnValue_t tftp_server_child_task_create(VOID)
{

}

/*
 * FunctionName:
 *     tftp_server_child_sem_create
 * Description:
 *     线程池通信子任务互斥信号量初始化
 * Notes:
 *     
 */
LOCAL tftpReturnValue_t tftp_server_child_sem_create(VOID)
{

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

}

/*
 * FunctionName:
 *     tftp_server_task_pool_sem_init
 * Description:
 *     线程池读写互斥信号量初始化
 * Notes:
 *     
 */
LOCAL tftpReturnValue_t tftp_server_task_pool_sem_init(VOID)
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
	/* 初始化主线程中保存通信子线程的线程池结构 */
	tftp_server_task_pool_init();

	/* 初始化访问线程池的互斥信号量 */
	tftp_server_task_pool_sem_init();

	/* 初始化主线程用于监听连接的socket */
	tftp_server_listen_socket_init();
}


