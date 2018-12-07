#pragma once
#include "StdAfx.h"
#include "rkcSessionCtrlIF.h"
#include "rkcmsgdriver.h"

class CRkcSession : public CRkcSessionCtrlIF,
                    public CRkcMsgDriver
{
public:
    CRkcSession();
    ~CRkcSession();

    //��ȡ�ӿ� 
    virtual u16 RkcGetInterface(CRkcSysCtrlIF **ppCtrl);
    virtual u16 RkcGetInterface(CRkcConfigCtrlIF **ppCtrl);
    virtual u16 RkcGetInterface(CRkcSearchCtrlIF **ppCtrl);

protected:
    // ��ʼ��OSP 
    u16 InitializeOsp();

    virtual void DispEvent(const CMessage &cMsg);
    virtual void OnTimeOut(u16 wEvent);

private:
    BOOL32 m_bInitOsp;

    // ����������ӿ���
    CRkcSysCtrlIF  *m_pSysCtrlIf;
    CRkcConfigCtrlIF  *m_pConfigCtrlIf;
    CRkcSearchCtrlIF  *m_pSearchCtrlIf;

};

