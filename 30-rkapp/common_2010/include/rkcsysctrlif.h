/*****************************************************************************
ģ����      : rkclib�ӿ�
�ļ���      : rkcsysctrlif.h
����ļ�    : 
�ļ�ʵ�ֹ���: rkc����
����        : Ҷ��ƽ
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
2018/8/30   1.0         Ҷ��ƽ        ����
******************************************************************************/
#ifndef __RKCSYSCTRLIF_H__
#define __RKCSYSCTRLIF_H__

#include "kdvdispevent.h"

class CRkcSysCtrlIF : public CKdvDispEvent
{
public:
    /**
	*   Socket����
	*/ 
    virtual u16 SocketConnect(s8* pchIP, u32 dwPort) = 0;
    /**
	*   Socket�Ͽ�
	*/ 
    virtual u16 CloseSocket() = 0;
    /**
	*   ������Ϣ
	*/ 
    virtual u16 SendLoginReq(TRK100LoginInfo tRK100LoginInfo) = 0;
    /**
	*   �ж��Ƿ��¼
	*/ 
    virtual bool IsLoginState() = 0;
    /**
	*   �����޸�����������Ϣ
	*/ 
    virtual u16 SendModifyPasswordReq(TRK100LoginInfo tRK100LoginInfo) = 0;
    /**
	*   ��õ�¼����Ϣ��������
	*/ 
    virtual u16 GetLoginBackInfo(TRK100MsgHead& tRK100MsgHead) = 0;
    /**
	*   TFTP���
	*/ 
    virtual bool OpenTftp() = 0;
    virtual bool CloseTftp() = 0;
    virtual bool SetTftpPath(const s8 *pchPath) = 0;
    virtual bool SetDhcpBootFile(const s8 *pchPath) = 0;
    virtual bool KillTftpProcess() = 0;
	
};

#endif __RKCSYSCTRLIF_H__