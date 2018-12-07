#include "stdafx.h"
#include "searchequipmentlogic.h"
#include "ToolFrameLogic.h"
#include "messageboxlogic.h"
#include "networksetuplogic.h"
#include "radiosetuplogic.h"
#include "debugmodelogic.h"
#include "workingmodelogic.h"
#include "modifypasswordlogic.h"

#define    BOTTOM_STRING    "设备IP:%s  设备型号:%s  版本号:%s  电流:%.3fA  功耗:%.3fW/H"      //用于下行leb显示

template<> CToolFrameLogic* Singleton<CToolFrameLogic>::ms_pSingleton  = NULL;

static UINT g_nMsgPowerTimerID;   //功耗信息实时获取定时器
VOID  CALLBACK  CToolFrameTimerPoc( HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime )
{
    if ( idEvent == g_nMsgPowerTimerID )
    {
        CRkcComInterface->GetPowerConfig();
    }
}

APP_BEGIN_MSG_MAP(CToolFrameLogic, CNotifyUIImpl)
    MSG_CREATEWINDOW(_T("ToolFrameLayout"), OnCreate)
    MSG_INIWINDOW(_T("ToolFrameLayout"), OnInit)

    MSG_SELECTCHANGE(_T("NetworkSetupOpt"), OnTabNetworkSetup)
    MSG_SELECTCHANGE(_T("RadioSetupOpt"), OnTabRadioSetup)
    MSG_SELECTCHANGE(_T("WorkingModeOpt"), OnTabWorkingMode)
    MSG_SELECTCHANGE(_T("BackupUpgradeOpt"), OnTabBackupUpgrade)
    MSG_SELECTCHANGE(_T("DebugModeOpt"), OnTabDebugModel)

    USER_MSG(UI_RKC_POWER_FLESH , OnRkcPowerReflesh)
    USER_MSG(UI_RKC_DISCONNECTED , OnRkcDisconnected)

APP_END_MSG_MAP()

CToolFrameLogic::CToolFrameLogic()
{
    g_nMsgPowerTimerID = 0;
    m_bIsFirstLogin = false;
}

CToolFrameLogic::~CToolFrameLogic()
{
}

bool CToolFrameLogic::OnCreate( TNotifyUI& msg )
{
    s32 nTop = DEFAULT_TITLE_HEIGHT;
    if ( CPaintManagerUI::IsSelfAdaption() )
    {
        float fAdpX, fAdpY;
        CPaintManagerUI::GetAdpResolution( &fAdpX, &fAdpY );
        nTop = s32(nTop * fAdpY);
    }
    SetWindowPos( m_pm->GetPaintWindow(), NULL, 0, nTop, 0, 0, SWP_NOSIZE |SWP_NOACTIVATE );
    return false;
}

bool CToolFrameLogic::OnInit( TNotifyUI& msg )
{
    REG_RCKTOOL_MSG_WND_OB(m_pm->GetPaintWindow());

    // 密码修改帮助窗口创建
    CModifyPasswordLogic::GetSingletonPtr()->OnGreatePwdHelpWind();

    CRkcComInterface->KillTftpProcess();
    NOTIFY_MSG(UI_RKC_POWER_FLESH);
    NOTIFY_MSG(UI_RKC_NETWORK_REFLESH, TRUE, 0);
    NOTIFY_MSG(UI_RKC_WORKMODE_REFLESH, TRUE, 0);
    NOTIFY_MSG(UI_RKC_DEBUGMODE_FLESH, TRUE, 0);
    if (m_bIsFirstLogin)
    {
        CTabLayoutUI *pControl = (CTabLayoutUI*)IRkcToolCommonOp::FindControl( m_pm, _T("ToolFrameSlideTab") );
        if (pControl)
        {
            pControl->SelectItem(emTabID_ModifyPassword);
        }
        m_pm->DoCase(_T("caseMenuItemSel"));
    }

    return true;
}

bool CToolFrameLogic::OnMsgNotify(TNotifyUI& msg)
{
    CSearchEquipmentLogic::GetSingletonPtr()->SetTimerOutTimer(true);
    return true;
}

void CToolFrameLogic::InitBottomLeb()
{
    TDevItem tLoginDevitem;
    CRkcComInterface->GetLoginDevItem(tLoginDevitem);
    u32 dwIP = htonl(tLoginDevitem.tDevInfo.tAddr.dwIpaddr);
    char achBottom[256] = {0};
    sprintf(achBottom, BOTTOM_STRING, inet_ntoa(*(in_addr*)&dwIP), tLoginDevitem.tDevID.achDevType, tLoginDevitem.tDevEx.achDevSoftVersion, 0.0, 0.0);
    IRkcToolCommonOp::SetControlText( CA2T(achBottom) , m_pm ,_T("BottomLeb"));
    IRkcToolCommonOp::SetControlText( CA2T(tLoginDevitem.tDevEx.achDevSoftVersion), m_pm, _T("BuildVersion"));    // 获取关于界面软件版本号信息
//     IRkcToolCommonOp::SetControlText( CA2T(inet_ntoa(*(in_addr*)&dwIP)) , m_pm ,_T("BottomIPLeb"));
//     IRkcToolCommonOp::SetControlText( CA2T(tLoginDevitem.tDevID.achDevType) , m_pm ,_T("BottomTypeLeb"));
//     IRkcToolCommonOp::SetControlText( CA2T(tLoginDevitem.tDevEx.achDevSoftVersion) , m_pm ,_T("BottomVerLeb"));

    //登录成功 获取配置数据内容
    CRkcComInterface->GetWorkModeConfig();
    CRkcComInterface->GetNetWorkConfig();
    CRkcComInterface->GetPowerConfig();
    CRkcComInterface->GetDebugConfig();
    g_nMsgPowerTimerID = SetTimer( NULL, NULL, 5000, CToolFrameTimerPoc );
}

void CToolFrameLogic::SetFirstLogin(bool bFirstLogin)
{
    m_bIsFirstLogin = bFirstLogin;
    if (m_bIsFirstLogin)
    {
        CTabLayoutUI *pControl = (CTabLayoutUI*)IRkcToolCommonOp::FindControl( m_pm, _T("ToolFrameSlideTab") );
        if (pControl)
        {
            pControl->SelectItem(emTabID_ModifyPassword);
        }
        m_pm->DoCase(_T("caseMenuItemSel"));
    }
}

bool CToolFrameLogic::IsFirstLogin()
{
    return m_bIsFirstLogin;
}

bool CToolFrameLogic::OnTabNetworkSetup(TNotifyUI& msg)
{
    if (IsFirstLogin())//密码修改强制不可切换tab
    {
        m_pm->DoCase(_T("caseMenuItemSel"));
        return false;
    }
    CTabLayoutUI *pControl = (CTabLayoutUI*)IRkcToolCommonOp::FindControl( m_pm, _T("ToolFrameSlideTab") );
    if (pControl)
    {
        //是否已经退出登录 此时不需要进行修改判断
        if (CRkcComInterface->IsLoginState() == false)
        {
            pControl->SelectItem(emTabID_NetworkSetup);
            return false;
        }
        //修改判断
        if (IsConfigChange())
        {
            pControl->SelectItem(emTabID_NetworkSetup);
        }
        else
        {
            COptionUI* pMsgSpender = (COptionUI*)msg.pSender;
            if (pMsgSpender)
            {
                pMsgSpender->SetCheckNoMsg(false);
            }
            switch(pControl->GetCurSel())
            {
            case emTabID_NetworkSetup:
                IRkcToolCommonOp::OptionSelectNoMsg(true,m_pm,_T("NetworkSetupOpt"));
                break;
            case emTabID_RadioSetup:
                IRkcToolCommonOp::OptionSelectNoMsg(true,m_pm,_T("RadioSetupOpt"));
                break;
            case emTabID_WorkingMode:
                IRkcToolCommonOp::OptionSelectNoMsg(true,m_pm,_T("WorkingModeOpt"));
                break;
            case emTabID_BackupUpgrade:
                IRkcToolCommonOp::OptionSelectNoMsg(true,m_pm,_T("BackupUpgradeOpt"));
                break;
            case emTabID_DebugMode:
                IRkcToolCommonOp::OptionSelectNoMsg(true,m_pm,_T("DebugModeOpt"));
                break;
            default:
                break;
            }
        }
    }
    return true;
}

bool CToolFrameLogic::OnTabRadioSetup(TNotifyUI& msg)
{
    if (IsFirstLogin())//密码修改强制不可切换tab
    {
        m_pm->DoCase(_T("caseMenuItemSel"));
        return false;
    }
    CTabLayoutUI *pControl = (CTabLayoutUI*)IRkcToolCommonOp::FindControl( m_pm, _T("ToolFrameSlideTab") );
    if (pControl)
    {
        if (IsConfigChange())
        {
            pControl->SelectItem(emTabID_RadioSetup);
        }
        else
        {
            COptionUI* pMsgSpender = (COptionUI*)msg.pSender;
            if (pMsgSpender)
            {
                pMsgSpender->SetCheckNoMsg(false);
            }
            switch(pControl->GetCurSel())
            {
            case emTabID_NetworkSetup:
                IRkcToolCommonOp::OptionSelectNoMsg(true,m_pm,_T("NetworkSetupOpt"));
                break;
            case emTabID_RadioSetup:
                IRkcToolCommonOp::OptionSelectNoMsg(true,m_pm,_T("RadioSetupOpt"));
                break;
            case emTabID_WorkingMode:
                IRkcToolCommonOp::OptionSelectNoMsg(true,m_pm,_T("WorkingModeOpt"));
                break;
            case emTabID_BackupUpgrade:
                IRkcToolCommonOp::OptionSelectNoMsg(true,m_pm,_T("BackupUpgradeOpt"));
                break;
            case emTabID_DebugMode:
                IRkcToolCommonOp::OptionSelectNoMsg(true,m_pm,_T("DebugModeOpt"));
                break;
            default:
                break;
            }
        }
    }
    return true;
}

bool CToolFrameLogic::OnTabWorkingMode(TNotifyUI& msg)
{
    if (IsFirstLogin())//密码修改强制不可切换tab
    {
        m_pm->DoCase(_T("caseMenuItemSel"));
        return false;
    }
    CTabLayoutUI *pControl = (CTabLayoutUI*)IRkcToolCommonOp::FindControl( m_pm, _T("ToolFrameSlideTab") );
    if (pControl)
    {
        if (IsConfigChange())
        {
            pControl->SelectItem(emTabID_WorkingMode);
        }
        else
        {
            COptionUI* pMsgSpender = (COptionUI*)msg.pSender;
            if (pMsgSpender)
            {
                pMsgSpender->SetCheckNoMsg(false);
            }
            switch(pControl->GetCurSel())
            {
            case emTabID_NetworkSetup:
                IRkcToolCommonOp::OptionSelectNoMsg(true,m_pm,_T("NetworkSetupOpt"));
                break;
            case emTabID_RadioSetup:
                IRkcToolCommonOp::OptionSelectNoMsg(true,m_pm,_T("RadioSetupOpt"));
                break;
            case emTabID_WorkingMode:
                IRkcToolCommonOp::OptionSelectNoMsg(true,m_pm,_T("WorkingModeOpt"));
                break;
            case emTabID_BackupUpgrade:
                IRkcToolCommonOp::OptionSelectNoMsg(true,m_pm,_T("BackupUpgradeOpt"));
                break;
            case emTabID_DebugMode:
                IRkcToolCommonOp::OptionSelectNoMsg(true,m_pm,_T("DebugModeOpt"));
                break;
            default:
                break;
            }
        }
    }
    return true;
}

bool CToolFrameLogic::OnTabBackupUpgrade(TNotifyUI& msg)
{
    if (IsFirstLogin())//密码修改强制不可切换tab
    {
        m_pm->DoCase(_T("caseMenuItemSel"));
        return false;
    }
    CTabLayoutUI *pControl = (CTabLayoutUI*)IRkcToolCommonOp::FindControl( m_pm, _T("ToolFrameSlideTab") );
    if (pControl)
    {
        if (IsConfigChange())
        {
            pControl->SelectItem(emTabID_BackupUpgrade);
        }
        else
        {
            COptionUI* pMsgSpender = (COptionUI*)msg.pSender;
            if (pMsgSpender)
            {
                pMsgSpender->SetCheckNoMsg(false);
            }
            switch(pControl->GetCurSel())
            {
            case emTabID_NetworkSetup:
                IRkcToolCommonOp::OptionSelectNoMsg(true,m_pm,_T("NetworkSetupOpt"));
                break;
            case emTabID_RadioSetup:
                IRkcToolCommonOp::OptionSelectNoMsg(true,m_pm,_T("RadioSetupOpt"));
                break;
            case emTabID_WorkingMode:
                IRkcToolCommonOp::OptionSelectNoMsg(true,m_pm,_T("WorkingModeOpt"));
                break;
            case emTabID_BackupUpgrade:
                IRkcToolCommonOp::OptionSelectNoMsg(true,m_pm,_T("BackupUpgradeOpt"));
                break;
            case emTabID_DebugMode:
                IRkcToolCommonOp::OptionSelectNoMsg(true,m_pm,_T("DebugModeOpt"));
                break;
            default:
                break;
            }
        }
    }
    return true;
}

bool CToolFrameLogic::OnTabDebugModel(TNotifyUI& msg)
{
    if (IsFirstLogin())//密码修改强制不可切换tab
    {
        m_pm->DoCase(_T("caseMenuItemSel"));
        return false;
    }
    CTabLayoutUI *pControl = (CTabLayoutUI*)IRkcToolCommonOp::FindControl( m_pm, _T("ToolFrameSlideTab") );
    if (pControl)
    {
        if (IsConfigChange())
        {
            pControl->SelectItem(emTabID_DebugMode);
        }
        else
        {
            COptionUI* pMsgSpender = (COptionUI*)msg.pSender;
            if (pMsgSpender)
            {
                pMsgSpender->SetCheckNoMsg(false);
            }
            switch(pControl->GetCurSel())
            {
            case emTabID_NetworkSetup:
                IRkcToolCommonOp::OptionSelectNoMsg(true,m_pm,_T("NetworkSetupOpt"));
                break;
            case emTabID_RadioSetup:
                IRkcToolCommonOp::OptionSelectNoMsg(true,m_pm,_T("RadioSetupOpt"));
                break;
            case emTabID_WorkingMode:
                IRkcToolCommonOp::OptionSelectNoMsg(true,m_pm,_T("WorkingModeOpt"));
                break;
            case emTabID_BackupUpgrade:
                IRkcToolCommonOp::OptionSelectNoMsg(true,m_pm,_T("BackupUpgradeOpt"));
                break;
            case emTabID_DebugMode:
                IRkcToolCommonOp::OptionSelectNoMsg(true,m_pm,_T("DebugModeOpt"));
                break;
            default:
                break;
            }
        }
    }
    return true;
}

bool CToolFrameLogic::IsConfigChange()
{
    CTabLayoutUI *pControl = (CTabLayoutUI*)IRkcToolCommonOp::FindControl( m_pm, _T("ToolFrameSlideTab") );
    if (pControl)
    {
        int nCurSel = pControl->GetCurSel();
        CVerticalLayoutUI* pVer = (CVerticalLayoutUI*)pControl->GetItemAt(nCurSel);
        if (pVer)
        {
            if (nCurSel == emTabID_NetworkSetup)
            {
                CButtonUI* pSaveButton = (CButtonUI*)IRkcToolCommonOp::FindControl(m_pm,_T("SaveNetWorkBut"),pVer);
                if (pSaveButton->IsEnabled())
                {
                    int nBoxRe = ShowMessageBox(_T("是否保存当前修改内容"),2);
                    if (nBoxRe == IDOK)
                    {
                        return CNetworkSetupLogic::GetSingletonPtr()->OnSaveNetWorkButClicked();
                    }
                    else if (nBoxRe == IDNO)
                    {
                        return false;
                    }
                    else
                    {
                        CRkcComInterface->GetNetWorkConfig();
                        return true;
                    }
                }
            }
            else if (nCurSel == emTabID_RadioSetup)
            {
                CButtonUI* pSaveButton = (CButtonUI*)IRkcToolCommonOp::FindControl(m_pm,_T("SaveRadioBut"),pVer);
                if (pSaveButton->IsEnabled())
                {
                    int nBoxRe = ShowMessageBox(_T("是否保存当前修改内容"),2);
                    if (nBoxRe == IDOK)
                    {
                        return CRadioSetupLogic::GetSingletonPtr()->OnSaveRadioButClicked();
                    }
                    else if (nBoxRe == IDNO)
                    {
                        return false;
                    }
                    else
                    {
                        CRkcComInterface->GetWorkModeConfig();
                        return true;
                    }
                }
            }
            else if (nCurSel == emTabID_WorkingMode)
            {
                CButtonUI* pSaveButton = (CButtonUI*)IRkcToolCommonOp::FindControl(m_pm,_T("SaveWorkModeBut"),pVer);
                if (pSaveButton->IsEnabled())
                {
                    int nBoxRe = ShowMessageBox(_T("是否保存当前修改内容"),2);
                    if (nBoxRe == IDOK)
                    {
                        return CWorkingModeLogic::GetSingletonPtr()->OnSaveWorkModeButClicked();
                    }
                    else if (nBoxRe == IDNO)
                    {
                        return false;
                    }
                    else
                    {
                        CRkcComInterface->GetWorkModeConfig();
                        return true;
                    }
                }
            }
            else if (nCurSel == emTabID_DebugMode)
            {
                CButtonUI* pSaveButton = (CButtonUI*)IRkcToolCommonOp::FindControl(m_pm,_T("SaveDebugModeBut"),pVer);
                if (pSaveButton->IsEnabled())
                {
                    int nBoxRe = ShowMessageBox(_T("是否保存当前修改内容"),2);
                    if (nBoxRe == IDOK)
                    {
                        return CDebugModeLogic::GetSingletonPtr()->OnSaveDebugModeButClicked();
                    }
                    else if (nBoxRe == IDNO)
                    {
                        return false;
                    }
                    else
                    {
                        CRkcComInterface->GetDebugConfig();
                        return true;
                    }
                }
            }
            else if (nCurSel == emTabID_ModifyPassword)
            {
                return CModifyPasswordLogic::GetSingletonPtr()->IsConfigChange();
            }
        }
    }
    return true;
}

u8 CToolFrameLogic::ExitCheckChange()
{
    CTabLayoutUI *pControl = (CTabLayoutUI*)IRkcToolCommonOp::FindControl( m_pm, _T("ToolFrameSlideTab") );
    if (pControl)
    {
        int nCurSel = pControl->GetCurSel();
        CVerticalLayoutUI* pVer = (CVerticalLayoutUI*)pControl->GetItemAt(nCurSel);
        if (pVer)
        {
            if (nCurSel == emTabID_NetworkSetup)
            {
                CButtonUI* pSaveButton = (CButtonUI*)IRkcToolCommonOp::FindControl(m_pm,_T("SaveNetWorkBut"),pVer);
                if (pSaveButton->IsEnabled())
                {
                    int nBoxRe = ShowMessageBox(_T("是否保存当前修改内容"),2);
                    if (nBoxRe == IDOK)
                    {
                        CNetworkSetupLogic::GetSingletonPtr()->OnSaveNetWorkButClicked();
                        return 1;
                    }
                    else
                    {
                        return 2;
                    }
                }
            }
            else if (nCurSel == emTabID_RadioSetup)
            {
                CButtonUI* pSaveButton = (CButtonUI*)IRkcToolCommonOp::FindControl(m_pm,_T("SaveRadioBut"),pVer);
                if (pSaveButton->IsEnabled())
                {
                    int nBoxRe = ShowMessageBox(_T("是否保存当前修改内容"),2);
                    if (nBoxRe == IDOK)
                    {
                        CRadioSetupLogic::GetSingletonPtr()->OnSaveRadioButClicked();
                        return 1;
                    }
                    else
                    {
                        return 2;
                    }
                }
            }
            else if (nCurSel == emTabID_WorkingMode)
            {
                CButtonUI* pSaveButton = (CButtonUI*)IRkcToolCommonOp::FindControl(m_pm,_T("SaveWorkModeBut"),pVer);
                if (pSaveButton->IsEnabled())
                {
                    int nBoxRe = ShowMessageBox(_T("是否保存当前修改内容"),2);
                    if (nBoxRe == IDOK)
                    {
                        CWorkingModeLogic::GetSingletonPtr()->OnSaveWorkModeButClicked();
                        return 1;
                    }
                    else
                    {
                        return 2;
                    }
                }
            }
            else if (nCurSel == emTabID_DebugMode)
            {
                CButtonUI* pSaveButton = (CButtonUI*)IRkcToolCommonOp::FindControl(m_pm,_T("SaveDebugModeBut"),pVer);
                if (pSaveButton->IsEnabled())
                {
                    int nBoxRe = ShowMessageBox(_T("是否保存当前修改内容"),2);
                    if (nBoxRe == IDOK)
                    {
                        CDebugModeLogic::GetSingletonPtr()->OnSaveDebugModeButClicked();
                        return 1;
                    }
                    else
                    {
                        return 2;
                    }
                }
            }
            else if (nCurSel == emTabID_ModifyPassword)
            {
                return CModifyPasswordLogic::GetSingletonPtr()->ExitCheckChange();
            }
        }
    }
    return 3;
}

bool CToolFrameLogic::OnTabModifyPassword()
{
    CTabLayoutUI *pControl = (CTabLayoutUI*)IRkcToolCommonOp::FindControl( m_pm, _T("ToolFrameSlideTab") );
    if (pControl)
    {
        int nCurSel = pControl->GetCurSel();
        CVerticalLayoutUI* pVer = (CVerticalLayoutUI*)pControl->GetItemAt(nCurSel);
        if (pVer)
        {
            if (nCurSel == emTabID_ModifyPassword)
            {
                if (CModifyPasswordLogic::GetSingletonPtr()->IsConfigChange())
                {
                    CModifyPasswordLogic::GetSingletonPtr()->OnResetAllInput();
                    pControl->SelectItem(NULL);     //重新选择修改密码界面
                    pControl->SelectItem(emTabID_ModifyPassword);
                }
            }
            else
            {
                CModifyPasswordLogic::GetSingletonPtr()->OnResetAllInput();
                pControl->SelectItem(emTabID_ModifyPassword);
            }

            m_pm->DoCase(_T("caseMenuItemSel"));
        }    
    }

    return true;
}

bool CToolFrameLogic::OnTabAboutInfo()
{
    CTabLayoutUI *pControl = (CTabLayoutUI*)IRkcToolCommonOp::FindControl( m_pm, _T("ToolFrameSlideTab") );
    if (pControl)
    {
        int nCurSel = pControl->GetCurSel();
        CVerticalLayoutUI* pVer = (CVerticalLayoutUI*)pControl->GetItemAt(nCurSel);
        if (pVer)
        {
            if (nCurSel == emTabID_ModifyPassword)
            {
                if (CModifyPasswordLogic::GetSingletonPtr()->IsConfigChange())
                {
                    pControl->SelectItem(emTabID_AboutInfo);
                }
            }
            else
            {
                pControl->SelectItem(emTabID_AboutInfo);                
            }

            m_pm->DoCase(_T("caseMenuItemSel"));
        }
    }
    
    return true;
}

bool CToolFrameLogic::OnRkcPowerReflesh( WPARAM wparam, LPARAM lparam, bool& bHandle )
{
    TRK100PowerInfo tRK100PowerInfo;
    memset(&tRK100PowerInfo, 0, sizeof(TRK100PowerInfo));
    CRkcComInterface->GetPowerConfig(tRK100PowerInfo);

    TDevItem tLoginDevitem;
    CRkcComInterface->GetLoginDevItem(tLoginDevitem);

    u32 dwIP = htonl(tLoginDevitem.tDevInfo.tAddr.dwIpaddr);
    char achBottom[256] = {0};
    sprintf(achBottom, BOTTOM_STRING, inet_ntoa(*(in_addr*)&dwIP), tLoginDevitem.tDevID.achDevType, tLoginDevitem.tDevEx.achDevSoftVersion, ((float)tRK100PowerInfo.dwCurrent)/1000, ((float)tRK100PowerInfo.dwPower)/1000);
    IRkcToolCommonOp::SetControlText( CA2T(achBottom) , m_pm ,_T("BottomLeb"));

    return true;
}

bool CToolFrameLogic::OnRkcDisconnected( WPARAM wparam, LPARAM lparam, bool& bHandle )
{
    m_bIsFirstLogin = false;
    KillTimer(NULL, g_nMsgPowerTimerID);
    g_nMsgPowerTimerID = 0;
    WINDOW_MGR_PTR->ShowWindow(g_stcStrToolFrameDlg.c_str(),false);
    m_pm->DoCase(_T("caseIsnotLogin"));
    //选中网络设置
    IRkcToolCommonOp::OptionSelect(true,m_pm,_T("NetworkSetupOpt"));
    return true;
}