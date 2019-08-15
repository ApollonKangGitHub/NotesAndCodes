#include <tftpSem.h>
#include <tftpLog.h>
#include <tftpPublic.h>

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

EXTERN INT32 tftp_sem_destroy(tftpSem_t semId)
{
	TFTP_LOGDBG(tftp_dbgSwitch_sem, "tftp sem destroy, semId=%d", semId);
	return sem_destroy(&semId);
}

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

EXTERN INT32 tftp_sem_post(tftpSem_t semId)
{
	TFTP_LOGDBG(tftp_dbgSwitch_sem, "tftp sem post, semId=%d", semId);
	return sem_post(&semId);
}
