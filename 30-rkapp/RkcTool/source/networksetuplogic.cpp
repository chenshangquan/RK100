#include "stdafx.h"
#include "searchequipmentlogic.h"
#include "networksetuplogic.h"
#include "messageboxlogic.h"
#include "tipboxlogic.h"
#include "toolframelogic.h"

static UINT     g_nRebootTimerID;              //timer ��id,���ڿ�����ʾʱ��
#define         TIME_REBOOT         3000        //��ʱ��ʱ����

static u32 dwCheckingIP;                 //����IP

VOID  CALLBACK  CTimerFun(  HWND   hwnd,   UINT   uMsg, UINT_PTR  idEvent, DWORD   dwTime  )
{
    if ( idEvent == g_nRebootTimerID )
    {
        KillTimer( NULL, g_nRebootTimerID );
        g_nRebootTimerID = 0;
        CRkcComInterface->ReBootRk();  
    }
}

UINT ThreadNetIpConflictChecking(LPVOID lpParam)
{
    TDevItem tLoginDevitem;
    CRkcComInterface->GetLoginDevItem(tLoginDevitem);
    if (UIDATAMGR->NetIpConflict( tLoginDevitem.tDevInfo.tAddr.dwIpaddr, dwCheckingIP))
    {
        NOTIFY_MSG( UI_RKC_IP_CHECK, FALSE, 0 );
    }
    else
    {
        NOTIFY_MSG( UI_RKC_IP_CHECK, TRUE, 0 );
    }
    return 0;
}

template<> CNetworkSetupLogic* Singleton<CNetworkSetupLogic>::ms_pSingleton  = NULL;

APP_BEGIN_MSG_MAP(CNetworkSetupLogic, CNotifyUIImpl)
    MSG_CLICK(_T("SaveNetWorkBut"), OnSaveNetWorkButClicked)
    MSG_CLICK(_T("IPCheckBtn"), OnIPCheckBtnClicked)

    MSG_EDITCHANGE(_T("DeviceIPEdt"), OnDevIPEditTextChange)
    MSG_EDITCHANGE(_T("DeviceSubmaskEdt"), OnEditTextChange)
    MSG_EDITCHANGE(_T("DeviceGatewayEdt"), OnEditTextChange)
    MSG_EDITCHANGE(_T("MqttIPEdt"), OnEditTextChange)
    MSG_EDITCHANGE(_T("MqttPortEdt"), OnEditTextChange)

    USER_MSG(UI_RKC_NETWORK_REFLESH , OnRkcNetWorkReflesh)
    USER_MSG(UI_RKC_NETWORK_CHANGE , OnRkcNetWorkChangeRsp)

    USER_MSG(UI_RKC_IP_CHECK , OnRkcIPChecked)
    USER_MSG(UI_RKC_DISCONNECTED , OnRkcDisconnected)

APP_END_MSG_MAP()

CNetworkSetupLogic::CNetworkSetupLogic()
{
    g_nRebootTimerID = 0;
}

CNetworkSetupLogic::~CNetworkSetupLogic()
{
}

bool CNetworkSetupLogic::OnIPCheckBtnClicked(TNotifyUI& msg)
{
    //����IP
    CString strDeviceIp = (IRkcToolCommonOp::GetControlText(m_pm, _T("DeviceIPEdt"))).c_str();
    if (!strDeviceIp.IsEmpty())//������Ϊ��
    {
        if(!UIDATAMGR->IsValidIp(CT2A(strDeviceIp)))
        {
            ShowMessageBox(_T("����IP��ַ�Ƿ�"));
            return false;
        }
    }
    else
    {
        ShowMessageBox(_T("����IP��ַ����Ϊ��"));
        return false;
    }
    UIDATAMGR->GetClearIP(strDeviceIp);
    dwCheckingIP = inet_addr(CT2A(strDeviceIp));
    IRkcToolCommonOp::EnableControl(false, m_pm, _T("IPCheckBtn"));
    AfxBeginThread( ThreadNetIpConflictChecking , NULL );
    return true;
}

bool CNetworkSetupLogic::OnSaveNetWorkButClicked()
{
    TRK100NetParam tRK100NetParam;
    memset(&tRK100NetParam, 0, sizeof(TRK100NetParam));
    CRkcComInterface->GetNetWorkConfig(tRK100NetParam);

    bool bIsChange = false;
    //����IP
    CString strDeviceIp = (IRkcToolCommonOp::GetControlText(m_pm, _T("DeviceIPEdt"))).c_str();
    if (!strDeviceIp.IsEmpty())//������Ϊ��
    {
        if(!UIDATAMGR->IsValidIp(CT2A(strDeviceIp)))
        {
            ShowMessageBox(_T("����IP��ַ�Ƿ�"));
            return false;
        }
    }
    else
    {
        ShowMessageBox(_T("����IP��ַ����Ϊ��"));
        return false;
    }
    UIDATAMGR->GetClearIP(strDeviceIp);
    u32 dwDevIP = inet_addr(CT2A(strDeviceIp));
    if (tRK100NetParam.dwIP != dwDevIP)
    {
        tRK100NetParam.dwIP = dwDevIP;
        bIsChange = true;
    }
    //������������
    CString strDeviceSubmask = (IRkcToolCommonOp::GetControlText(m_pm, _T("DeviceSubmaskEdt"))).c_str();
    if (!strDeviceSubmask.IsEmpty())//������Ϊ��
    {
        if(!UIDATAMGR->IsValidIp(CT2A(strDeviceSubmask)))
        {
            ShowMessageBox(_T("������������Ƿ�"));
            return false;
        }
    }
    else
    {
        ShowMessageBox(_T("�����������벻��Ϊ��"));
        return false;
    }
    UIDATAMGR->GetClearIP(strDeviceSubmask);
    u32 dwDevSubMask = inet_addr(CT2A(strDeviceSubmask));
    if (tRK100NetParam.dwSubMask != dwDevSubMask)
    {
        tRK100NetParam.dwSubMask = dwDevSubMask;
        bIsChange = true;
    }
    //��������
    CString strDeviceGateway = (IRkcToolCommonOp::GetControlText(m_pm, _T("DeviceGatewayEdt"))).c_str();
    if (!strDeviceGateway.IsEmpty())//������Ϊ��
    {
        if(!UIDATAMGR->IsValidIp(CT2A(strDeviceGateway)))
        {
            ShowMessageBox(_T("�������طǷ�"));
            return false;
        }
    }
    else
    {
        ShowMessageBox(_T("�������ز���Ϊ��"));
        return false;
    }
    UIDATAMGR->GetClearIP(strDeviceGateway);
    u32 dwDevGateWay = inet_addr(CT2A(strDeviceGateway));
    if (tRK100NetParam.dwGateway != dwDevGateWay)
    {
        tRK100NetParam.dwGateway = dwDevGateWay;
        bIsChange = true;
    }
    //MqttIP
    CString strMqttIp = (IRkcToolCommonOp::GetControlText(m_pm, _T("MqttIPEdt"))).c_str();
    if (!strMqttIp.IsEmpty())//������Ϊ��
    {
        if(!UIDATAMGR->IsValidIp(CT2A(strMqttIp)))
        {
            ShowMessageBox(_T("ƽ̨IP��ַ�Ƿ�"));
            return false;
        }
    }
    else
    {
        ShowMessageBox(_T("ƽ̨IP��ַ����Ϊ��"));
        return false;
    }
    UIDATAMGR->GetClearIP(strMqttIp);
    u32 dwDevMqttIP = inet_addr(CT2A(strMqttIp));
    if (tRK100NetParam.dwMqttIP != dwDevMqttIP)
    {
        tRK100NetParam.dwMqttIP = dwDevMqttIP;
        bIsChange = true;
    }
    //MqttPort
    CString strMqttPort = (IRkcToolCommonOp::GetControlText(m_pm, _T("MqttPortEdt"))).c_str();
    if (strMqttPort.IsEmpty())//������Ϊ��
    {
        ShowMessageBox(_T("������ƽ̨����˿���Ϣ"));
        return false;
    }
    u32 dwMqttPort = _ttoi64(strMqttPort);
    if (1 > dwMqttPort || dwMqttPort > 65535)
    {
        ShowMessageBox(_T("�˿ں���1-65535֮��"));
        return false;
    }
    if (tRK100NetParam.MqttPort != dwMqttPort)
    {
        tRK100NetParam.MqttPort = dwMqttPort;
        bIsChange = true;
    }

    if (bIsChange)
    {
        CRkcComInterface->SetNetWorkConfig(tRK100NetParam);
    }
    return true;
}

bool CNetworkSetupLogic::OnSaveNetWorkButClicked(TNotifyUI& msg)
{
    return OnSaveNetWorkButClicked();
}

bool CNetworkSetupLogic::OnDevIPEditTextChange(TNotifyUI& msg)
{
    TRK100NetParam tRK100NetParam;
    memset(&tRK100NetParam, 0, sizeof(TRK100NetParam));
    CRkcComInterface->GetNetWorkConfig(tRK100NetParam);
    //����IP
    CString strDeviceIp = (IRkcToolCommonOp::GetControlText(m_pm, _T("DeviceIPEdt"))).c_str();
    UIDATAMGR->GetClearIP(strDeviceIp);
    u32 dwDevIP = inet_addr(CT2A(strDeviceIp));
    if (tRK100NetParam.dwIP != dwDevIP)
    {
        m_pm->DoCase(_T("caseIPNotCheck"));
    }
    else
    {
        m_pm->DoCase(_T("caseIPIsSave"));
    }
    SetSaveBtnEnable();
    return true;
}

bool CNetworkSetupLogic::OnEditTextChange(TNotifyUI& msg)
{
    SetSaveBtnEnable();
    return true;
}

bool CNetworkSetupLogic::OnRkcNetWorkReflesh( WPARAM wparam, LPARAM lparam, bool& bHandle )
{
    bool bGetSuccess = (bool)wparam;
    if (bGetSuccess == false)
    {
        CRkcComInterface->GetNetWorkConfig();
        return false;
    }

    TRK100NetParam tRK100NetParam;
    memset(&tRK100NetParam, 0, sizeof(TRK100NetParam));
    CRkcComInterface->GetNetWorkConfig(tRK100NetParam);
    //IP
    if (0 != tRK100NetParam.dwIP)
    {
        in_addr tAddrIP;
        tAddrIP.S_un.S_addr = tRK100NetParam.dwIP;
        IRkcToolCommonOp::SetControlText((CA2T)inet_ntoa(tAddrIP), m_pm, _T("DeviceIPEdt"));
    }
    else
    {
        IRkcToolCommonOp::SetControlText(_T(""), m_pm, _T("DeviceIPEdt"));
    }
    //��������
    if (0 != tRK100NetParam.dwSubMask)
    {
        in_addr tAddrSubMask;
        tAddrSubMask.S_un.S_addr = tRK100NetParam.dwSubMask;
        IRkcToolCommonOp::SetControlText((CA2T)inet_ntoa(tAddrSubMask), m_pm, _T("DeviceSubmaskEdt"));
    }
    else
    {
        IRkcToolCommonOp::SetControlText(_T(""), m_pm, _T("DeviceSubmaskEdt"));
    }
    //����
    if (0 != tRK100NetParam.dwGateway)
    {
        in_addr tAddrGateway;
        tAddrGateway.S_un.S_addr = tRK100NetParam.dwGateway;
        IRkcToolCommonOp::SetControlText((CA2T)inet_ntoa(tAddrGateway), m_pm, _T("DeviceGatewayEdt"));
    }
    else
    {
        IRkcToolCommonOp::SetControlText(_T(""), m_pm, _T("DeviceGatewayEdt"));
    }
    //ƽ̨IP
    if ( 0 != tRK100NetParam.dwMqttIP)
    {
        in_addr tAddrMqtt;
        tAddrMqtt.S_un.S_addr = tRK100NetParam.dwMqttIP;
        IRkcToolCommonOp::SetControlText((CA2T)inet_ntoa(tAddrMqtt), m_pm, _T("MqttIPEdt"));
    }
    else
    {
        IRkcToolCommonOp::SetControlText(_T(""), m_pm, _T("MqttIPEdt"));
    }
    //ƽ̨�˿�
    if (tRK100NetParam.MqttPort != 0)
    {
        CString strPort= _T("");
        strPort.Format(_T("%u"), tRK100NetParam.MqttPort);
        IRkcToolCommonOp::SetControlText(strPort, m_pm, _T("MqttPortEdt"));
    }
    else
    {
        IRkcToolCommonOp::SetControlText(_T(""), m_pm, _T("MqttPortEdt"));
    }

    IRkcToolCommonOp::EnableControl(false, m_pm, _T("SaveNetWorkBut"));
    m_pm->DoCase(_T("caseIPIsSave"));
    return true;
}

bool CNetworkSetupLogic::OnRkcNetWorkChangeRsp( WPARAM wparam, LPARAM lparam, bool& bHandle )
{
    bool bSuccess = (bool)wparam;
    EmErrRkcLib emReason = (EmErrRkcLib)lparam;
    if (bSuccess)
    {
        CRkcComInterface->GetNetWorkConfig();
        ShowTipBox(_T("����ɹ�"));
        //��ʱ�����豸
        g_nRebootTimerID = SetTimer( NULL, 0, TIME_REBOOT, CTimerFun );
    }
    else
    {
        ShowTipBox(_T("����ʧ��"));
    }
    return true;
}

bool CNetworkSetupLogic::OnRkcIPChecked( WPARAM wparam, LPARAM lparam, bool& bHandle )
{
    bool bSuccess = (bool)wparam;
    if (bSuccess)
    {
        m_pm->DoCase(_T("caseIPCheckOK"));
    }
    else
    {
        ShowMessageBox(_T("IP��ַ��ͻ�����޸�"));
        m_pm->DoCase(_T("caseIPNotCheck"));
    }
    return true;
}

bool CNetworkSetupLogic::OnRkcDisconnected( WPARAM wparam, LPARAM lparam, bool& bHandle )
{
    CButtonUI *pBtn = (CButtonUI*)IRkcToolCommonOp::FindControl(m_pm, _T("SaveNetWorkBut"));
    if (pBtn)
    {
        pBtn->SetFocus();
    }
    return true;
}


void CNetworkSetupLogic::SetSaveBtnEnable()
{
    TRK100NetParam tRK100NetParam;
    memset(&tRK100NetParam, 0, sizeof(TRK100NetParam));
    CRkcComInterface->GetNetWorkConfig(tRK100NetParam);

    //����IP
    CString strDeviceIp = (IRkcToolCommonOp::GetControlText(m_pm, _T("DeviceIPEdt"))).c_str();
    if (!strDeviceIp.IsEmpty())//������Ϊ��
    {
        if(!UIDATAMGR->IsValidIp(CT2A(strDeviceIp)))
        {
            IRkcToolCommonOp::EnableControl(true, m_pm, _T("SaveNetWorkBut"));
            return;
        }
    }
    else
    {
        IRkcToolCommonOp::EnableControl(true, m_pm, _T("SaveNetWorkBut"));
        return;
    }
    u32 dwDevIP = inet_addr(CT2A(strDeviceIp));
    if (tRK100NetParam.dwIP != dwDevIP)
    {
        IRkcToolCommonOp::EnableControl(true, m_pm, _T("SaveNetWorkBut"));
        return;
    }
    //������������
    CString strDeviceSubmask = (IRkcToolCommonOp::GetControlText(m_pm, _T("DeviceSubmaskEdt"))).c_str();
    if (!strDeviceSubmask.IsEmpty())//������Ϊ��
    {
        if(!UIDATAMGR->IsValidIp(CT2A(strDeviceSubmask)))
        {
            IRkcToolCommonOp::EnableControl(true, m_pm, _T("SaveNetWorkBut"));
            return;
        }
    }
    else
    {
        IRkcToolCommonOp::EnableControl(true, m_pm, _T("SaveNetWorkBut"));
        return;
    }
    u32 dwDevSubMask = inet_addr(CT2A(strDeviceSubmask));
    if (tRK100NetParam.dwSubMask != dwDevSubMask)
    {
        IRkcToolCommonOp::EnableControl(true, m_pm, _T("SaveNetWorkBut"));
        return;
    }
    //��������
    CString strDeviceGateway = (IRkcToolCommonOp::GetControlText(m_pm, _T("DeviceGatewayEdt"))).c_str();
    if (!strDeviceGateway.IsEmpty())//������Ϊ��
    {
        if(!UIDATAMGR->IsValidIp(CT2A(strDeviceGateway)))
        {
            IRkcToolCommonOp::EnableControl(true, m_pm, _T("SaveNetWorkBut"));
            return;
        }
    }
    else
    {
        IRkcToolCommonOp::EnableControl(true, m_pm, _T("SaveNetWorkBut"));
        return;
    }
    u32 dwDevGateWay = inet_addr(CT2A(strDeviceGateway));
    if (tRK100NetParam.dwGateway != dwDevGateWay)
    {
        IRkcToolCommonOp::EnableControl(true, m_pm, _T("SaveNetWorkBut"));
        return;
    }
    //MqttIP
    CString strMqttIp = (IRkcToolCommonOp::GetControlText(m_pm, _T("MqttIPEdt"))).c_str();
    if (!strMqttIp.IsEmpty())//������Ϊ��
    {
        if(!UIDATAMGR->IsValidIp(CT2A(strMqttIp)))
        {
            IRkcToolCommonOp::EnableControl(true, m_pm, _T("SaveNetWorkBut"));
            return;
        }
    }
    else
    {
        IRkcToolCommonOp::EnableControl(true, m_pm, _T("SaveNetWorkBut"));
        return;
    }
    u32 dwDevMqttIP = inet_addr(CT2A(strMqttIp));
    if (tRK100NetParam.dwMqttIP != dwDevMqttIP)
    {
        IRkcToolCommonOp::EnableControl(true, m_pm, _T("SaveNetWorkBut"));
        return;
    }
    //MqttPort
    CString strMqttPort = (IRkcToolCommonOp::GetControlText(m_pm, _T("MqttPortEdt"))).c_str();
    if (strMqttPort.IsEmpty())//������Ϊ��
    {
        IRkcToolCommonOp::EnableControl(true, m_pm, _T("SaveNetWorkBut"));
        return;
    }
    u16 dwMqttPort = _ttoi(strMqttPort);
    if (1 > dwMqttPort || dwMqttPort > 65535)
    {
        IRkcToolCommonOp::EnableControl(true, m_pm, _T("SaveNetWorkBut"));
        return;
    }
    if (tRK100NetParam.MqttPort != dwMqttPort)
    {
        IRkcToolCommonOp::EnableControl(true, m_pm, _T("SaveNetWorkBut"));
        return;
    }

    IRkcToolCommonOp::EnableControl(false, m_pm, _T("SaveNetWorkBut"));
}
