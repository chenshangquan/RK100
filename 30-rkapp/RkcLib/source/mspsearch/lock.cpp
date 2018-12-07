/*****************************************************************************
模块名  : Lock.h 
文件名  : Lock.h 
相关文件：
实现功能：各种锁定义入口
作者    ：
版本    ：IPC-V7.0-R1.0 Copyright (C) 2009 - 2012 All Rights Reserved
-----------------------------------------------------------------------------
修改记录:
日  期        版本        修改人        走读人    修改内容
2017/03/21    1.0  
******************************************************************************/

#include "stdall.h"
#include "lock.h"

#ifdef _LINUX_
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#endif //_LINUX_
#ifdef _MSC_VER

#endif	// _MSC_VER


#ifdef _LINUX_

typedef struct
{
	pthread_cond_t m_tCond;
	pthread_mutex_t m_tMutex;
	s32 m_dwCurrentCount;
	u32 m_dwMaxCount;
}TCond;

#endif

void schlck::CLock::LockTst(SEMHANDLE& sem)
{
    schlck::creaelock(sem);
	printf("sem ==  %d\n", (int)sem);
	printf("start\n");
	int nTmp = 0;
	while(nTmp < 100)
	{
        schlck::lock(sem);

		printf("run %d\n", nTmp++);
	}
	printf("end\n");
	destroylock(sem);
}


bool schlck::lock(SEMHANDLE& semhandle, u32 dwTimeout)
{
	int nRet = 0;
#ifdef _MSC_VER
	if( WAIT_FAILED == WaitForSingleObject(semhandle, dwTimeout) ){ int nRet = 1;}
#else
	if (NULL == semhandle)
    {
        return false;
    }
    TCond* pTCond = (TCond* )semhandle;
    
    struct timeval now;
    struct timespec timeout;
    gettimeofday(&now, NULL);

    timeout.tv_sec = now.tv_sec + dwTimeout/1000;
    int nTime = dwTimeout%1000;
    if(now.tv_usec+nTime*1000>=1000000) 
    {
        timeout.tv_sec++;
        timeout.tv_nsec = (now.tv_usec+nTime*1000-1000000)*1000;
    }
    else
    {
        timeout.tv_nsec = (now.tv_usec + nTime*1000) * 1000;
    }

	u32 dwCycleTimes = 0;
	pthread_mutex_lock( &pTCond->m_tMutex );
    while( pTCond->m_dwCurrentCount <= 0 )
    {
    	nRet = pthread_cond_timedwait( &pTCond->m_tCond, &pTCond->m_tMutex, &timeout );
    	if( 138 == nRet 
#ifdef _DM365_
            ||pTCond->m_dwCurrentCount >0
#endif            
            )
		{
				break;
    	}
		if( pTCond->m_dwCurrentCount <= 0 
#ifdef _DM365_
            &&dwCycleTimes < 10
#endif        
            )
		{
			dwCycleTimes++;
		}
#ifdef _DM365_
        else
            break;
#endif            
    }

    if( 0 == nRet )
    {
        if(pTCond->m_dwCurrentCount > 0)
        {        
    	    pTCond->m_dwCurrentCount--;
        }
    }
    pthread_mutex_unlock( &pTCond->m_tMutex );
#endif

	return ( 0 == nRet );
}
bool schlck::unlock(SEMHANDLE& semhandle)
{
	int nRet = 0;
#ifdef _MSC_VER
	DWORD previous;
	if(!ReleaseSemaphore(semhandle, 1, (LPLONG)&previous)){nRet = 1;}
#else
	if (NULL == semhandle)
    {
        return false;
    }
    TCond* pTCond = (TCond* )semhandle;
    
    pthread_mutex_lock( &pTCond->m_tMutex );
    if( pTCond->m_dwMaxCount > pTCond->m_dwCurrentCount )
    {
        if( 0 == pthread_cond_signal( &pTCond->m_tCond ) )
		{
		    nRet = 0;
		}
		else
		{
		    nRet = 1;
		}
    }
    else
    {
		   	nRet = 2;
    }
    if( 0 == nRet )
    {
    	pTCond->m_dwCurrentCount++;
    }
    pthread_mutex_unlock( &pTCond->m_tMutex );
#endif

	return ( 0 == nRet );
}
bool schlck::creaelock(SEMHANDLE& semhandle)
{
	semhandle = NULL;

#ifdef _MSC_VER
	semhandle = CreateSemaphore(NULL, 1, 1, NULL);
	if (semhandle == NULL)
	{return false;	 }
#else
	TCond* pTCond = ( TCond* )malloc(sizeof(TCond));
	if (pTCond == NULL)
	{
		return false;
	}

	pthread_cond_init(&pTCond->m_tCond, NULL);
	pthread_mutex_init(&pTCond->m_tMutex, NULL);
	pTCond->m_dwCurrentCount = 1;
	pTCond->m_dwMaxCount = 1;
	semhandle = (SEMHANDLE)pTCond;

#endif
	SCHSLEEP(30);
	//TraceDebug("creaelock lock ok %s\n", "123");
	return true;
}
bool schlck::destroylock(SEMHANDLE& semhandle)
{
#ifdef _MSC_VER    
	return (bool)CloseHandle(semhandle);
#else
	 if (NULL == semhandle)
    {
        return false;
    }
    
    TCond* pTCond = (TCond* )semhandle;
    pthread_cond_destroy( &pTCond->m_tCond );
    pthread_mutex_destroy( &pTCond->m_tMutex );
    free(pTCond);
#endif
	semhandle = NULL;

	
	return true;
}