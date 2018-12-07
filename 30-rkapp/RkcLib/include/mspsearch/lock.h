/*****************************************************************************
ģ����  : Lock.h
�ļ���  : Lock.h
����ļ���
ʵ�ֹ��ܣ��������������
����    ��
�汾    ��IPC-V7.0-R1.0 Copyright (C) 2009 - 2012 All Rights Reserved
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��        �汾        �޸���        �߶���    �޸�����
2017/03/21				  					����
******************************************************************************/
#ifndef LOCK_H
#define LOCK_H


#ifdef _LINUX_
#include <sys/sem.h>
#include <pthread.h>
#endif 



#ifndef SEMHANDLE
#ifdef _LINUX_
#define SEMHANDLE			 pthread_cond_t*
#endif	// _LINUX_
#ifdef _MSC_VER
#define SEMHANDLE			 HANDLE
#endif	// _MSC_VER
#endif

#ifdef _LINUX_
#define INFINITE			 0xFFFFFFFF
#endif	// _LINUX_

namespace schlck{
    bool lock(SEMHANDLE& semhandle, u32 dwTimeout = INFINITE);
    bool unlock(SEMHANDLE& semhandle);
    bool creaelock(SEMHANDLE& semhandle);
    bool destroylock(SEMHANDLE& semhandle);

    // ��
    class CLock
    {
    public:
        CLock(SEMHANDLE &semhandle, int nTimeOut = INFINITE) :m_semhandle(semhandle)
        {
            lock(m_semhandle, nTimeOut);
        }

        virtual ~CLock(void)
        {
            unlock(m_semhandle);
        }

        static void LockTst(SEMHANDLE& sem);

    protected:
        SEMHANDLE m_semhandle;
    };

    class CLockObject
    {
    public:
        CLockObject()
        {
            creaelock(m_semhandle);
        }

        virtual ~CLockObject(void)
        {
            destroylock(m_semhandle);
        }

        SEMHANDLE &GetLockObj(){ return m_semhandle; }

    protected:
        SEMHANDLE m_semhandle;
    };

}

#endif
