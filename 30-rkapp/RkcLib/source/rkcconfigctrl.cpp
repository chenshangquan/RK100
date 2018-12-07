#include "stdafx.h"
#include "rkcconfigctrl.h"
#include "event.h"
#include "socketmanager.h"
#include "rkcevent.h"
#include "rkcprintctrl.h"

CRkcConfigCtrl::CRkcConfigCtrl(CRkcSession &cSession) : CRkcConfigCtrlIF()
{
    m_pSession = &cSession;

    memset(&m_tRK100WorkMode, 0, sizeof(TRK100WorkMode));
    memset(&m_tRK100NetParam, 0, sizeof(TRK100NetParam));
    memset(&m_tRK100TftpFwUpdate, 0, sizeof(TRK100TftpFwUpdate));
    memset(&m_tRK100PowerInfo, 0, sizeof(TRK100PowerInfo));
    memset(&m_tRK100DebugInfo, 0, sizeof(TRK100DebugMode));
    memset(&m_tRK100UpdateHead, 0, sizeof(TRK100UpdateHead));

    BuildEventsMap();
}

CRkcConfigCtrl::~CRkcConfigCtrl()
{

}

void CRkcConfigCtrl::BuildEventsMap()
{
    REG_PFUN( UI_RKC_DISCONNECTED, CRkcConfigCtrl::OnDicconnected );

    REG_PFUN( RK100_EVT_GET_WORK_MODE_ACK, CRkcConfigCtrl::OnGetWorkModeConfigRsp );
    REG_PFUN( RK100_EVT_SET_WORK_MODE_ACK, CRkcConfigCtrl::OnSetWorkModeConfigRsp );
    REG_PFUN( RK100_EVT_GET_NETPARAM_ACK, CRkcConfigCtrl::OnGetNetWorkConfigRsp );
    REG_PFUN( RK100_EVT_SET_NETPARAM_ACK, CRkcConfigCtrl::OnSetNetWorkConfigRsp );
    REG_PFUN( RK100_EVT_TFTP_UPDATE_FIRST_ACK, CRkcConfigCtrl::OnSetFtpUpdateFirstRsp);
    REG_PFUN( RK100_EVT_TFTP_UPDATE_FIRST_NOTIFY, CRkcConfigCtrl::OnSetFtpUpdateFirstNotify);
    REG_PFUN( RK100_EVT_TFTP_UPDATE_SECOND_ACK, CRkcConfigCtrl::OnSetFtpUpdateSecondRsp);
    REG_PFUN( RK100_EVT_TFTP_UPDATE_SECOND_NOTIFY, CRkcConfigCtrl::OnSetFtpUpdateSecondNotify);
    REG_PFUN( RK100_EVT_REBOOT_ACK, CRkcConfigCtrl::OnReBootRkRsp);
    REG_PFUN( RK100_EVT_RESTORE_ACK, CRkcConfigCtrl::OnRestoreRkRsp);
    REG_PFUN( RK100_EVT_GET_POWER_ACK, CRkcConfigCtrl::OnPowerRsp);
    REG_PFUN( RK100_EVT_GET_DEBUG_MODE_ACK, CRkcConfigCtrl::OnGetDebugModeRsp);
    REG_PFUN( RK100_EVT_SET_DEBUG_MODE_ACK, CRkcConfigCtrl::OnSetDebugModeRsp);
}

void CRkcConfigCtrl::DispEvent(const CMessage &cMsg)
{
    DISP_FUN(CRkcConfigCtrl, cMsg);
}

void CRkcConfigCtrl::OnTimeOut(u16 wEvent)
{ 
}

void CRkcConfigCtrl::OnDicconnected(const CMessage& cMsg)
{
    //清空数据
    memset(&m_tRK100WorkMode, 0, sizeof(TRK100WorkMode));
    memset(&m_tRK100NetParam, 0, sizeof(TRK100NetParam));
    memset(&m_tRK100TftpFwUpdate, 0, sizeof(TRK100TftpFwUpdate));
    memset(&m_tRK100PowerInfo, 0, sizeof(TRK100PowerInfo));
    memset(&m_tRK100UpdateHead, 0, sizeof(TRK100UpdateHead));
    memset(&m_tRK100DebugInfo, 0, sizeof(TRK100DebugMode));
}

u16 CRkcConfigCtrl::ReBootRk()
{
    TRK100MsgHead tRK100MsgHead;//定义消息头结构体
    memset(&tRK100MsgHead,0,sizeof(TRK100MsgHead));
    //整型传数据集的转网络序
    tRK100MsgHead.dwEvent = htonl(RK100_EVT_REBOOT);
    CRkMessage rkmsg;//定义消息
    rkmsg.SetBody(&tRK100MsgHead, sizeof(TRK100MsgHead));//添加头内容

    PrtRkcMsg( RK100_EVT_REBOOT, emEventTypeScoketSend ,"重启");

    SOCKETWORK->SendDataPack(rkmsg);//消息发送
    return NOERROR;
}

void CRkcConfigCtrl::OnReBootRkRsp(const CMessage& cMsg)
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

    PrtRkcMsg( RK100_EVT_REBOOT_ACK, emEventTypeScoketRecv, "wOptRtn = %d", tMsgHead.wOptRtn);

    PostEvent(UI_RKC_REBOOT, WPARAM(RK100_OPT_RTN_OK == tMsgHead.wOptRtn) , (LPARAM)tMsgHead.wOptRtn );
}

u16 CRkcConfigCtrl::RestoreRk(TRK100LoginInfo tRK100LoginInfo)
{
    TRK100MsgHead tRK100MsgHead;//定义消息头结构体
    memset(&tRK100MsgHead,0,sizeof(TRK100MsgHead));
    //整型传数据集的转网络序
    tRK100MsgHead.dwEvent = htonl(RK100_EVT_RESTORE);
    tRK100MsgHead.wMsgLen = htons(sizeof(TRK100LoginInfo));
    CRkMessage rkmsg;//定义消息
    rkmsg.SetBody(&tRK100MsgHead, sizeof(TRK100MsgHead));//添加头内容
    rkmsg.CatBody(&tRK100LoginInfo, sizeof(TRK100LoginInfo));//添加消息内容

    PrtRkcMsg( RK100_EVT_RESTORE, emEventTypeScoketSend, "password = %s", tRK100LoginInfo.szPwd);

    SOCKETWORK->SendDataPack(rkmsg);//消息发送
    return NOERROR;
}

void CRkcConfigCtrl::OnRestoreRkRsp(const CMessage& cMsg)
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

    PrtRkcMsg( RK100_EVT_RESTORE_ACK, emEventTypeScoketRecv, "wOptRtn = %d", tMsgHead.wOptRtn);

    PostEvent(UI_RKC_RESTONE, WPARAM(RK100_OPT_RTN_OK == tMsgHead.wOptRtn) , (LPARAM)tMsgHead.wOptRtn );
}

u16 CRkcConfigCtrl::GetWorkModeConfig()
{
    TRK100MsgHead tRK100MsgHead;//定义消息头结构体
    memset(&tRK100MsgHead,0,sizeof(TRK100MsgHead));
    //整型传数据集的转网络序
    tRK100MsgHead.dwEvent = htonl(RK100_EVT_GET_WORK_MODE);
    CRkMessage rkmsg;//定义消息
    rkmsg.SetBody(&tRK100MsgHead, sizeof(TRK100MsgHead));//添加头内容

    PrtRkcMsg( RK100_EVT_GET_WORK_MODE, emEventTypeScoketSend ,"获取工作模式");

    SOCKETWORK->SendDataPack(rkmsg);//消息发送
    return NOERROR;
}

void CRkcConfigCtrl::OnGetWorkModeConfigRsp(const CMessage& cMsg)
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

    PrtRkcMsg( RK100_EVT_GET_WORK_MODE_ACK, emEventTypeScoketRecv, "wOptRtn = %d", tMsgHead.wOptRtn);

    if (tMsgHead.wMsgLen != 0)
    {
        m_tRK100WorkMode = *reinterpret_cast<TRK100WorkMode*>( cMsg.content + sizeof(TRK100MsgHead) );
    }
    PostEvent(UI_RKC_WORKMODE_REFLESH, WPARAM(RK100_OPT_RTN_OK == tMsgHead.wOptRtn), (LPARAM)tMsgHead.wOptRtn );
}

u16 CRkcConfigCtrl::GetWorkModeConfig(TRK100WorkMode& tRK100WorkMode)
{
    tRK100WorkMode = m_tRK100WorkMode;
    return NOERROR;
}

u16 CRkcConfigCtrl::SetWorkModeConfig(TRK100WorkMode tRK100WorkMode)
{
    TRK100MsgHead tRK100MsgHead;//定义消息头结构体
    memset(&tRK100MsgHead,0,sizeof(TRK100MsgHead));
    //整型传数据集的转网络序
    tRK100MsgHead.dwEvent = htonl(RK100_EVT_SET_WORK_MODE);
    tRK100MsgHead.wMsgLen = htons(sizeof(TRK100WorkMode));
    CRkMessage rkmsg;//定义消息
    rkmsg.SetBody(&tRK100MsgHead, sizeof(TRK100MsgHead));//添加头内容
    rkmsg.CatBody(&tRK100WorkMode, sizeof(TRK100WorkMode));//添加消息体

    PrtRkcMsg( RK100_EVT_SET_WORK_MODE, emEventTypeScoketSend ,"设置工作模式");

    SOCKETWORK->SendDataPack(rkmsg);//消息发送
    return NOERROR;
}

void CRkcConfigCtrl::OnSetWorkModeConfigRsp(const CMessage& cMsg)
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

    PrtRkcMsg( RK100_EVT_SET_WORK_MODE_ACK, emEventTypeScoketRecv, "wOptRtn = %d", tMsgHead.wOptRtn);

    if (RK100_OPT_RTN_OK == tMsgHead.wOptRtn)
    {
        PostEvent(UI_RKC_WORKMODE_CHANGE, true);
    }
    else
    {
        PostEvent(UI_RKC_WORKMODE_CHANGE, false);
    }
}

u16 CRkcConfigCtrl::GetNetWorkConfig()
{
    TRK100MsgHead tRK100MsgHead;//定义消息头结构体
    memset(&tRK100MsgHead,0,sizeof(TRK100MsgHead));
    //整型传数据集的转网络序
    tRK100MsgHead.dwEvent = htonl(RK100_EVT_GET_NETPARAM);
    CRkMessage rkmsg;//定义消息
    rkmsg.SetBody(&tRK100MsgHead, sizeof(TRK100MsgHead));//添加头内容

    PrtRkcMsg( RK100_EVT_GET_NETPARAM, emEventTypeScoketSend ,"获取网络配置");

    SOCKETWORK->SendDataPack(rkmsg);//消息发送
    return NOERROR;
}

void CRkcConfigCtrl::OnGetNetWorkConfigRsp(const CMessage& cMsg)
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

    PrtRkcMsg( RK100_EVT_GET_NETPARAM_ACK, emEventTypeScoketRecv, "wOptRtn = %d", tMsgHead.wOptRtn);

    if (tMsgHead.wMsgLen != 0)
    {
        m_tRK100NetParam = *reinterpret_cast<TRK100NetParam*>( cMsg.content + sizeof(TRK100MsgHead) );
        m_tRK100NetParam.dwIP = ntohl(m_tRK100NetParam.dwIP);
        m_tRK100NetParam.dwSubMask = ntohl(m_tRK100NetParam.dwSubMask);
        m_tRK100NetParam.dwGateway = ntohl(m_tRK100NetParam.dwGateway);
        m_tRK100NetParam.dwMqttIP = ntohl(m_tRK100NetParam.dwMqttIP);
        m_tRK100NetParam.MqttPort = ntohs(m_tRK100NetParam.MqttPort);
    }
    PostEvent(UI_RKC_NETWORK_REFLESH, WPARAM(RK100_OPT_RTN_OK == tMsgHead.wOptRtn), (LPARAM)tMsgHead.wOptRtn );
}

u16 CRkcConfigCtrl::GetNetWorkConfig(TRK100NetParam& tRK100NetParam)
{
    tRK100NetParam = m_tRK100NetParam;
    return NOERROR;
}

u16 CRkcConfigCtrl::SetNetWorkConfig(TRK100NetParam tRK100NetParam)
{
    TRK100MsgHead tRK100MsgHead;//定义消息头结构体
    memset(&tRK100MsgHead,0,sizeof(TRK100MsgHead));
    //整型传数据集的转网络序
    tRK100MsgHead.dwEvent = htonl(RK100_EVT_SET_NETPARAM);
    tRK100MsgHead.wMsgLen = htons(sizeof(TRK100NetParam));
    CRkMessage rkmsg;//定义消息
    rkmsg.SetBody(&tRK100MsgHead, sizeof(TRK100MsgHead));//添加头内容
    tRK100NetParam.dwIP = htonl(tRK100NetParam.dwIP);
    tRK100NetParam.dwSubMask = htonl(tRK100NetParam.dwSubMask);
    tRK100NetParam.dwGateway = htonl(tRK100NetParam.dwGateway);
    tRK100NetParam.dwMqttIP = htonl(tRK100NetParam.dwMqttIP);
    tRK100NetParam.MqttPort = htons(tRK100NetParam.MqttPort);
    rkmsg.CatBody(&tRK100NetParam, sizeof(TRK100NetParam));//添加消息体

    PrtRkcMsg( RK100_EVT_SET_NETPARAM, emEventTypeScoketSend ,"设置网络配置");

    SOCKETWORK->SendDataPack(rkmsg);//消息发送
    return NOERROR;
}

void CRkcConfigCtrl::OnSetNetWorkConfigRsp(const CMessage& cMsg)
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

    PrtRkcMsg( RK100_EVT_SET_NETPARAM_ACK, emEventTypeScoketRecv, "wOptRtn = %d", tMsgHead.wOptRtn);

    if (RK100_OPT_RTN_OK == tMsgHead.wOptRtn)
    {
        PostEvent(UI_RKC_NETWORK_CHANGE, true);
    }
    else
    {
        PostEvent(UI_RKC_NETWORK_CHANGE, false);
    }
}

u16 CRkcConfigCtrl::SetFtpUpdateFirst(TRK100TftpFwUpdate tRK100TftpFwUpdate)
{
    //保存参数 用于second消息发送
    m_tRK100TftpFwUpdate = tRK100TftpFwUpdate;

    TRK100MsgHead tRK100MsgHead;//定义消息头结构体
    memset(&tRK100MsgHead,0,sizeof(TRK100MsgHead));
    //整型传数据集的转网络序
    tRK100MsgHead.dwEvent = htonl(RK100_EVT_TFTP_UPDATE_FIRST);
    tRK100MsgHead.wMsgLen = htons(sizeof(TRK100TftpFwUpdate));
    CRkMessage rkmsg;//定义消息
    rkmsg.SetBody(&tRK100MsgHead, sizeof(TRK100MsgHead));//添加头内容
    tRK100TftpFwUpdate.dwTftpSvrIp = htonl(tRK100TftpFwUpdate.dwTftpSvrIp);
    tRK100TftpFwUpdate.dwFileSize = htonl(tRK100TftpFwUpdate.dwFileSize);
    rkmsg.CatBody(&tRK100TftpFwUpdate, sizeof(TRK100TftpFwUpdate));//添加后续消息
    SOCKETWORK->SendDataPack(rkmsg);//消息发送
    return NOERROR;
}

void CRkcConfigCtrl::OnSetFtpUpdateFirstRsp(const CMessage& cMsg)
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

    PrtRkcMsg( RK100_EVT_TFTP_UPDATE_FIRST_ACK, emEventTypeScoketRecv, "wOptRtn = %d", tMsgHead.wOptRtn);
    PostEvent(UI_RKC_UPDATE_FIRST_ACK, WPARAM(RK100_OPT_RTN_OK == tMsgHead.wOptRtn) , (LPARAM)tMsgHead.wOptRtn);

}

void CRkcConfigCtrl::OnSetFtpUpdateFirstNotify(const CMessage& cMsg)
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

    if (tMsgHead.wMsgLen != 0)
    {
        m_tRK100UpdateHead = *reinterpret_cast<TRK100UpdateHead*>( cMsg.content + sizeof(TRK100MsgHead) );
        m_tRK100UpdateHead.Magic = ntohl(m_tRK100UpdateHead.Magic);
    }

    PrtRkcMsg( RK100_EVT_TFTP_UPDATE_FIRST_NOTIFY, emEventTypeScoketRecv, "wOptRtn = %d", tMsgHead.wOptRtn);
    PostEvent(UI_RKC_UPDATE_FIRST_NTY, WPARAM(RK100_OPT_RTN_OK == tMsgHead.wOptRtn) , (LPARAM)tMsgHead.wOptRtn);
}

u16 CRkcConfigCtrl::SetFtpUpdateSecond()
{
    TRK100MsgHead tRK100MsgHead;//定义消息头结构体
    memset(&tRK100MsgHead,0,sizeof(TRK100MsgHead));
    //整型传数据集的转网络序
    tRK100MsgHead.dwEvent = htonl(RK100_EVT_TFTP_UPDATE_SECOND);
    tRK100MsgHead.wMsgLen = htons(sizeof(TRK100TftpFwUpdate));
    CRkMessage rkmsg;//定义消息
    rkmsg.SetBody(&tRK100MsgHead, sizeof(TRK100MsgHead));//添加头内容
    m_tRK100TftpFwUpdate.dwTftpSvrIp = htonl(m_tRK100TftpFwUpdate.dwTftpSvrIp);
    m_tRK100TftpFwUpdate.dwFileSize = htonl(m_tRK100TftpFwUpdate.dwFileSize);
    rkmsg.CatBody(&m_tRK100TftpFwUpdate, sizeof(TRK100TftpFwUpdate));//添加后续消息
    SOCKETWORK->SendDataPack(rkmsg);//消息发送
    return NOERROR;
}

void CRkcConfigCtrl::OnSetFtpUpdateSecondRsp(const CMessage& cMsg)
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

    PrtRkcMsg( RK100_EVT_TFTP_UPDATE_SECOND_ACK, emEventTypeScoketRecv, "wOptRtn = %d", tMsgHead.wOptRtn);
}

void CRkcConfigCtrl::OnSetFtpUpdateSecondNotify(const CMessage& cMsg)
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

    PrtRkcMsg( RK100_EVT_TFTP_UPDATE_SECOND_NOTIFY, emEventTypeScoketRecv, "wOptRtn = %d", tMsgHead.wOptRtn);
    PostEvent(UI_RKC_UPDATE_SECOND_NTY, WPARAM(RK100_OPT_RTN_OK == tMsgHead.wOptRtn) , (LPARAM)tMsgHead.wOptRtn);
}

u16 CRkcConfigCtrl::GetUpdateConfig(TRK100UpdateHead& tRK100UpdateHead)
{
    tRK100UpdateHead = m_tRK100UpdateHead;
    return true;
}

u16 CRkcConfigCtrl::GetPowerConfig()
{
    TRK100MsgHead tRK100MsgHead;//定义消息头结构体
    memset(&tRK100MsgHead,0,sizeof(TRK100MsgHead));
    //整型传数据集的转网络序
    tRK100MsgHead.dwEvent = htonl(RK100_EVT_GET_POWER);
    CRkMessage rkmsg;//定义消息
    rkmsg.SetBody(&tRK100MsgHead, sizeof(TRK100MsgHead));//添加头内容

    PrtRkcMsg( RK100_EVT_GET_POWER, emEventTypeScoketSend ,"获取电源状态");

    SOCKETWORK->SendDataPack(rkmsg);//消息发送
    return NOERROR;
}

void CRkcConfigCtrl::OnPowerRsp(const CMessage& cMsg)
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

    PrtRkcMsg( RK100_EVT_GET_POWER_ACK, emEventTypeScoketRecv, "wOptRtn = %d", tMsgHead.wOptRtn);

    if (tMsgHead.wMsgLen != 0)
    {
        m_tRK100PowerInfo = *reinterpret_cast<TRK100PowerInfo*>( cMsg.content + sizeof(TRK100MsgHead) );
        m_tRK100PowerInfo.dwCurrent = ntohl(m_tRK100PowerInfo.dwCurrent);
        m_tRK100PowerInfo.dwPower = ntohl(m_tRK100PowerInfo.dwPower);

        PostEvent(UI_RKC_POWER_FLESH);
    }
}

u16 CRkcConfigCtrl::GetPowerConfig(TRK100PowerInfo& tRK100PowerInfo)
{
    tRK100PowerInfo = m_tRK100PowerInfo;
    return true;
}

u16 CRkcConfigCtrl::GetDebugConfig()
{
    TRK100MsgHead tRK100MsgHead;//定义消息头结构体
    memset(&tRK100MsgHead,0,sizeof(TRK100MsgHead));
    //整型传数据集的转网络序
    tRK100MsgHead.dwEvent = htonl(RK100_EVT_GET_DEBUG_MODE);
    CRkMessage rkmsg;//定义消息
    rkmsg.SetBody(&tRK100MsgHead, sizeof(TRK100MsgHead));//添加头内容

    PrtRkcMsg( RK100_EVT_GET_DEBUG_MODE, emEventTypeScoketSend ,"获取调试模式");

    SOCKETWORK->SendDataPack(rkmsg);//消息发送
    return NOERROR;
}

void CRkcConfigCtrl::OnGetDebugModeRsp(const CMessage& cMsg)
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

    PrtRkcMsg( RK100_EVT_GET_DEBUG_MODE_ACK, emEventTypeScoketRecv, "wOptRtn = %d", tMsgHead.wOptRtn);

    if (tMsgHead.wMsgLen != 0)
    {
        m_tRK100DebugInfo = *reinterpret_cast<TRK100DebugMode*>( cMsg.content + sizeof(TRK100MsgHead) );
    }
    PostEvent(UI_RKC_DEBUGMODE_FLESH, WPARAM(RK100_OPT_RTN_OK == tMsgHead.wOptRtn), (LPARAM)tMsgHead.wOptRtn );
}

u16 CRkcConfigCtrl::GetDebugConfig(TRK100DebugMode& tRK100DebugInfo)
{
    tRK100DebugInfo = m_tRK100DebugInfo;
    return true;
}

u16 CRkcConfigCtrl::SetDebugConfig(TRK100DebugMode tRK100DebugInfo)
{
    TRK100MsgHead tRK100MsgHead;//定义消息头结构体
    memset(&tRK100MsgHead,0,sizeof(TRK100MsgHead));
    //整型传数据集的转网络序
    tRK100MsgHead.dwEvent = htonl(RK100_EVT_SET_DEBUG_MODE);
    tRK100MsgHead.wMsgLen = htons(sizeof(TRK100DebugMode));
    CRkMessage rkmsg;//定义消息
    rkmsg.SetBody(&tRK100MsgHead, sizeof(TRK100MsgHead));//添加头内容
    rkmsg.CatBody(&tRK100DebugInfo, sizeof(TRK100DebugMode));//添加消息体

    PrtRkcMsg( RK100_EVT_SET_NETPARAM, emEventTypeScoketSend ,"设置调试模式配置");

    SOCKETWORK->SendDataPack(rkmsg);//消息发送
    return NOERROR;
}

void CRkcConfigCtrl::OnSetDebugModeRsp(const CMessage& cMsg)
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

    PrtRkcMsg( RK100_EVT_SET_DEBUG_MODE_ACK, emEventTypeScoketRecv, "wOptRtn = %d", tMsgHead.wOptRtn);

    if (RK100_OPT_RTN_OK == tMsgHead.wOptRtn)
    {
        PostEvent(UI_RKC_DEBUGMODE_CHANGE, true);
    }
    else
    {
        PostEvent(UI_RKC_DEBUGMODE_CHANGE, false);
    }
}