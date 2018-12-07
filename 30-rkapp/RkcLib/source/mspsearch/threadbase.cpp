#include "stdall.h"
#include "threadbase.h"
#ifdef _LINUX_
    #include <unistd.h>
	#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <cerrno>
#else
	#include "process.h"
#endif

CThreadBase::CThreadBase(void)
{
#ifdef WIN32
	m_hExitHandle = NULL;
	m_hStopHandle = NULL;
#else
	pthread_cond_t cv;
	m_hExitHandle = pthread_cond_init(&cv, NULL);
	pthread_cond_t cv1;
	m_hStopHandle = pthread_cond_init(&cv1, NULL);
#endif
	m_hTheadHandle = NULL;
	m_uTheadId = 0;
	m_bThreadSus = false;
}

CThreadBase::~CThreadBase(void)
{
#ifdef WIN32
	SetEvent(m_hExitHandle);
	//关闭事件核心对象
	if(m_hExitHandle)
	{
		::CloseHandle(m_hExitHandle);
		m_hExitHandle = NULL;
	}
	if(m_hStopHandle)
	{
		::CloseHandle(m_hStopHandle);
		m_hStopHandle = NULL;
	}
#else
	if (m_hExitHandle)
	{
		close(m_hExitHandle);
		m_hExitHandle = NULL;
	}

	if(m_hStopHandle)
	{
		close(m_hStopHandle);
		m_hStopHandle = NULL;
	}
#endif
}

bool CThreadBase::Start(void* pParam, PFunRun pfun)
{
	if(m_hTheadHandle != NULL)
		return true;

#ifdef _LINUX_
	pthread_t tid;
	m_hTheadHandle  = pthread_create(&tid, NULL, (void* (*)(void*))pfun, pParam);
	if (m_hTheadHandle != NULL)
	{
        printf("create thread failed ,error:[%s]\n", strerror(errno));
		return false;
	}

#else
	if (m_hExitHandle == NULL)
	{
		//创建同步事件对象-退出事件
		m_hExitHandle=CreateEvent( NULL, // 事件属性
			true,  // 是否手动设置
			false, // 是否有信号,有信号立刻执行，无信号等待激活
			NULL); // 事件名称
	}

	if(NULL == m_hStopHandle)
	{
		m_hStopHandle = CreateEvent(NULL, true, false, NULL);
	}

	ResetEvent(m_hStopHandle);
	ResetEvent(m_hExitHandle);

	if(m_hTheadHandle == NULL)
	{
		m_hTheadHandle	= (HANDLE)_beginthreadex(NULL, 0, *pfun, pParam, 0, &m_uTheadId);
		if (m_hTheadHandle ==  NULL)
		{
			//TraceDebug("begingthread faild");
			return false;
		}
	}
#endif
	
	return true;
}

bool CThreadBase::Suspend()
{
#ifdef WIN32
	if(m_hTheadHandle)
	{
		SuspendThread(m_hTheadHandle);
		m_bThreadSus = true;
		//TraceInfo("CBaseThread::Pause() Handle == %d", m_hTheadHandle);
		return true;
	}
#endif

	return false;
}

bool CThreadBase::Resume()
{
#ifdef WIN32
	if(m_hTheadHandle)
	{
		ResumeThread(m_hTheadHandle);
		m_bThreadSus = false; 
		//TraceInfo("CBaseThread::Resume() Handle == %d", m_hTheadHandle);
		return true;
	}
#endif

	return false;
}

bool CThreadBase::Exit()
{
#ifdef WIN32

	::SetEvent(m_hStopHandle);
	if(WAIT_OBJECT_0 != ::WaitForSingleObject(m_hExitHandle , 100) && m_hTheadHandle != NULL)
	{
		::TerminateThread(m_hTheadHandle, -1);
	}
	if(m_hTheadHandle)
	{
		//TraceInfo("CBaseThread::Exit() m_hTheadHandle == %d", m_hTheadHandle);
		CloseHandle(m_hTheadHandle);
		m_hTheadHandle = NULL;
	}

	if(m_hExitHandle)
	{
		//TraceInfo("CBaseThread::Exit() m_hExitHandle == %d", m_hTheadHandle);
		CloseHandle(m_hExitHandle);
		m_hExitHandle = NULL;
	}

	if(m_hStopHandle)
	{
		//TraceInfo("CBaseThread::Exit() m_hStopHandle == %d", m_hStopHandle);
		CloseHandle(m_hStopHandle);
		m_hStopHandle = NULL;
	}


#else
	if (m_hExitHandle)
	{
		close(m_hExitHandle);
		m_hExitHandle = NULL;
	}

	if(m_hStopHandle)
	{
		close(m_hStopHandle);
		m_hStopHandle = NULL;
	}
#endif

	return true;
}

bool CThreadBase::IsRuning()
{
	return (m_hTheadHandle != NULL);
}

bool CThreadBase::IsSuspend()
{
	return m_bThreadSus;
}

// 判断线程是否退出
bool CThreadBase::IsExit(void)
{
#ifdef WIN32
	DWORD dr=::WaitForSingleObject(m_hExitHandle,//事件对象
		0   //时间，INFINITE无限等待，单位毫秒
		);
	if(dr==WAIT_OBJECT_0)//有信号
	{
		return true;
	}
	else if(dr==WAIT_TIMEOUT)//超时
	{
	} 
	else if(dr=WAIT_FAILED)  //意外处理
	{
	}
	else
	{
	}
#endif
	return false;
}




