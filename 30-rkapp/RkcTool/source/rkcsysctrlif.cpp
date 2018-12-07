#include "stdafx.h"
#include "rkcinterface.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

UINT ThreadConnectRkc(LPVOID lpParam)
{
    u16 re  = CRkcComInterface->SocketIP();

    if ( re != NO_ERROR )
    {
        NOTIFY_MSG( UI_RKC_CONNECTED, FALSE, re );
        return re;
    }

    CRkcComInterface->SendLoginReq();

    return re;
}

u16 CRkcInterface::SocketConnect(TDevItem tDevItem , s8* szUser , s8* szPwd)
{
    if( NULL == m_pSysCtrlIf )
    {
        return -1;
    }
    m_tDevItem = tDevItem;

    u32 dwIP = htonl(tDevItem.tDevInfo.tAddr.dwIpaddr);
    strncpy(m_tLoginInfo.m_achIp, inet_ntoa(*(in_addr*)&dwIP), sizeof(m_tLoginInfo.m_achIp));
    m_tLoginInfo.m_wPort = RK100_LISTEN_PORT;

    strncpy(m_tRK100LoginInfo.szUsr, szUser, sizeof(m_tRK100LoginInfo.szUsr));
    strncpy(m_tRK100LoginInfo.szPwd, szPwd, sizeof(m_tRK100LoginInfo.szPwd));

    //连接cns
    AfxBeginThread( ThreadConnectRkc , NULL );

    return NO_ERROR;
}

u16 CRkcInterface::SocketIP()
{
    return m_pSysCtrlIf->SocketConnect(m_tLoginInfo.m_achIp, m_tLoginInfo.m_wPort);
}

u16 CRkcInterface::CloseSocket()
{
    return m_pSysCtrlIf->CloseSocket();
}

u16 CRkcInterface::SendLoginReq()
{
    if( NULL == m_pSysCtrlIf )
    {
        return -1;
    }

    u16 re  = m_pSysCtrlIf->SendLoginReq(m_tRK100LoginInfo);

    return re;
}

bool CRkcInterface::IsLoginState()
{
    if( NULL == m_pSysCtrlIf )
    {
        return false;
    }

    return m_pSysCtrlIf->IsLoginState();
}

u16 CRkcInterface::GetLoginDevItem(TDevItem& tDevItem)
{
    tDevItem = m_tDevItem;
    return NO_ERROR;
}

u16 CRkcInterface::GetLoginInfo(TRK100LoginInfo& tRK100LoginInfo)
{
    tRK100LoginInfo = m_tRK100LoginInfo;
    return NO_ERROR;
}

u16 CRkcInterface::GetLoginBackInfo(TRK100MsgHead& tRK100MsgHead)
{
    if( NULL == m_pSysCtrlIf )
    {
        return -1;
    }

    u16 re  = m_pSysCtrlIf->GetLoginBackInfo(tRK100MsgHead);

    return re;
}

u16 CRkcInterface::SetLoginInfo(s8* szNewPwd)
{
    strncpy(m_tRK100LoginInfo.szPwd, szNewPwd, sizeof(m_tRK100LoginInfo.szPwd));
    return NO_ERROR;
}

u16 CRkcInterface::SendModifyPasswordReq()
{
    if( NULL == m_pSysCtrlIf )
    {
        return -1;
    }

    u16 re  = m_pSysCtrlIf->SendModifyPasswordReq(m_tRK100LoginInfo);

    return re;
}

//TFtp相关
bool CRkcInterface::OpenTftp()
{
    if( NULL == m_pSysCtrlIf )
    {
        return false;
    }
    return m_pSysCtrlIf->OpenTftp();
}
bool CRkcInterface::CloseTftp()
{
    if( NULL == m_pSysCtrlIf )
    {
        return false;
    }
    return m_pSysCtrlIf->CloseTftp();
}

bool CRkcInterface::SetTftpPath(const s8 *pchPath)
{
    if( NULL == m_pSysCtrlIf )
    {
        return false;
    }
    return m_pSysCtrlIf->SetTftpPath(pchPath);
}
bool CRkcInterface::SetDhcpBootFile(const s8 *pchPath)
{
    if( NULL == m_pSysCtrlIf )
    {
        return false;
    }
    return m_pSysCtrlIf->SetDhcpBootFile(pchPath);
}
bool CRkcInterface::KillTftpProcess()
{
    if( NULL == m_pSysCtrlIf )
    {
        return false;
    }
    return m_pSysCtrlIf->KillTftpProcess();
}
