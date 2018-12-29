#include "stdafx.h"
#include "rkcsearchctrl.h"
#include "event.h"
#include "rkcevent.h"
#include <Windows.h>
#pragma    comment(lib,"ws2_32.lib")
#include <stdio.h>
#include <memory.h>
#include "kdvtype.h"
#include "rkcprintctrl.h"


void MsgProCallBack(u32 wMsg, void* pParam, u32 dwContext)
{
    switch (wMsg)
    {
    case NC_DEV_TRACK_REQ_CAST:
        {
        }
        break;
    case DEV_NC_TRACK_ACK_CAST:
        {
            TDevItem tItem;
            memcpy(&tItem, pParam, sizeof(tItem));
            OspPost(MAKEIID(AID_RKC_APP,0), UI_RKC_RKDEV_REFLESH , &tItem , sizeof(TDevItem));
        }
        break;
    case DEV_NC_MODADDR_ACK_CAST:
        {
            TDevRetInfo* pInfo = (TDevRetInfo*)pParam;
        }
        break;
    default:
        break;
    }
}


CRkcSearchCtrl::CRkcSearchCtrl(CRkcSession &cSession) : CRkcSearchCtrlIF()
{
    m_pSession = &cSession;

    m_EmSearchType = emTypeAll;
    m_dwStartIP = 0;
    m_dwEndIP = 0;

    //搜索准备
    WSADATA wsaData;
    int nRet;
    if ((nRet = WSAStartup(MAKEWORD(2, 2), &wsaData)) != 0)
    {
        exit(0);
    }
    InitMspSearch();
    SetMsgAckCB(MsgProCallBack, 0);

    BuildEventsMap();
}

CRkcSearchCtrl::~CRkcSearchCtrl()
{
    ExitMspSearch();
}

void CRkcSearchCtrl::BuildEventsMap()
{
    REG_PFUN( UI_RKC_RKDEV_REFLESH, CRkcSearchCtrl::OnRkcDevReflesh );

    REG_PFUN( UI_RKC_DISCONNECTED, CRkcSearchCtrl::OnDicconnected );
}

void CRkcSearchCtrl::DispEvent(const CMessage &cMsg)
{
    DISP_FUN(CRkcSearchCtrl, cMsg);
}

void CRkcSearchCtrl::OnTimeOut(u16 wEvent)
{ 
}

u16 CRkcSearchCtrl::StartSearch()
{
    if (m_EmSearchType == emTypeIP)
    {
        SendDevDetectMsgByUnicast(true, m_dwStartIP, m_dwEndIP);
    }
    else
    {
        SendDevDetectMsg(true);
    }
    //通知界面搜索包发送完毕
    PostEvent(UI_RKC_SEARCH_FINISH);
    return 0;
}

u16 CRkcSearchCtrl::EndSearch()
{
    SendDevDetectMsg(false);
    return 0;
}

u16 CRkcSearchCtrl::SetSearchType(EmSearchType emtype , u32 dwStartip , u32 dwEndip)
{
    m_EmSearchType = emtype;
    m_dwStartIP = dwStartip;
    m_dwEndIP = dwEndip;
    return 0;
}

void CRkcSearchCtrl::ReSet()
{
    m_vecDevItem.clear();
    m_EmSearchType = emTypeAll;
    m_dwStartIP = 0;
    m_dwEndIP = 0;
}

void CRkcSearchCtrl::OnDicconnected(const CMessage& cMsg)
{
    //清空数据
    m_EmSearchType = emTypeAll;
    m_dwStartIP = 0;
    m_dwEndIP = 0;
}

void CRkcSearchCtrl::OnRkcDevReflesh(const CMessage& cMsg)
{
    TDevItem tDevItem = *(TDevItem*)(cMsg.content);
    //屏蔽显示 只显示RK100
    if (strcmp("RK100", tDevItem.tDevID.achDevType) != 0)
    {
        return;
    }
    //搜索区间
    if (m_EmSearchType == emTypeIP)
    {
        u32 dwIP = tDevItem.tDevInfo.tAddr.dwIpaddr;
        if (dwIP < m_dwStartIP || m_dwEndIP < dwIP)
        {
            return;
        }
    }

    bool bfind = false;
    for (unsigned int i = 0 ; i < m_vecDevItem.size() ; i++ )
    {
        if (m_vecDevItem.at(i).tDevInfo.tAddr.dwIpaddr == tDevItem.tDevInfo.tAddr.dwIpaddr)
        {
            bfind = true;
            break;
        }
    }
    if (!bfind)
    {
        m_vecDevItem.push_back(tDevItem);
    }
    
    PostEvent(UI_RKC_RKDEV_REFLESH);
}

const vector<TDevItem>& CRkcSearchCtrl::GetDevList() const
{
    return m_vecDevItem;
}