#include <tftpType.h>
#include <tftpTask.h>
#include <tftpLog.h>
#include <tftpPublic.h>

/*
 * Linux查看系统中某进程正在运行的线程:
 * 以TFTP.exe为例：
 * ps -aux | grep TFTP.exe获取到<pid>
 * ps -T -p <pid>即可查看对应进程的线程
 */

tftpTaskInfoList_t * gTaskInfoHead = NULL;
tftpTaskInfoList_t * gTaskInfoTail = NULL;

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
	tftpTaskInfoList_t * pInfoTemp = NULL;
	UINT8 taskNum = 0;
	
	TFTP_LOGDBG(tftp_dbgSwitch_task, \
		"tftp task info code insert, taskInfoCode=%p, taskName:%s, tid:%lld", 
			taskInfoCode, taskInfoCode->_taskInfo._name, taskInfoCode->_taskInfo._tid);

	if (NULL == taskInfoCode) {
		TFTP_LOGERR("Error tftp task info insert, taskInfo=%p!", taskInfoCode);
		return tftp_ret_Null;		
	}

	if (NULL == gTaskInfoHead) {
		/* 头指针和尾指针初始化 */
		taskInfoCode->_taskNum = 1;
		taskInfoCode->_taskId = __TFTP_TASK_ID_START_;
		taskInfoCode->_next = taskInfoCode->_pre = NULL;
		gTaskInfoHead = gTaskInfoTail = taskInfoCode;

		taskNum = gTaskInfoHead->_taskNum;
	}
	else {
		/* 尾插法，插入新节点,头指针不动,尾指针修改,
		 * 修改前根据当前尾结点为新的尾结点赋值
		 */
		taskInfoCode->_taskNum = 1;
		taskInfoCode->_taskId = gTaskInfoTail->_taskId + 1;
		taskInfoCode->_next = NULL;
		taskInfoCode->_pre = gTaskInfoTail;
		gTaskInfoTail->_next = taskInfoCode;
		gTaskInfoTail = taskInfoCode;

		taskNum = gTaskInfoHead->_taskNum + 1;
	}
	
	TFTP_LOGDBG(tftp_dbgSwitch_task, "taskId:%d, taskNum:%d, taskName:%s!",
		gTaskInfoTail->_taskId, taskNum, gTaskInfoTail->_taskInfo._name);

	/* 每插入一次，_taskNum对于头结点增加一次，所有节点更新一次 */	
	pInfoTemp = gTaskInfoHead;
	while (pInfoTemp) {
		pInfoTemp->_taskNum = taskNum;
		pInfoTemp = pInfoTemp->_next;
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

	TFTP_LOGDBG(tftp_dbgSwitch_task, \
		"tftp task info memory create, taskInfo=%p", taskInfo);

	if (NULL == taskInfo) {
		TFTP_LOGERR("Error tftp task malloc, pTask=%p!", taskInfo);
		return NULL;		
	}

	pTaskInfoCode = malloc(sizeof(tftpTaskInfoList_t));
	if (NULL == pTaskInfoCode) {
		TFTP_LOGERR("Error tftp task malloc, pTask=%p!", pTaskInfoCode);
		return NULL;		
	}

	memset(pTaskInfoCode, 0, sizeof(tftpTaskInfoList_t));
	
	(VOID)memcpy(&pTaskInfoCode->_taskInfo, taskInfo, sizeof(tftpTaskInfo_t));
	pTaskInfoCode->_next = NULL;
	pTaskInfoCode->_pre = NULL;
	pTaskInfoCode->_taskNum = 0;
	pTaskInfoCode->_taskId = 0;
	
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
	
	TFTP_LOGDBG(tftp_dbgSwitch_task, \
		"tftp task create init, taskInfo=%p", taskInfo);
	
	if (NULL == taskInfo) {
		TFTP_LOGERR("Error argument taskInfo:%p!", taskInfo);
		return tftp_ret_Null;		
	}
	
	ret = pthread_attr_init(&attr);
	if (ret != 0) {
		TFTP_LOGERR("Error task attr init, ret = %d!", ret);
		return tftp_ret_Error;
	}	

	/* 设置分离态PTHREAD_CREATE_DETACHED */
	ret = pthread_attr_setdetachstate(&attr, taskInfo->_detachState);
	if (ret != 0) {
		TFTP_LOGERR("Error set task attr detach state, ret = %d!", ret);
		return tftp_ret_Error;
	}

	/* 设置线程栈大小 */
	ret = pthread_attr_setstacksize(&attr, taskInfo->_stackSize);
	if (ret != 0) {
		TFTP_LOGERR("Error set task attr stack size, ret = %d!", ret);
		return tftp_ret_Error;
	}

	/* 创建线程 */
	ret = pthread_create(&tid, &attr, taskInfo->_deal_function, NULL);
	if (ret != 0) {
		TFTP_LOGERR("Error create task, ret = %d!", ret);
		return tftp_ret_Error;
	}

	/* 保存线程ID */
	taskInfo->_tid = tid;
	
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
	CHAR taskName[__TFTP_TASK_NAME_LENGTH_] = {__TFTP_TASK_NAME_MAIN_};

	TFTP_LOGDBG(tftp_dbgSwitch_task, "tftp task module init");

	memset(&mainTask, 0, sizeof(mainTask));

	/* 设置主线程名字 */
	tftp_task_set_name(__TFTP_TASK_NAME_MAIN_);

	ret = pthread_attr_init(&attr);
	if (ret != 0) {
		TFTP_LOGERR("Error task attr init, ret = %d!", ret);
		return tftp_ret_Error;
	}	

	/* 获取主任务线程栈大小 */
	ret = pthread_attr_getstacksize(&attr, (size_t*)&stackSize);
	if (ret != 0) {
		TFTP_LOGERR("Error get task attr stack size, ret = %d!", ret);
		return tftp_ret_Error;
	}
	
	/* 获取主任务分离属性 */
	ret = pthread_attr_getdetachstate(&attr, &detachState);
	if (ret != 0) {
		TFTP_LOGERR("Error get task attr detach state, ret = %d!", ret);
		return tftp_ret_Error;
	}

	/* 获取主线程ID, always succeeds. */
	tid = pthread_self();

	mainTask._tid = tid;
	mainTask._stackSize = stackSize;
	mainTask._detachState = detachState;
	(VOID)strncpy(mainTask._name, taskName, __TFTP_TASK_NAME_LENGTH_);

	ret = pthread_attr_destroy(&attr);
	if (ret != 0) {
		TFTP_LOGERR("Error destroy task attr, ret = %d!", ret);
		return tftp_ret_Error;
	}

	/* 创建信息保存节点 */
	pTaskInfo = tftp_task_info_create(&mainTask);
	if (NULL == pTaskInfo) {
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
EXTERN INT64 tftp_task_get_tid(VOID)
{
	TFTP_LOGDBG(tftp_dbgSwitch_task, "tftp task get tid");
	
	return pthread_self();\
}

/*
 * FunctionName:
 *     tftp_task_destroy
 * Description:
 *     
 * Notes:
 *     
 */
EXTERN tftpReturnValue_t tftp_task_destroy(tftpTid_t tid)
{
	UINT8 retTask[128] = {0};
	INT32 ret = -1;
	tftpTaskInfo_t taskInfo;
	
	memset(&taskInfo, 0, sizeof(tftpTaskInfo_t));
	
	TFTP_LOGDBG(tftp_dbgSwitch_task, \
		"tftp task destroy, tid=%lld", tid);
	
	ret = tftp_task_get_info_by_tid(tid, &taskInfo);
	if (ret != -1) {
		//TFTP_LOGWARN("Task:%s[%lld] was destroy success!", taskInfo._name, taskInfo._tid);
		/* 此处应该是直接结束，由主线程监听子线程销毁并清空对应数据结构 */
		//(VOID)pthread_exit((VOID*)&retTask);
	}
	else {
		TFTP_LOGWARN("Task is %lld want to destroy, But not success!", tid);
	}
	
	return tftp_ret_Ok;
}

/*
 * FunctionName:
 *     tftp_task_get_info
 * Description:
 *     获取指定局部taskId的任务信息
 * Notes:
 *     
 */
EXTERN INT32 tftp_task_get_info
(
	INT32 taskId,
	tftpTaskInfo_t * taskInfo
)
{
	tftpTaskInfoList_t * pTaskInfo = NULL;

	TFTP_LOGDBG(tftp_dbgSwitch_task, \
		"tftp task get info by taskId, taskId=%d", taskId);
	
	if (NULL == taskInfo) {
		TFTP_LOGERR("Error argument taskInfo:%p,taskName:%p!", taskInfo);
		return -1;		
	}	
	
	for (pTaskInfo = gTaskInfoHead; pTaskInfo; pTaskInfo = pTaskInfo->_next) {
		if (pTaskInfo->_taskId == taskId) {
			TFTP_LOGDBG(tftp_dbgSwitch_task, "taskId:%d, _taskId:%d, _taskNum:%d!", \
				taskId, pTaskInfo->_taskId, pTaskInfo->_taskNum);
			
		 	memcpy(taskInfo, &pTaskInfo->_taskInfo, sizeof(tftpTaskInfo_t));
			return pTaskInfo->_taskNum;
		}
	}

	return -1;
}

/*
 * FunctionName:
 *     tftp_task_get_info_by_tid
 * Description:
 *     获取指定tid的任务信息
 * Notes:
 *     
 */
EXTERN INT32 tftp_task_get_info_by_tid
(
	tftpTid_t tid, 
	tftpTaskInfo_t * taskInfo
)
{
	tftpTaskInfoList_t * pTaskInfo = NULL;

	TFTP_LOGDBG(tftp_dbgSwitch_task, \
		"tftp task get info by task tid, tid=%p", tid);
	
	if (NULL == taskInfo) {
		TFTP_LOGERR("Error argument taskInfo:%p!", taskInfo);
		return -1;		
	}	
	
	for (pTaskInfo = gTaskInfoHead; pTaskInfo; pTaskInfo = pTaskInfo->_next) {
		if (tid == pTaskInfo->_taskInfo._tid) {
		 	memcpy(taskInfo, &pTaskInfo->_taskInfo, sizeof(tftpTaskInfo_t));
			return pTaskInfo->_taskId;;
		}
	}

	return -1;
}

/*
 * FunctionName:
 *     tftp_task_get_info_by_name
 * Description:
 *     
 * Notes:
 *     
 */
EXTERN INT32 tftp_task_get_info_by_name
(
	CHAR * taskName, 
	tftpTaskInfo_t * taskInfo
)
{
	tftpTaskInfoList_t * pTaskInfo = NULL;

	TFTP_LOGDBG(tftp_dbgSwitch_task, \
		"tftp task get info by task name, taskName=%s", taskName ? taskName : "Invalid");
	
	if (NULL == taskInfo || NULL == taskName) {
		TFTP_LOGERR("Error argument taskInfo:%p,taskName:%p!", taskInfo, taskName);
		return -1;		
	}	
	
	for (pTaskInfo = gTaskInfoHead; pTaskInfo; pTaskInfo = pTaskInfo->_next) {
		if (0 == strncmp(pTaskInfo->_taskInfo._name, taskName,  __TFTP_TASK_NAME_LENGTH_)) {
		 	memcpy(taskInfo, &pTaskInfo->_taskInfo, sizeof(tftpTaskInfo_t));
			return pTaskInfo->_taskId;
		}
	}

	return -1;
}



