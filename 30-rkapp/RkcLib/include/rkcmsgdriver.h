/*=======================================================================
ģ����      : RKC����̨
�ļ���      : rckmsgdriver.h
����ļ�    : 
�ļ�ʵ�ֹ���: RCK��Ϣ������
����        : Ҷ��ƽ
-------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����

=======================================================================*/
#ifndef RKCMSGDRIVER_H
#define RKCMSGDRIVER_H

#include <vector>
#include "kdvdispevent.h"
#include "ospmsg.h"
#include "eventoutrkcentre.h"
#include "crkmessage.h"

#define     AID_RKC_APP     100

class CRkcMsgDriver
{
public:
    CRkcMsgDriver();
    ~CRkcMsgDriver();

    // �õ�������Ϣ��ָ��
    COspMsg* GetOspMsgPtr(BOOL32 bClear = TRUE);
    // ע��һ��������Ϣ�����ָ��
    void RegHandler(CKdvDispEvent* const pDispEvnet);
    // ����osp��Ϣ
    virtual u16 PostMsg(u32 dwType = TYPE_CMESSAGE);

public:
    static CRkcMsgDriver *s_pMsgDriver;

    // ��ӦWM_OSPMESSAGECOMING��Ϣ
    void OnOspMessageComing(WPARAM wParam, LPARAM lParam);

protected:
    COspMsg m_tOspMsg;                      //osp������Ϣ
private:
    void MappingEventName();

    vector<CKdvDispEvent*> m_vpDispEvent;   // ��Ϣ�ַ���

};


#endif //RKCMSGDRIVER_H
