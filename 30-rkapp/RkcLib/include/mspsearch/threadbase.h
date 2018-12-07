#pragma once

#ifdef WIN32
#ifndef CALLBACKRET
#define  CALLBACKRET   u32
#endif // !CALLBACKRET
#else
#ifndef CALLBACKRET
#define  CALLBACKRET   void
#endif // !CALLBACKRET
#endif

typedef CALLBACKRET(STDCALL *PFunRun)(void* ptr);

class CThreadBase
{
public:
	CThreadBase(void);
	~CThreadBase(void);

public:
#ifdef WIN32
	HANDLE m_hExitHandle;
	HANDLE m_hStopHandle;
	HANDLE m_hTheadHandle;
#else 
	u32	m_hExitHandle;
	u32 m_hStopHandle;
	u32 m_hTheadHandle;
#endif


	unsigned m_uTheadId;
	bool    m_bThreadSus;

public:
	bool Start(void* pParam, PFunRun pfun);
	bool Suspend();
	bool Resume();
	bool Exit();
	bool IsRuning();
	bool IsSuspend();
	bool IsExit(void);
};


