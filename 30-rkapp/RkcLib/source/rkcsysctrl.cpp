#include "stdafx.h"
#include "rkcsysctrl.h"
#include "event.h"
#include "socketmanager.h"
#include "rkcevent.h"
#include "rkcprintctrl.h"
#include "Tftp.h"
#include "cmd5.h"

CRkcSysCtrl::CRkcSysCtrl(CRkcSession &cSession) : CRkcSysCtrlIF()
{
    memset(&m_tRK100MsgHead,0,sizeof(m_tRK100MsgHead));
    m_pSession = &cSession;
    BuildEventsMap();
}

CRkcSysCtrl::~CRkcSysCtrl()
{

}

u16 CRkcSysCtrl::SocketConnect(s8* pchIP, u32 dwPort)
{
    SOCKETWORK->setSocketIP(pchIP);
    SOCKETWORK->SetSocketPort(dwPort);
    u8 nRe = SOCKETWORK->OpenSocket();
    PrtRkcMsg( RK100_EVT_LOGIN, emEventTypeScoketSend, "connect Ip : nRe =  %d", nRe );
    return nRe;
}

u16 CRkcSysCtrl::CloseSocket()
{
    SOCKETWORK->CloseSocket();
    return NO_ERROR;
}

u16 CRkcSysCtrl::SendLoginReq( TRK100LoginInfo tRK100LoginInfo )
{
    TRK100MsgHead tRK100MsgHead;//定义消息头结构体
    memset(&tRK100MsgHead,0,sizeof(TRK100MsgHead));
    //整型传数据集的转网络序
    tRK100MsgHead.dwEvent = htonl(RK100_EVT_LOGIN);
    tRK100MsgHead.wMsgLen = htons(sizeof(TRK100LoginInfo));
    CRkMessage rkmsg;//定义消息
    rkmsg.SetBody(&tRK100MsgHead, sizeof(TRK100MsgHead));//添加头内容
    CMD5Encrypt cMd5;
    cMd5.GetEncrypted(tRK100LoginInfo.szPwd, tRK100LoginInfo.szPwd);//Md5加密
    rkmsg.CatBody(&tRK100LoginInfo, sizeof(TRK100LoginInfo));//添加消息内容

    PrtRkcMsg( RK100_EVT_LOGIN, emEventTypeScoketSend, "Login : username =  %s", tRK100LoginInfo.szUsr );
    SOCKETWORK->SendDataPack(rkmsg);//消息发送
    return NOERROR;
}

bool CRkcSysCtrl::IsLoginState()
{
    return SOCKETWORK->IsSocket();
}

u16 CRkcSysCtrl::SendModifyPasswordReq( TRK100LoginInfo tRK100LoginInfo )
{
    TRK100MsgHead tRK100MsgHead;//定义消息头结构体
    memset(&tRK100MsgHead,0,sizeof(TRK100MsgHead));
    //整型传数据集的转网络序
    tRK100MsgHead.dwEvent = htonl(RK100_EVT_SET_PASSWORD);
    tRK100MsgHead.wMsgLen = htons(sizeof(TRK100LoginInfo));
    CRkMessage rkmsg;//定义消息
    rkmsg.SetBody(&tRK100MsgHead, sizeof(TRK100MsgHead));//添加头内容
    CMD5Encrypt cMd5;
    cMd5.GetEncrypted(tRK100LoginInfo.szPwd, tRK100LoginInfo.szPwd);//Md5加密
    rkmsg.CatBody(&tRK100LoginInfo, sizeof(TRK100LoginInfo));//添加消息内容
    CSocketManager::GetSocketManager()->SendDataPack(rkmsg);//消息发送
    return NOERROR;
}

void CRkcSysCtrl::BuildEventsMap()
{
    REG_PFUN( RK100_EVT_LOGIN_ACK, CRkcSysCtrl::OnLoginRsp );
    REG_PFUN( UI_RKC_DISCONNECTED, CRkcSysCtrl::OnDicconnected );
    REG_PFUN( RK100_EVT_LOGIN_OTHER, CRkcSysCtrl::OnLoginOther );
    REG_PFUN( RK100_EVT_SET_PASSWORD_ACK, CRkcSysCtrl::OnModifyPasswordRsp );
}

void CRkcSysCtrl::OnDicconnected(const CMessage& cMsg)
{
    //发送界面提醒
    PostEvent( UI_RKC_DISCONNECTED);
}

void CRkcSysCtrl::OnLoginOther(const CMessage& cMsg)
{
    CloseSocket();
    PrtRkcMsg( RK100_EVT_LOGIN_OTHER, emEventTypeScoketRecv, "被抢登...");
    PostEvent( UI_RKC_DISCONNECTED, 1  );
}

void CRkcSysCtrl::OnLoginRsp(const CMessage& cMsg)
{
    TRK100MsgHead tMsgHead = *reinterpret_cast<TRK100MsgHead*>( cMsg.content );
    tMsgHead.dwEvent = ntohl(tMsgHead.dwEvent);
    tMsgHead.dwHandle = ntohl(tMsgHead.dwHandle);
    tMsgHead.dwProtocolVer = ntohl(tMsgHead.dwProtocolVer);
    tMsgHead.dwRsvd = ntohl(tMsgHead.dwRsvd);
    tMsgHead.dwSerial = ntohl(tMsgHead.dwSerial);
    tMsgHead.nArgv = ntohl(tMsgHead.nArgv);
    tMsgHead.wExtLen = ntohs(tMsgHead.wExtLen);
    tMsgHead.wMsgLen = ntohs(tMsgHead.wMsgLen);
    tMsgHead.wOptRtn = ntohs(tMsgHead.wOptRtn);
    tMsgHead.wReserved1 = ntohs(tMsgHead.wReserved1);

    PrtRkcMsg( RK100_EVT_LOGIN_ACK, emEventTypeScoketRecv, "LoginRsp : wOptRtn =  %d", tMsgHead.wOptRtn );

    if (RK100_OPT_RTN_OK != tMsgHead.wOptRtn && tMsgHead.wOptRtn != RK100_OPT_ERR_FIRST_LOGIN)
    {
        CloseSocket();
    }
    m_tRK100MsgHead = tMsgHead;
    PostEvent(UI_RKC_CONNECTED, WPARAM(RK100_OPT_RTN_OK == tMsgHead.wOptRtn) , (LPARAM)tMsgHead.wOptRtn );
}

void CRkcSysCtrl::OnModifyPasswordRsp(const CMessage& cMsg)
{
    TRK100MsgHead tMsgHead = *reinterpret_cast<TRK100MsgHead*>( cMsg.content );
    tMsgHead.dwEvent = ntohl(tMsgHead.dwEvent);
    tMsgHead.dwHandle = ntohl(tMsgHead.dwHandle);
    tMsgHead.dwProtocolVer = ntohl(tMsgHead.dwProtocolVer);
    tMsgHead.dwRsvd = ntohl(tMsgHead.dwRsvd);
    tMsgHead.dwSerial = ntohl(tMsgHead.dwSerial);
    tMsgHead.nArgv = ntohl(tMsgHead.nArgv);
    tMsgHead.wExtLen = ntohs(tMsgHead.wExtLen);
    tMsgHead.wMsgLen = ntohs(tMsgHead.wMsgLen);
    tMsgHead.wOptRtn = ntohs(tMsgHead.wOptRtn);
    tMsgHead.wReserved1 = ntohs(tMsgHead.wReserved1);

    PostEvent(UI_RKC_MODIFY_PASSWORD, WPARAM(RK100_OPT_RTN_OK == tMsgHead.wOptRtn) , (LPARAM)tMsgHead.wOptRtn );
}

u16 CRkcSysCtrl::GetLoginBackInfo(TRK100MsgHead& tRK100MsgHead)
{
    tRK100MsgHead = m_tRK100MsgHead;
    return NOERROR;
}

void CRkcSysCtrl::DispEvent(const CMessage &cMsg)
{
    DISP_FUN(CRkcSysCtrl, cMsg);
}

void CRkcSysCtrl::OnTimeOut(u16 wEvent)
{ 
}

//Tftp相关接口
bool CRkcSysCtrl::OpenTftp()
{
    try
    {
        return CTftpOp::Open();
    }
    catch (...)
    {
        return false;
    }
}
bool CRkcSysCtrl::CloseTftp()
{
    try
    {
        return CTftpOp::Open();
    }
    catch (...)
    {
        return false;
    }
    return CTftpOp::Close();
}
bool CRkcSysCtrl::SetTftpPath(const s8 *pchPath)
{
    try
    {
        return CTftpOp::SetTftpPath(pchPath);
    }
    catch (...)
    {
        return false;
    }
}
bool CRkcSysCtrl::SetDhcpBootFile(const s8 *pchPath)
{
    try
    {
        return CTftpOp::SetDhcpBootFile(pchPath);
    }
    catch (...)
    {
        return false;
    }
}
bool CRkcSysCtrl::KillTftpProcess()
{
    try
    {
        return CTftpOp::KillTftpProcess();
    }
    catch (...)
    {
        return false;
    }
}
