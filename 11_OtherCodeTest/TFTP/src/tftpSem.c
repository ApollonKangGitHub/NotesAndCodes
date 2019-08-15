#include <tftpSem.h>
#include <tftpLog.h>
#include <tftpPublic.h>

/* 信号量管理结构链表保护信号量 */
LOCAL tftpSem_t gSemSelf;

/* 信号量链表头尾指针 */
tftpSemInfoList_t * gSemListHead = NULL;
tftpSemInfoList_t * gSemListTail = NULL;

/*
 * FunctionName:
 *     tftp_sem_create
 * Description:
 *     创建指定信号量
 * Notes:
 *     
 */
EXTERN tftpReturnValue_t tftp_sem_create(tftpSemInfo_t * semInfo)
{
	INT32 ret = 0;
	tftpSem_t semId;
	tftpSemStatus_t status = tftp_semStatus_post;	/* 默认空闲 */
	tftpSemShare_t shared = tftp_semShared_thread;			/* 默认线程间共享 */

	TFTP_LOGDBG(tftp_dbgSwitch_sem, "tftp sem create, semInfo=%p", semInfo);
	if (NULL == semInfo) {
		TFTP_LOGERR("semInfo is NULL, please check it!");
		return tftp_ret_Null;
	}
	
	ret = sem_init(&semId, shared, status);
	if (-1 == ret) {
		TFTP_LOGERR("create sem fail!");
		tftp_perror("Error and Over!");
		return tftp_ret_Error;
	}

	semInfo->_semId = semId;
	return tftp_ret_Ok;
}
/*
 * FunctionName:
 *     tftp_sem_destroy
 * Description:
 *     销毁指定信号量
 * Notes:
 *     
 */
EXTERN INT32 tftp_sem_destroy(tftpSem_t semId)
{
	TFTP_LOGDBG(tftp_dbgSwitch_sem, "tftp sem destroy, semId=%d", semId);
	/* 销毁前销毁结构 */
	
	return sem_destroy(&semId);
}
/*
 * FunctionName:
 *     tftp_sem_wait
 * Description:
 *     获取信号量
 * Notes:
 *     
 */
EXTERN INT32 tftp_sem_wait(tftpSemInfo_t * semInfo)
{
	tftpSem_t semId;
	BOOL waitForever = FALSE;
	struct timeval time;
	tftpSemTimeout_t _timeout;
	
	TFTP_LOGDBG(tftp_dbgSwitch_sem, "tftp sem wait, semInfo=%p", semInfo);

	semId = semInfo->_semId;
	waitForever = semInfo->_waitForever;
	
	gettimeofday(&time, NULL);
    _timeout._sec = time.tv_sec + semInfo->_timeout._sec;
    _timeout._nsec = time.tv_usec + (semInfo->_timeout._nsec * 1000);
	
	if (waitForever) {
		return sem_wait(&semId);
	}
	else {
		return sem_timedwait(&semId, (struct timespec *)&_timeout);
	}
}
/*
 * FunctionName:
 *     tftp_sem_post
 * Description:
 *     释放信号量
 * Notes:
 *     
 */
EXTERN INT32 tftp_sem_post(tftpSem_t semId)
{
	TFTP_LOGDBG(tftp_dbgSwitch_sem, "tftp sem post, semId=%d", semId);
	return sem_post(&semId);
}

/*
 * FunctionName:
 *     tftp_sem_module_List_create
 * Description:
 *     信号量管理模块初始化
 * Notes:
 *     
 */
LOCAL tftpReturnValue_t tftp_sem_create_code(VOID)
{
	return tftp_ret_Ok;
}
/*
 * FunctionName:
 *     tftp_sem_module_List_create
 * Description:
 *     信号量管理模块初始化
 * Notes:
 *     
 */
LOCAL tftpReturnValue_t tftp_sem_insrt_code(VOID)
{
 return tftp_ret_Ok;
}
/*
 * FunctionName:
 *     tftp_sem_module_List_create
 * Description:
 *     信号量管理模块初始化
 * Notes:
 *     
 */
tftpReturnValue_t tftp_sem_module_List_create(VOID)
{
	tftpSem_t semId;
	INT32 ret = 0;
	tftpSemInfo_t semInfo;
	memset(&semInfo, 0, sizeof(tftpSem_t));
	
	TFTP_LOGDBG(tftp_dbgSwitch_sem, "tftp sem init for self and create sem list");
	
	semInfo._semTask = 0;
	semInfo._waitForever = TRUE;
	semInfo._status = tftp_semStatus_post;
	semInfo._pshared = tftp_semShared_thread;
	memcpy(semInfo._semName, __TFTP_SEM_NAME_SLEF_, __TFTP_SEM_NAME_LENGTH_);

	ret = tftp_sem_create(&semInfo);
	if (-1 == ret) {
		TFTP_LOGERR("create sem for self info list fail!");
		return tftp_ret_Error;
	}
	else{
		gSemSelf = semInfo._semId;
	}

	tftp_sem_create_code();

	tftp_sem_insrt_code();
	
	return tftp_ret_Ok;

	
}

/*
 * FunctionName:
 *     tftp_sem_module_init
 * Description:
 *     信号量管理模块初始化
 * Notes:
 *     
 */
EXTERN tftpReturnValue_t tftp_sem_module_init(VOID)
{	
	TFTP_LOGDBG(tftp_dbgSwitch_sem, "tftp sem init for self");
	
	tftp_sem_module_List_create();
	
	return tftp_ret_Ok;
}