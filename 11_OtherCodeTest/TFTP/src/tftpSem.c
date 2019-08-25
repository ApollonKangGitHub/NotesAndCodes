#include <tftpSem.h>
#include <tftpLog.h>
#include <tftpShell.h>
#include <tftpPublic.h>

/* 信号量管理结构链表保护信号量 */
LOCAL tftpSem_t * gSemSelf;

tftpSemInfo_t * gSelfNode = NULL;

/* 信号量链表头尾指针 */
tftpSemInfoList_t * gSemListHead = NULL;
tftpSemInfoList_t * gSemListTail = NULL;

LOCAL VOID tftp_sem_list_display(INT32 argc, CHAR * argv[])
{
	tftpSemInfoList_t * pSemInfo;
	CHAR * semName = argv[3];
	
	tftp_print("\r\n%-16s%-16s%-16s%-16s%-16s%-16s", 
		"semName", "shared", "semId", "curTask", "timeout(s:ms)", "waitForever");
	
	for (pSemInfo = gSemListHead; pSemInfo; pSemInfo = pSemInfo->_next) {
		if ((0 == strcmp(semName, pSemInfo->_semInfo._semName))
			|| (0 == strcmp(semName, "all"))) {
			tftp_print("\r\n%-16s%-16s%-16p%-16d%-7ld:%-8ld%-16s", 
				pSemInfo->_semInfo._semName,
				pSemInfo->_semInfo._pshared ? "process" : "thread", 
				pSemInfo->_semInfo._semId,
				pSemInfo->_semInfo._semTask,
				pSemInfo->_semInfo._timeout._sec, 
				pSemInfo->_semInfo._timeout._nsec * 1000,
				pSemInfo->_semInfo._waitForever ? "TRUE" : "FALSE");
		}
		if (0 == strcmp(semName, pSemInfo->_semInfo._semName)) {
			break;
		}
	} 
}

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
	tftpSem_t * semId;
	tftpSemStatus_t status = tftp_semStatus_post;			/* 默认空闲 */
	tftpSemShare_t shared = tftp_semShared_thread;			/* 默认线程间共享 */

	TFTP_LOGDBG(tftp_dbgSwitch_sem, "tftp sem create, semInfo=%p", semInfo);
	if (NULL == semInfo) {
		TFTP_LOGERR("semInfo is NULL, please check it!");
		return tftp_ret_Null;
	}

	/* 根据传参确定具体的信号量初始化状态和共享 */
	status = semInfo->_status;
	shared = semInfo->_pshared;

	/* 信号量的空间必须是全局变量或者堆上动态申请的 */
	semId = malloc(sizeof(tftpSem_t));
	
	ret = sem_init(semId, shared, status);
	if (-1 == ret) {
		TFTP_LOGERR("create sem fail, semId=%p, shared=%d, status=%d",
				semId, shared, status);
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
EXTERN INT32 tftp_sem_destroy(tftpSem_t * semId)
{
	TFTP_LOGDBG(tftp_dbgSwitch_sem, "tftp sem destroy, semId=%p", semId);
	/* 销毁前销毁结构 */
	
	return sem_destroy(semId);
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
	tftpSem_t * semId;
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
		return sem_wait(semId);
	}
	else {
		return sem_timedwait(semId, (struct timespec *)&_timeout);
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
EXTERN INT32 tftp_sem_post(tftpSem_t * semId)
{
	TFTP_LOGDBG(tftp_dbgSwitch_sem, "tftp sem post, semId=%p", semId);
	return sem_post(semId);
}

/*
 * FunctionName:
 *     tftp_sem_info_node_find
 * Description:
 *     查找信号量信息节点
 * Notes:
 *     
 */
LOCAL tftpReturnValue_t tftp_sem_info_node_find
(
	IN tftpSem_t * semId, 
	OUT tftpSemInfo_t * pSemInfo
)
{
	TFTP_LOGDBG(tftp_dbgSwitch_task, \
		"tftp sem info node find, semId=%p pSemInfo=%p", semId, pSemInfo);

	if (NULL == pSemInfo) {
		TFTP_LOGERR("Error tftp info node find for agrument, pSemInfo=%p!", pSemInfo);
		return tftp_ret_Null;
	}

	/* 遍历信号量信息链表，根据semId匹配信号量节点 */
	tftpSemInfoList_t * pHeadTemp = gSemListHead;
	for (; pHeadTemp; pHeadTemp = pHeadTemp->_next) {
		if (pHeadTemp->_semInfo._semId == semId) {
			memcpy(pSemInfo, &pHeadTemp->_semInfo, sizeof(tftpSemInfo_t));
			return tftp_ret_Ok;
		}
	}
	return tftp_ret_NotFound;
}
/*
 * FunctionName:
 *     tftp_sem_info_node_find
 * Description:
 *     创建新的信号量信息节点并初始化
 * Notes:
 *     
 */
LOCAL tftpSemInfoList_t * tftp_sem_info_node_create(IN tftpSemInfo_t * pSemInfo)
{
	CHAR * ret = NULL;
	tftpSemInfoList_t * pSemInfoCode = NULL;

	TFTP_LOGDBG(tftp_dbgSwitch_task, \
		"tftp sem info node memory create, pSemInfo=%p", pSemInfo);

	if (NULL == pSemInfo) {
		TFTP_LOGERR("Error tftp task malloc, pSemInfo=%p!", pSemInfo);
		return NULL;		
	}

	pSemInfoCode = malloc(sizeof(tftpSemInfoList_t));
	if (NULL == pSemInfoCode) {
		TFTP_LOGERR("Error tftp sem info malloc, pSemInfoCode=%p!", pSemInfoCode);
		return NULL;		
	}

	memset(pSemInfoCode, 0, sizeof(tftpSemInfoList_t));
	(VOID)memcpy(&pSemInfoCode->_semInfo, pSemInfo, sizeof(tftpSemInfoList_t));\
	pSemInfoCode->_next = pSemInfoCode->_pre = NULL;

	return pSemInfoCode;
}
/*
 * FunctionName:
 *     tftp_sem_info_node_insert
 * Description:
 *     向信号量管理链表中插入新的信号量信息节点
 * Notes:
 *     
 */
LOCAL tftpReturnValue_t tftp_sem_info_node_insert(IN tftpSemInfoList_t * PsemInfoCode)
{
	TFTP_LOGDBG(tftp_dbgSwitch_sem, \
		"tftp sem info node insert info list, PsemInfoCode:%p",PsemInfoCode);

	tftpReturnValue_t ret = tftp_ret_Error;
	if (NULL == PsemInfoCode || NULL == gSemListTail) {
		TFTP_LOGERR("Error tftp sem info insert, PsemInfoCode=%p, gSemListTail=%p!",
			PsemInfoCode, gSemListTail);
		return tftp_ret_Null;		
	}
	
	/* 写链表操作需要加锁 */
	tftp_sem_wait(gSelfNode);
	
	gSemListTail->_next = PsemInfoCode;
	PsemInfoCode->_pre = gSemListTail;
	PsemInfoCode->_next = NULL;
	gSemListTail = PsemInfoCode;

	/* 写完释放锁 */
	tftp_sem_post(gSemSelf);
	
 	return tftp_ret_Ok;
}

/*
 * FunctionName:
 *     tftp_sem_create_init
 * Description:
 *     创建指定信号量并保存
 * Notes:
 *     
 */
EXTERN tftpReturnValue_t tftp_sem_create_init
(
	IN OUT tftpSemInfo_t * pSemInfo
)
{
	INT32 ret = 0;
	tftpSemInfo_t semInfo;
	tftpSemInfoList_t * pSelfNode;

	TFTP_LOGDBG(tftp_dbgSwitch_sem, "tftp sem create and init, semInfo=%p", semInfo);		
	if (NULL == pSemInfo) {
		TFTP_LOGERR("Error tftp sem create init, pSemInfo=%p!",  pSemInfo);
		return tftp_ret_Null;		
	}	
	
	memset(&semInfo, 0, sizeof(tftpSemInfo_t));
	semInfo._semTask = pSemInfo->_semTask;
	semInfo._waitForever = pSemInfo->_waitForever;
	semInfo._status = pSemInfo->_status;
	semInfo._pshared = pSemInfo->_pshared;
	semInfo._timeout._nsec = pSemInfo->_timeout._nsec;
	semInfo._timeout._sec = pSemInfo->_timeout._sec;
	memcpy(semInfo._semName, pSemInfo->_semName, __TFTP_SEM_NAME_LENGTH_);

	ret = tftp_sem_create(&semInfo);
	if (-1 == ret) {
		TFTP_LOGERR("create sem for %s fail!", pSemInfo->_semName);
		return tftp_ret_Error;
	}
	else {
		pSemInfo->_semId = semInfo._semId;
	}
	
	pSelfNode = tftp_sem_info_node_create(&semInfo);
	if (NULL == pSelfNode) {
		TFTP_LOGERR("create sem info code for self fail!");
		return tftp_ret_Error;
	}
	tftp_sem_info_node_insert(pSelfNode);
	
	return tftp_ret_Ok;
}

/*
 * FunctionName:
 *     tftp_sem_module_List_init
 * Description:
 *     信号量管理模块初始化
 * Notes:
 *     
 */
LOCAL tftpReturnValue_t tftp_sem_module_List_init(VOID)
{
	tftpReturnValue_t ret = 0;
	tftpSemInfo_t semInfo;
	tftpSemInfoList_t * pSelfNode;
	
	memset(&semInfo, 0, sizeof(tftpSemInfo_t));
	
	TFTP_LOGDBG(tftp_dbgSwitch_sem, "tftp sem init for self and create sem list");
	
	semInfo._semTask = 0;
	semInfo._waitForever = TRUE;
	semInfo._status = tftp_semStatus_post;
	semInfo._pshared = tftp_semShared_thread;
	semInfo._timeout._nsec = 0;
	semInfo._timeout._sec = 0;
	memcpy(semInfo._semName, __TFTP_SEM_NAME_SLEF_, __TFTP_SEM_NAME_LENGTH_);

	ret = tftp_sem_create(&semInfo);
	if (-1 == ret) {
		TFTP_LOGERR("create sem for self info list fail!");
		return tftp_ret_Error;
	}
	else{
		gSemSelf = semInfo._semId;
	}

	pSelfNode = tftp_sem_info_node_create(&semInfo);
	if (NULL == pSelfNode) {
		TFTP_LOGERR("create sem info code for self fail!");
		return tftp_ret_Error;
	}

	/* 信号量头结点，初始化完成后，最少有了这一个节点 */
	pSelfNode->_next = pSelfNode->_pre = NULL;
	gSemListHead = gSemListTail = pSelfNode;
	
	gSelfNode = &(pSelfNode->_semInfo);
	
	return tftp_ret_Ok;	
}

/*
 * FunctionName:
 *     tftp_sem_shell_command_init
 * Description:
 *     信号量相关的shell命令初始化
 * Notes:
 *     
 */
LOCAL VOID tftp_sem_shell_command_init(VOID)
{
	TFTP_LOGDBG(tftp_dbgSwitch_server, "tftp server module shell command register");

	tftp_shell_cmd_register((tftp_cmd_deal_fun)tftp_sem_list_display, 
		__TFTP_CMD_HIDE_,
		"sem{semaphore information display}"
			"display{display some information with sem}"
				"name{display with sem name}"
					"__STRING__{sem name('all' or special name)}");
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
	TFTP_LOGNOR("tftp semaphore module init......");
	
	tftp_sem_module_List_init();
	tftp_sem_shell_command_init();
	return tftp_ret_Ok;
}
