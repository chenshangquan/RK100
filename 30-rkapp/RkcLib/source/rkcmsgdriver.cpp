#include "stdafx.h"
#include "rkcmsgdriver.h"
#include "rkcmsgrecver.h"
#include "rkcprintctrl.h"

CRkcMsgDriver* CRkcMsgDriver::s_pMsgDriver = NULL;

CRkcMsgDriver::CRkcMsgDriver()
{
    // 构造事件名称表
    MappingEventName();
    s_pMsgDriver = this;
}

CRkcMsgDriver::~CRkcMsgDriver()
{
}

COspMsg* CRkcMsgDriver::GetOspMsgPtr(BOOL32 bClear)
{
    if (bClear) 
    {
        ZeroMemory(&m_tOspMsg, sizeof(COspMsg));
    }

    return &m_tOspMsg;
}
//注册一个处理消息的类的指针
void CRkcMsgDriver::RegHandler(CKdvDispEvent* const pDispEvnet)
{
    m_vpDispEvent.push_back(pDispEvnet);
}

void CRkcMsgDriver::MappingEventName()
{
    RKCMAPPING_HELPER( RK100_EVT_LOGIN, _T("RK100_EVT_LOGIN") );
    RKCMAPPING_HELPER( RK100_EVT_LOGIN_ACK, _T("RK100_EVT_LOGIN_ACK") );

    RKCMAPPING_HELPER( RK100_EVT_SET_PASSWORD, _T("RK100_EVT_SET_PASSWORD") );
    RKCMAPPING_HELPER( RK100_EVT_SET_PASSWORD_ACK, _T("RK100_EVT_SET_PASSWORD_ACK") );

    RKCMAPPING_HELPER( RK100_EVT_GET_BRD_INFO, _T("RK100_EVT_GET_BRD_INFO") );
    RKCMAPPING_HELPER( RK100_EVT_GET_BRD_INFO_ACK, _T("RK100_EVT_GET_BRD_INFO_ACK") );

    RKCMAPPING_HELPER( RK100_EVT_SET_BRD_INFO, _T("RK100_EVT_SET_BRD_INFO") );
    RKCMAPPING_HELPER( RK100_EVT_SET_BRD_INFO_ACK, _T("RK100_EVT_SET_BRD_INFO_ACK") );

    RKCMAPPING_HELPER( RK100_EVT_GET_BRD_INFO, _T("RK100_EVT_GET_BRD_INFO") );
    RKCMAPPING_HELPER( RK100_EVT_GET_BRD_INFO_ACK, _T("RK100_EVT_GET_BRD_INFO_ACK") );

    RKCMAPPING_HELPER( RK100_EVT_REBOOT, _T("RK100_EVT_REBOOT") );
    RKCMAPPING_HELPER( RK100_EVT_REBOOT_ACK, _T("RK100_EVT_REBOOT_ACK") );

    RKCMAPPING_HELPER( RK100_EVT_TFTP_UPDATE_FIRST, _T("RK100_EVT_TFTP_UPDATE_FIRST") );
    RKCMAPPING_HELPER( RK100_EVT_TFTP_UPDATE_FIRST_ACK, _T("RK100_EVT_TFTP_UPDATE_FIRST_ACK") );

    RKCMAPPING_HELPER( RK100_EVT_TFTP_UPDATE_SECOND, _T("RK100_EVT_TFTP_UPDATE_SECOND") );
    RKCMAPPING_HELPER( RK100_EVT_TFTP_UPDATE_SECOND_ACK, _T("RK100_EVT_TFTP_UPDATE_SECOND_ACK") );

    RKCMAPPING_HELPER( RK100_EVT_GET_NETPARAM, _T("RK100_EVT_GET_NETPARAM") );
    RKCMAPPING_HELPER( RK100_EVT_GET_NETPARAM_ACK, _T("RK100_EVT_GET_NETPARAM_ACK") );

    RKCMAPPING_HELPER( RK100_EVT_SET_NETPARAM, _T("RK100_EVT_SET_NETPARAM") );
    RKCMAPPING_HELPER( RK100_EVT_SET_NETPARAM_ACK, _T("RK100_EVT_SET_NETPARAM_ACK") );

    RKCMAPPING_HELPER( RK100_EVT_RESTORE, _T("RK100_EVT_RESTORE") );
    RKCMAPPING_HELPER( RK100_EVT_RESTORE_ACK, _T("RK100_EVT_RESTORE_ACK") );

    RKCMAPPING_HELPER( RK100_EVT_GET_WORK_MODE, _T("RK100_EVT_GET_WORK_MODE") );
    RKCMAPPING_HELPER( RK100_EVT_GET_WORK_MODE_ACK, _T("RK100_EVT_GET_WORK_MODE_ACK") );

    RKCMAPPING_HELPER( RK100_EVT_SET_WORK_MODE, _T("RK100_EVT_SET_WORK_MODE") );
    RKCMAPPING_HELPER( RK100_EVT_SET_WORK_MODE_ACK, _T("RK100_EVT_SET_WORK_MODE_ACK") );

    RKCMAPPING_HELPER( RK100_EVT_SET_HEART_BEAT, _T("RK100_EVT_SET_HEART_BEAT") ,3);
    RKCMAPPING_HELPER( RK100_EVT_SET_HEART_BEAT_ACK, _T("RK100_EVT_SET_HEART_BEAT_ACK") ,3);

    RKCMAPPING_HELPER( RK100_EVT_GET_POWER, _T("RK100_EVT_GET_POWER") ,3);
    RKCMAPPING_HELPER( RK100_EVT_GET_POWER_ACK, _T("RK100_EVT_GET_POWER_ACK") ,3);

    RKCMAPPING_HELPER( RK100_EVT_LOGIN_OTHER, _T("RK100_EVT_LOGIN_OTHER") );

    RKCMAPPING_HELPER( RK100_EVT_TFTP_UPDATE_FIRST_NOTIFY, _T("RK100_EVT_TFTP_UPDATE_FIRST_NOTIFY") );
    RKCMAPPING_HELPER( RK100_EVT_TFTP_UPDATE_SECOND_NOTIFY, _T("RK100_EVT_TFTP_UPDATE_SECOND_NOTIFY") );

    RKCMAPPING_HELPER( RK100_EVT_SET_DEBUG_MODE, _T("RK100_EVT_SET_DEBUG_MODE"));
    RKCMAPPING_HELPER( RK100_EVT_SET_DEBUG_MODE_ACK, _T("RK100_EVT_SET_DEBUG_MODE_ACK"));

    RKCMAPPING_HELPER( RK100_EVT_GET_DEBUG_MODE, _T("RK100_EVT_GET_DEBUG_MODE"));
    RKCMAPPING_HELPER( RK100_EVT_GET_DEBUG_MODE_ACK, _T("RK100_EVT_GET_DEBUG_MODE_ACK"));
}

u16 CRkcMsgDriver::PostMsg(u32 dwType)
{  
    u16 wRet = NO_ERROR;
    u16 wEvent = 0;
    if (TYPE_TPMSG == dwType) 
    {  
        wRet = OspPost(MAKEIID(AID_RKC_APP,0), m_tOspMsg.GetEvent(),m_tOspMsg.GetBody(),m_tOspMsg.GetBodyLen());
    }
    return wRet;
}

void CRkcMsgDriver::OnOspMessageComing(WPARAM wParam, LPARAM lParam)
{
    // 从OSP回调线程提取消息
    CRkcMsgHandler *pHandler = CRkcMsgHandler::GetMsgHandler();
    if (!pHandler) 
    {
        return;
    }
    CRkcMsgQueue cMsgQue;
    pHandler->PopAllMsg(cMsgQue);
    // 分发消息
    while(!cMsgQue.IsEmpty())
    {
        const CMessage &cMsg = cMsgQue.Front();

        //打印输出
        CString strEvent = CRkcPrintCtrl::GetPrintCtrl()->GetEventDescribe(cMsg.event); 

        PrtRkcMsg(cMsg.event, "\n[RkcLib]: 收到消息:%s(%u).", strEvent,cMsg.event);

        // 检索消息分发表
        vector<CKdvDispEvent*>::iterator itr = m_vpDispEvent.begin();
        BOOL bFind = FALSE;
        for(; itr != m_vpDispEvent.end(); itr++)
        {
            if ((*itr)->HasRegEvent(cMsg.event)) 
            {
                (*itr)->DispEvent(cMsg);
                bFind = TRUE;
            }
        }
        if (!bFind) 
        {	  	 
            PrtRkcMsg( "[RkcLib]: 消息:%s(%d)被抛弃,因为没有找到匹配的消息处理器.\n", strEvent, cMsg.event);		
        }

        cMsgQue.Pop();
    }
}

