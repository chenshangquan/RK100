/*****************************************************************************
ģ����      : rkclib�ӿ�
�ļ���      : rkcsysctrlif.h
����ļ�    : 
�ļ�ʵ�ֹ���: rkc����
����        : Ҷ��ƽ
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
2018/10/23   1.0         Ҷ��ƽ        ����
******************************************************************************/
#ifndef __RKCCONFIGCTRLIF_H__
#define __RKCCONFIGCTRLIF_H__

#include "kdvdispevent.h"

class CRkcConfigCtrlIF : public CKdvDispEvent
{
public:
    /**
	*   �����豸
	*/ 
    virtual u16 ReBootRk() = 0;

    /**
	*   �ָ���������
	*/ 
    virtual u16 RestoreRk(TRK100LoginInfo tRK100LoginInfo) = 0;

    /**
	*   ��ȡ����ģʽ����
	*/ 
    virtual u16 GetWorkModeConfig() = 0;
	/**
	*   ��ȡ����ģʽ��������
	*/
    virtual u16 GetWorkModeConfig(TRK100WorkMode& tRK100WorkMode) = 0;

    /**
	*   �޸Ĺ���ģʽ����
	*/ 
    virtual u16 SetWorkModeConfig(TRK100WorkMode tRK100WorkMode) = 0;

    /**
	*   ��ȡ����������Ϣ
	*/ 
    virtual u16 GetNetWorkConfig() = 0;
    /**
	*   ��ȡ������������
	*/
    virtual u16 GetNetWorkConfig(TRK100NetParam& tRK100NetParam) = 0;

    /**
	*   �޸Ĺ���ģʽ����
	*/ 
    virtual u16 SetNetWorkConfig(TRK100NetParam tRK100NetParam) = 0;

    /**
	*   ��ȡ��������
	*/ 
    virtual u16 SetFtpUpdateFirst(TRK100TftpFwUpdate tRK100TftpFwUpdate) = 0;
    /**
	*   ��ȡ��������
	*/ 
    virtual u16 SetFtpUpdateSecond() = 0;
    /**
	*   ��ȡ��������
	*/ 
    virtual u16 GetUpdateConfig(TRK100UpdateHead& tRK100UpdateHead) = 0;

    /**
	*   ��ȡ��Դ����
	*/ 
    virtual u16 GetPowerConfig() = 0;
    /**
	*   ��ȡ��Դ��������
	*/
    virtual u16 GetPowerConfig(TRK100PowerInfo& tRK100PowerInfo) = 0;

    /**
	*   ��ȡ����ģʽ
	*/ 
    virtual u16 GetDebugConfig() = 0;
    /**
	*   ��ȡ����ģʽ����
	*/
    virtual u16 GetDebugConfig(TRK100DebugMode& tRK100DebugInfo) = 0;
    /**
	*   ���õ���ģʽ����
	*/
    virtual u16 SetDebugConfig(TRK100DebugMode tRK100DebugInfo) = 0;
};

#endif __RKCSYSCTRLIF_H__