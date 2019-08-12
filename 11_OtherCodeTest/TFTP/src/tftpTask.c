#include <tftpType.h>
#include <tftpTask.h>
#include <tftpLog.h>
#include <tftpPublic.h>


tftpTaskInfoList_t * gTaskInfo = NULL;

/*
 * FunctionName:
 *     tftp_task_info_insert
 * Description:
 *     
 * Notes:
 *     
 */
LOCAL tftpReturnValue_t tftp_task_info_insert(tftpTaskInfoList_t * taskInfoCode)
{
	tftpTaskInfoList_t * pInfoHead = NULL;
	
	TFTP_LOGDBG(tftp_dbgSwitch_task, "tftp task info code insert, taskInfoCode=%p", taskInfoCode);

	if(NULL == taskInfoCode)
	{
		TFTP_LOGERR("Error tftp task info insert, taskInfo=%p!", taskInfoCode);
		return tftp_ret_Null;		
	}

	if(NULL == gTaskInfo)
	{
		/* 头指针初始化 */
		gTaskInfo = taskInfoCode;
	}
	else
	{
		/* 头插法插入新节点 */
		taskInfoCode->_next = gTaskInfo;
		gTaskInfo = taskInfoCode;
	}

	return tftp_ret_Ok;
}


/*
 * FunctionName:
 *     tftp_task_info_create
 * Description:
 *     
 * Notes:
 *     
 */
LOCAL tftpTaskInfoList_t * tftp_task_info_create(tftpTaskInfo_t * taskInfo)
{
	CHAR * ret = NULL;
	tftpTaskInfoList_t * pTaskInfoCode = NULL;

	TFTP_LOGDBG(tftp_dbgSwitch_task, "tftp task info memory create, taskInfo=%p", taskInfo);

	if(NULL == taskInfo)
	{
		TFTP_LOGERR("Error tftp task malloc, pTask=%p!", taskInfo);
		return NULL;		
	}

	pTaskInfoCode = malloc(sizeof(tftpTaskInfoList_t));
	if(NULL == pTaskInfoCode)
	{
		TFTP_LOGERR("Error tftp task malloc, pTask=%p!", pTaskInfoCode);
		return NULL;		
	}
	
	(VOID)memcpy(&pTaskInfoCode->_taskInfo, taskInfo, sizeof(tftpTaskInfo_t));
	pTaskInfoCode->_next = NULL;
	
	return pTaskInfoCode;
}

/*
 * FunctionName:
 *     tftp_task_create_init
 * Description:
 *     
 * Notes:
 *     
 */
EXTERN tftpReturnValue_t tftp_task_create_init(tftpTaskInfo_t * taskInfo)
{
	INT32 ret = 0;
	pthread_t tid;
	pthread_attr_t attr;
	tftpTaskInfoList_t * pTaskInfoCode = NULL;
	
	TFTP_LOGDBG(tftp_dbgSwitch_task, "tftp task create init, taskInfo=%p", taskInfo);
	
	if(NULL == taskInfo)
	{
		TFTP_LOGERR("Error argument taskInfo:%p!", taskInfo);
		return tftp_ret_Null;		
	}
	
	ret = pthread_attr_init(&attr);
	if(ret != 0){
		TFTP_LOGERR("Error task attr init, ret = %d!", ret);
		return tftp_ret_Error;
	}	

	/* 设置分离态PTHREAD_CREATE_DETACHED */
	ret = pthread_attr_setdetachstate(&attr, taskInfo->_detachState);
	if(ret != 0){
		TFTP_LOGERR("Error set task attr detach state, ret = %d!", ret);
		return tftp_ret_Error;
	}

	/* 设置线程栈大小 */
	ret = pthread_attr_setstacksize(&attr, taskInfo->_stackSize);
	if(ret != 0){
		TFTP_LOGERR("Error set task attr stack size, ret = %d!", ret);
		return tftp_ret_Error;
	}

	/* 创建线程 */
	ret = pthread_create(&tid, &attr, taskInfo->_deal_function, NULL);
	if(ret != 0){
		TFTP_LOGERR("Error create task, ret = %d!", ret);
		return tftp_ret_Error;
	}

	/* 保存线程ID */
	taskInfo->_id = tid;
	
	/* 销毁线程属性结构,重新初始化之前不能使用 */
	ret = pthread_attr_destroy(&attr);
	if(ret != 0){
		TFTP_LOGERR("Error destroy task attr, ret = %d!", ret);
		return tftp_ret_Error;
	}

	/* 线程创建成功，保存线程信息 */
	pTaskInfoCode = tftp_task_info_create(taskInfo);
	tftp_task_info_insert(pTaskInfoCode);
	
	return tftp_ret_Ok;
}

/*
 * FunctionName:
 *     tftp_task_module_init
 * Description:
 *     任务模块初始化，主要创建保存任务结构体的链表，第一个任务为主线程
 * Notes:
 *     
 */
EXTERN tftpReturnValue_t tftp_task_module_init(VOID)
{
	INT32 stackSize;
	INT32 detachState;
	pthread_t tid;
	pthread_attr_t attr;
	tftpTaskInfo_t mainTask;
	tftpTaskInfoList_t * pTaskInfo = NULL;	
	tftpReturnValue_t ret = tftp_ret_Error;
	
	TFTP_LOGDBG(tftp_dbgSwitch_task, "tftp task module init");

	memset(&mainTask, 0, sizeof(mainTask));
	
	ret = pthread_attr_init(&attr);
	if(ret != 0){
		TFTP_LOGERR("Error task attr init, ret = %d!", ret);
		return tftp_ret_Error;
	}	

	/* 获取主任务线程栈大小 */
	ret = pthread_attr_getstacksize(&attr, (size_t*)&stackSize);
	if(ret != 0){
		TFTP_LOGERR("Error get task attr stack size, ret = %d!", ret);
		return tftp_ret_Error;
	}
	
	/* 获取主任务分离属性 */
	ret = pthread_attr_getdetachstate(&attr, &detachState);
	if(ret != 0){
		TFTP_LOGERR("Error get task attr detach state, ret = %d!", ret);
		return tftp_ret_Error;
	}

	/* 获取主线程ID, always succeeds. */
	tid = pthread_self();

	mainTask._id = tid;
	mainTask._stackSize = stackSize;
	mainTask._detachState = detachState;
	(VOID)strncpy(mainTask._name, "tftpMainTask", strlen("tftpMainTask"));

	ret = pthread_attr_destroy(&attr);
	if(ret != 0){
		TFTP_LOGERR("Error destroy task attr, ret = %d!", ret);
		return tftp_ret_Error;
	}

	/* 创建信息保存节点 */
	pTaskInfo = tftp_task_info_create(&mainTask);
	if(NULL == pTaskInfo)
	{
		TFTP_LOGERR("Error create task info, pTaskHead = %d!", pTaskInfo);
		return tftp_ret_Error;
	}

	tftp_task_info_insert(pTaskInfo);
	
	return tftp_ret_Ok;
}

/*
 * FunctionName:
 *     tftp_task_destroy
 * Description:
 *     
 * Notes:
 *     
 */
EXTERN tftpReturnValue_t tftp_task_destroy(tftpTaskInfo_t * taskInfo)
{
	TFTP_LOGDBG(tftp_dbgSwitch_task, "tftp task destroy, taskInfo=%p", taskInfo);

}

/*
 * FunctionName:
 *     tftp_task_get_info
 * Description:
 *     
 * Notes:
 *     
 */
EXTERN tftpReturnValue_t tftp_task_get_info(INT32 tid, tftpTaskInfo_t * taskInfo)
{
	tftpTaskInfoList_t * pTaskInfo = NULL;

	TFTP_LOGDBG(tftp_dbgSwitch_task, "tftp task get info, tid=%p", tid);
	
	if(NULL == taskInfo)
	{
		TFTP_LOGERR("Error argument taskInfo:%p!", taskInfo);
		return tftp_ret_Null;		
	}	
	
	for(pTaskInfo = gTaskInfo; pTaskInfo; pTaskInfo = pTaskInfo->_next)
	{
		if(tid == pTaskInfo->_taskInfo._id)
		{
		 	memcpy(taskInfo, &pTaskInfo->_taskInfo, sizeof(tftpTaskInfo_t));
			return tftp_ret_Ok;
		}
	}

	return tftp_ret_NotFound;
}

