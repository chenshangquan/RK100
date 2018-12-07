#include "stdafx.h"
#include "searchequipmentlogic.h"
#include "debugmodelogic.h"
#include "tipboxlogic.h"
#include "messageboxlogic.h"

template<> CDebugModeLogic* Singleton<CDebugModeLogic>::ms_pSingleton  = NULL;

APP_BEGIN_MSG_MAP(CDebugModeLogic, CNotifyUIImpl)

    MSG_CLICK(_T("SaveDebugModeBut"), OnSaveDebugModeButClicked)
    MSG_SELECTCHANGE(_T("DebugSwitchOpt"), OnDebugSwitchOptSel)

    USER_MSG(UI_RKC_DEBUGMODE_FLESH , OnRkcDebugModeReflesh)
    USER_MSG(UI_RKC_DEBUGMODE_CHANGE , OnRkcDebugModeChangeRsp)

APP_END_MSG_MAP()

CDebugModeLogic::CDebugModeLogic()
{
}

CDebugModeLogic::~CDebugModeLogic()
{
}

bool CDebugModeLogic::OnSaveDebugModeButClicked()
{
    TRK100DebugMode tRK100DebugInfo;
    memset(&tRK100DebugInfo, 0, sizeof(TRK100DebugMode));
    CRkcComInterface->GetDebugConfig(tRK100DebugInfo);
    bool bIsChange = false;
    bool bIsOpen = IRkcToolCommonOp::IsOptionSelected(m_pm, _T("DebugSwitchOpt"));
    if (bIsOpen)
    {
        if (tRK100DebugInfo.DebugSW == 0)
        {
            tRK100DebugInfo.DebugSW = 1;
            bIsChange = true;
        }
    }
    else
    {
        if (tRK100DebugInfo.DebugSW == 1)
        {
            tRK100DebugInfo.DebugSW = 0;
            bIsChange = true;
        }
    }
    if (bIsChange)
    {
        CRkcComInterface->SetDebugConfig(tRK100DebugInfo);
    }
    return true;
}

bool CDebugModeLogic::OnSaveDebugModeButClicked(TNotifyUI& msg)
{
    return OnSaveDebugModeButClicked();
}

bool CDebugModeLogic::OnDebugSwitchOptSel(TNotifyUI& msg)
{
    SetSaveBtnEnable();
    return true;
}

void CDebugModeLogic::SetSaveBtnEnable()
{
    TRK100DebugMode tRK100DebugInfo;
    memset(&tRK100DebugInfo, 0, sizeof(TRK100DebugMode));
    CRkcComInterface->GetDebugConfig(tRK100DebugInfo);
    bool bIsOpen = IRkcToolCommonOp::IsOptionSelected(m_pm, _T("DebugSwitchOpt"));
    if (bIsOpen)
    {
        if (tRK100DebugInfo.DebugSW == 0)
        {
            IRkcToolCommonOp::EnableControl(true, m_pm, _T("SaveDebugModeBut"));
            return;
        }
    }
    else
    {
        if (tRK100DebugInfo.DebugSW == 1)
        {
            IRkcToolCommonOp::EnableControl(true, m_pm, _T("SaveDebugModeBut"));
            return;
        }
    }
    IRkcToolCommonOp::EnableControl(false, m_pm, _T("SaveDebugModeBut"));
    return;
}

bool CDebugModeLogic::OnRkcDebugModeReflesh( WPARAM wparam, LPARAM lparam, bool& bHandle )
{
    bool bGetSuccess = (bool)wparam;
    if (bGetSuccess == false)
    {
        CRkcComInterface->GetDebugConfig();
        return false;
    }

    TRK100DebugMode tRK100DebugInfo;
    memset(&tRK100DebugInfo, 0, sizeof(TRK100DebugMode));
    CRkcComInterface->GetDebugConfig(tRK100DebugInfo);

    if (tRK100DebugInfo.DebugSW == 0)
    {
        IRkcToolCommonOp::OptionSelect(false, m_pm, _T("DebugSwitchOpt"));
    }
    else
    {
        IRkcToolCommonOp::OptionSelect(true, m_pm, _T("DebugSwitchOpt"));
    }
    IRkcToolCommonOp::EnableControl(false, m_pm, _T("SaveDebugModeBut"));
    return true;
}

bool CDebugModeLogic::OnRkcDebugModeChangeRsp( WPARAM wparam, LPARAM lparam, bool& bHandle )
{
    bool bSuccess = (bool)wparam;
    if (bSuccess)
    {
        CRkcComInterface->GetDebugConfig();
        int nBoxRe = ShowMessageBox(_T("修改调试模式需要重启设备，是否确定重启？"),2);
        if (nBoxRe == IDOK)
        {
            CRkcComInterface->ReBootRk();
        }
    }
    else
    {
        ShowTipBox(_T("保存失败"));
    }
    return true;
}