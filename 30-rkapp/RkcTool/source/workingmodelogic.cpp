#include "stdafx.h"
#include "searchequipmentlogic.h"
#include "workingmodelogic.h"
#include "messageboxlogic.h"

template<> CWorkingModeLogic* Singleton<CWorkingModeLogic>::ms_pSingleton  = NULL;

APP_BEGIN_MSG_MAP(CWorkingModeLogic, CNotifyUIImpl)
    MSG_SELECTCHANGE(_T("OpenRelayOpt"), OnTabOpenRelay)
    MSG_SELECTCHANGE(_T("CloseRelayOpt"), OnTabCloseRelay)

    MSG_CLICK(_T("SaveWorkModeBut"), OnSaveWorkModeButClicked)
    MSG_SELECTCHANGE(_T("EnableForOpenOpt"), OnEditTextChange)
    MSG_SELECTCHANGE(_T("DisEnableForOpenOpt"), OnEditTextChange)
    MSG_SELECTCHANGE(_T("EnableForCloseOpt"), OnEditTextChange)
    MSG_SELECTCHANGE(_T("DisEnableForCloseOpt"), OnEditTextChange)
    MSG_EDITCHANGE(_T("OpenDelayEdt"), OnEditTextChange)
    MSG_EDITCHANGE(_T("CloseDelayEdt"), OnEditTextChange)

    USER_MSG(UI_RKC_WORKMODE_REFLESH , OnRkcWorkModeReflesh)

APP_END_MSG_MAP()

CWorkingModeLogic::CWorkingModeLogic()
{
}

CWorkingModeLogic::~CWorkingModeLogic()
{
}


bool CWorkingModeLogic::OnTabOpenRelay(TNotifyUI& msg)
{
    CTabLayoutUI* pRelayTab = (CTabLayoutUI*)IRkcToolCommonOp::FindControl( m_pm, _T("RelayACTab") );
    if (pRelayTab)
    {
        pRelayTab->SelectItem(emTabID_OpenReday);
    }
    return true;
}

bool CWorkingModeLogic::OnTabCloseRelay(TNotifyUI& msg)
{
    CTabLayoutUI* pRelayTab = (CTabLayoutUI*)IRkcToolCommonOp::FindControl( m_pm, _T("RelayACTab") );
    if (pRelayTab)
    {
        pRelayTab->SelectItem(emTabID_CloseReday);
    }
    return true;
}

bool CWorkingModeLogic::OnSaveWorkModeButClicked()
{
    TRK100WorkMode tRK100WorkMode;
    memset(&tRK100WorkMode, 0, sizeof(TRK100WorkMode));
    CRkcComInterface->GetWorkModeConfig(tRK100WorkMode);

    bool bIsChange = false;
    //开机继电
    bool bIsEnableOpen = IRkcToolCommonOp::IsOptionSelected( m_pm , _T("EnableForOpenOpt") );
    if (bIsEnableOpen)
    {
        if (tRK100WorkMode.FuncMod[0].AcFlag == 0)
        {
            tRK100WorkMode.FuncMod[0].AcFlag = 1;
            bIsChange = true;
        }
    }
    else
    {
        if (tRK100WorkMode.FuncMod[0].AcFlag == 1)
        {
            tRK100WorkMode.FuncMod[0].AcFlag = 0;
            bIsChange = false;
        }
    }
    CString strOpenDelay = (IRkcToolCommonOp::GetControlText(m_pm, _T("OpenDelayEdt"))).c_str();
    u8 nOpenDelay = _ttoi(strOpenDelay);
    if (0 > nOpenDelay || nOpenDelay > 180)
    {
        ShowMessageBox(_T("继电延迟在0-180s之间。"));
        return false;
    }
    if (nOpenDelay != tRK100WorkMode.FuncMod[0].AcDelay)
    {
        tRK100WorkMode.FuncMod[0].AcDelay = nOpenDelay;
        bIsChange = true;
    }
    //关机继电
    bool bIsEnableClose = IRkcToolCommonOp::IsOptionSelected( m_pm , _T("EnableForCloseOpt") );
    if (bIsEnableClose)
    {
        if (tRK100WorkMode.FuncMod[1].AcFlag == 0)
        {
            tRK100WorkMode.FuncMod[1].AcFlag = 1;
            bIsChange = true;
        }
    }
    else
    {
        if (tRK100WorkMode.FuncMod[1].AcFlag == 1)
        {
            tRK100WorkMode.FuncMod[1].AcFlag = 0;
            bIsChange = false;
        }
    }
    CString strCloseDelay = (IRkcToolCommonOp::GetControlText(m_pm, _T("CloseDelayEdt"))).c_str();
    u8 nCloseDelay = _ttoi(strCloseDelay);
    if (0 > nCloseDelay || nCloseDelay > 180)
    {
        ShowMessageBox(_T("继电延迟在0-180s之间。"));
        return false;
    }
    if (nCloseDelay != tRK100WorkMode.FuncMod[1].AcDelay)
    {
        tRK100WorkMode.FuncMod[1].AcDelay = nCloseDelay;
        bIsChange = true;
    }
    if (bIsChange)
    {
        CRkcComInterface->SetWorkModeConfig(tRK100WorkMode);
    }
    return true;
}

bool CWorkingModeLogic::OnSaveWorkModeButClicked(TNotifyUI& msg)
{
    return OnSaveWorkModeButClicked();
}

bool CWorkingModeLogic::OnEditTextChange(TNotifyUI& msg)
{
    SetSaveBtnEnable();
    return true;
}

bool CWorkingModeLogic::OnRkcWorkModeReflesh( WPARAM wparam, LPARAM lparam, bool& bHandle )
{
    bool bGetSuccess = (bool)wparam;
    if (bGetSuccess == false)
    {
        CRkcComInterface->GetWorkModeConfig();
        return false;
    }

    TRK100WorkMode tRK100WorkMode;
    memset(&tRK100WorkMode, 0, sizeof(TRK100WorkMode));
    CRkcComInterface->GetWorkModeConfig(tRK100WorkMode);

    if (tRK100WorkMode.FuncMod[0].AcFlag == 0)
    {
        IRkcToolCommonOp::OptionSelect(true , m_pm, _T("DisEnableForOpenOpt") );
    }
    else
    {
        IRkcToolCommonOp::OptionSelect(true , m_pm, _T("EnableForOpenOpt") );
    }
    CString strOpendelay = _T("");
    strOpendelay.Format(_T("%d"), tRK100WorkMode.FuncMod[0].AcDelay);
    IRkcToolCommonOp::SetControlText(strOpendelay, m_pm, _T("OpenDelayEdt"));

    if (tRK100WorkMode.FuncMod[1].AcFlag == 0)
    {
        IRkcToolCommonOp::OptionSelect(true , m_pm, _T("DisEnableForCloseOpt") );
    }
    else
    {
        IRkcToolCommonOp::OptionSelect(true , m_pm, _T("EnableForCloseOpt") );
    }
    CString strClosedelay = _T("");
    strClosedelay.Format(_T("%d"), tRK100WorkMode.FuncMod[1].AcDelay);
    IRkcToolCommonOp::SetControlText(strClosedelay, m_pm, _T("CloseDelayEdt"));

    IRkcToolCommonOp::EnableControl(false, m_pm, _T("SaveWorkModeBut"));

    return true;
}

void CWorkingModeLogic::SetSaveBtnEnable()
{
    TRK100WorkMode tRK100WorkMode;
    memset(&tRK100WorkMode, 0, sizeof(TRK100WorkMode));
    CRkcComInterface->GetWorkModeConfig(tRK100WorkMode);

    bool bIsChange = false;
    //开机继电
    bool bIsEnableOpen = IRkcToolCommonOp::IsOptionSelected( m_pm , _T("EnableForOpenOpt") );
    if (bIsEnableOpen)
    {
        if (tRK100WorkMode.FuncMod[0].AcFlag == 0)
        {
            IRkcToolCommonOp::EnableControl(true, m_pm, _T("SaveWorkModeBut"));
            return;
        }
    }
    else
    {
        if (tRK100WorkMode.FuncMod[0].AcFlag == 1)
        {
            IRkcToolCommonOp::EnableControl(true, m_pm, _T("SaveWorkModeBut"));
            return;
        }
    }
    CString strOpenDelay = (IRkcToolCommonOp::GetControlText(m_pm, _T("OpenDelayEdt"))).c_str();
    u8 nOpenDelay = _ttoi(strOpenDelay);
    if (0 > nOpenDelay || nOpenDelay > 180)
    {
        IRkcToolCommonOp::EnableControl(true, m_pm, _T("SaveWorkModeBut"));
        return;
    }
    if (nOpenDelay != tRK100WorkMode.FuncMod[0].AcDelay)
    {
        IRkcToolCommonOp::EnableControl(true, m_pm, _T("SaveWorkModeBut"));
        return;
    }
    //关机继电
    bool bIsEnableClose = IRkcToolCommonOp::IsOptionSelected( m_pm , _T("EnableForCloseOpt") );
    if (bIsEnableClose)
    {
        if (tRK100WorkMode.FuncMod[1].AcFlag == 0)
        {
            IRkcToolCommonOp::EnableControl(true, m_pm, _T("SaveWorkModeBut"));
            return;
        }
    }
    else
    {
        if (tRK100WorkMode.FuncMod[1].AcFlag == 1)
        {
            IRkcToolCommonOp::EnableControl(true, m_pm, _T("SaveWorkModeBut"));
            return;
        }
    }
    CString strCloseDelay = (IRkcToolCommonOp::GetControlText(m_pm, _T("CloseDelayEdt"))).c_str();
    u8 nCloseDelay = _ttoi(strCloseDelay);
    if (0 > nCloseDelay || nCloseDelay > 180)
    {
        IRkcToolCommonOp::EnableControl(true, m_pm, _T("SaveWorkModeBut"));
        return;
    }
    if (nCloseDelay != tRK100WorkMode.FuncMod[1].AcDelay)
    {
        IRkcToolCommonOp::EnableControl(true, m_pm, _T("SaveWorkModeBut"));
        return;
    }

    IRkcToolCommonOp::EnableControl(false, m_pm, _T("SaveWorkModeBut"));
    return;
}