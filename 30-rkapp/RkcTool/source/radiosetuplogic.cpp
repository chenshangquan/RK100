#include "stdafx.h"
#include "searchequipmentlogic.h"
#include "radiosetuplogic.h"
#include "messageboxlogic.h"
#include "tipboxlogic.h"

static std::map<char, u8> map16hex;

template<> CRadioSetupLogic* Singleton<CRadioSetupLogic>::ms_pSingleton  = NULL;

APP_BEGIN_MSG_MAP(CRadioSetupLogic, CNotifyUIImpl)
    MSG_INIWINDOW(_T("ToolFrameLayout"), OnInit)

    MSG_CLICK(_T("itemdelbut"), OnItemDelBtnClicked)
    MSG_CLICK(_T("itemaddbut"), OnItemAddBtnClicked)
    MSG_CLICK(_T("SaveRadioBut"), OnSaveRadioButClicked)
    MSG_SELECTCHANGE(_T("RadioSwitchOpt"), OnRadioSwitchOptSel)
    MSG_SELECTCHANGE(_T("OpenRadioOpt"), OnOpenRadioOptSel)
    MSG_SELECTCHANGE(_T("CloseRadioOpt"), OnCloseRadioOptSel)
    MSG_EDITCHANGE(_T("RadioIpEdt"), OnEditTextChange)

    USER_MSG(UI_RKC_WORKMODE_REFLESH , OnRkcRadioReflesh) //工作模式数据内也包含射频ID信息
    USER_MSG(UI_RKC_WORKMODE_CHANGE , OnRkcWorkModeChangeRsp)

APP_END_MSG_MAP()

CRadioSetupLogic::CRadioSetupLogic():m_pPeripheralList(NULL)
{
    map16hex.insert(pair<char, u8>('0', 0));
    map16hex.insert(pair<char, u8>('1', 1));
    map16hex.insert(pair<char, u8>('2', 2));
    map16hex.insert(pair<char, u8>('3', 3));
    map16hex.insert(pair<char, u8>('4', 4));
    map16hex.insert(pair<char, u8>('5', 5));
    map16hex.insert(pair<char, u8>('6', 6));
    map16hex.insert(pair<char, u8>('7', 7));
    map16hex.insert(pair<char, u8>('8', 8));
    map16hex.insert(pair<char, u8>('9', 9));
    map16hex.insert(pair<char, u8>('A', 10));
    map16hex.insert(pair<char, u8>('B', 11));
    map16hex.insert(pair<char, u8>('C', 12));
    map16hex.insert(pair<char, u8>('D', 13));
    map16hex.insert(pair<char, u8>('E', 14));
    map16hex.insert(pair<char, u8>('F', 15));
}

CRadioSetupLogic::~CRadioSetupLogic()
{
}

bool CRadioSetupLogic::OnInit(TNotifyUI& msg)
{
   
    return true;
}

bool CRadioSetupLogic::OnItemDelBtnClicked(TNotifyUI& msg)
{
    if (m_pPeripheralList)
    {
        m_pPeripheralList->Remove(msg.pSender->GetParent());
        if (m_pPeripheralList->GetCount() == 0)
        {
            CListContainerElementUI *pListContainer = (CListContainerElementUI*)CONTROLFACTORY()->GetControl( _T("PeripheralListItem") );
            if (pListContainer)
            {
                COptionUI* pOpOpen = (COptionUI*)IRkcToolCommonOp::FindControl(m_pm,_T("OpenRadioOpt"),pListContainer);
                COptionUI* pOpClose = (COptionUI*)IRkcToolCommonOp::FindControl(m_pm,_T("CloseRadioOpt"),pListContainer);
                if (pOpClose && pOpOpen)
                {
                    CString strGroup = _T("");
                    strGroup.Format(_T("itemgroup%d"),m_pPeripheralList->GetCount());
                    pOpOpen->SetGroup(strGroup);
                    pOpClose->SetGroup(strGroup);
                }

                m_pm->DoCase(_T("NoRadio") ,pListContainer);
                m_pPeripheralList->Add(pListContainer);
            }
        }
        else
        {
            CListContainerElementUI *pListContainer = (CListContainerElementUI*)m_pPeripheralList->GetItemAt(m_pPeripheralList->GetCount()-1);
            if (pListContainer)
            {
                m_pm->DoCase(_T("LastRadio") ,pListContainer);
            }
        }
    }
    SetSaveBtnEnable();
    return true;
}

bool CRadioSetupLogic::OnItemAddBtnClicked(TNotifyUI& msg)
{
    if (m_pPeripheralList)
    {
        if (msg.pSender->GetTag() != 1)
        {
            m_pm->DoCase(_T("NormalRadio") ,msg.pSender->GetParent());
            CListContainerElementUI *pListContainer = (CListContainerElementUI*)CONTROLFACTORY()->GetControl( _T("PeripheralListItem") );
            if (pListContainer)
            {
                COptionUI* pOpOpen = (COptionUI*)IRkcToolCommonOp::FindControl(m_pm,_T("OpenRadioOpt"),pListContainer);
                COptionUI* pOpClose = (COptionUI*)IRkcToolCommonOp::FindControl(m_pm,_T("CloseRadioOpt"),pListContainer);
                if (pOpClose && pOpOpen)
                {
                    CString strGroup = _T("");
                    strGroup.Format(_T("itemgroup%d"),m_pPeripheralList->GetCount());
                    pOpOpen->SetGroup(strGroup);
                    pOpClose->SetGroup(strGroup);
                }

                if (m_pPeripheralList->GetCount() == 4)
                {
                    m_pm->DoCase(_T("NormalRadio") ,pListContainer);
                }
                else
                {
                    m_pm->DoCase(_T("LastRadio") ,pListContainer);
                }
                m_pPeripheralList->Add(pListContainer);
            }
        }
        else
        {
            m_pm->DoCase(_T("LastRadio") ,msg.pSender->GetParent());
        }
    }
    SetSaveBtnEnable();
    return true;
}

bool CRadioSetupLogic::OnSaveRadioButClicked()
{
    TRK100WorkMode tRK100WorkMode;
    memset(&tRK100WorkMode, 0, sizeof(TRK100WorkMode));
    CRkcComInterface->GetWorkModeConfig(tRK100WorkMode);

    //射频开关
    bool bIsChanged = false;//没有数据改变
    bool bisopen = IRkcToolCommonOp::IsOptionSelected( m_pm , _T("RadioSwitchOpt") );
    if (bisopen)
    {
        if (tRK100WorkMode.FuncMod[0].RfFlag == 0)
        {
            tRK100WorkMode.FuncMod[0].RfFlag = 1;
            bIsChanged = true;
        }
    }
    else
    {
        if (tRK100WorkMode.FuncMod[0].RfFlag == 1)
        {
            tRK100WorkMode.FuncMod[0].RfFlag = 0;
            bIsChanged = true;
        }
    }
    //射频ID
    m_pPeripheralList = (CListUI*)IRkcToolCommonOp::FindControl( m_pm, _T("PeripheralList") );
    if (m_pPeripheralList)
    {
        for (u8 i = 0 ; i < MAX_RADIO_COUNT ; i++)
        {
            u8 awRfID[5] = {0};
            if (i >= m_pPeripheralList->GetCount())
            {
                awRfID[0] = 0;
                awRfID[1] = 0;
                awRfID[2] = 0;
                awRfID[3] = 0;
                awRfID[4] = 0;
            }
            else
            {
                CListContainerElementUI *pListContainer = (CListContainerElementUI*)m_pPeripheralList->GetItemAt(i);
                CButtonUI* pButtonAdd = (CButtonUI*)IRkcToolCommonOp::FindControl(m_pm,_T("itemaddbut"),pListContainer);
                if (pButtonAdd && pButtonAdd->GetTag() == 1)
                {
                    awRfID[0] = 0;
                    awRfID[1] = 0;
                    awRfID[2] = 0;
                    awRfID[3] = 0;
                    awRfID[4] = 0;
                }
                else
                {
                    string strID = CT2A(IRkcToolCommonOp::GetControlText(m_pm, _T("RadioIpEdt"), pListContainer).c_str());
                    if (strID.size() != 8 || strcmp(strID.c_str(), "00000000") == 0)
                    {
                        ShowMessageBox(_T("射频ID格式错误！"));
                        return false;
                    }
                    transform(strID.begin(), strID.end(), strID.begin(), ::toupper);
                    for (u8 Index = 0 ; Index < strID.size() ; Index++)
                    {
                        if (strID[Index] < '0' || (strID[Index] > '9' && strID[Index] < 'A') || strID[Index] > 'F')
                        {
                            ShowMessageBox(_T("射频ID格式错误！"));
                            return false;
                        }
                    }
                    awRfID[0] = (IRkcToolCommonOp::IsOptionSelected(m_pm,_T("OpenRadioOpt"),pListContainer) ? 1 : 0);
                    awRfID[1] = map16hex[strID[0]] * 16 + map16hex[strID[1]];
                    awRfID[2] = map16hex[strID[2]] * 16 + map16hex[strID[3]];
                    awRfID[3] = map16hex[strID[4]] * 16 + map16hex[strID[5]];
                    awRfID[4] = map16hex[strID[6]] * 16 + map16hex[strID[7]];
                }
            }

            if (tRK100WorkMode.FuncMod[0].RfID[i][0] == awRfID[0] &&
                tRK100WorkMode.FuncMod[0].RfID[i][1] == awRfID[1] && 
                tRK100WorkMode.FuncMod[0].RfID[i][2] == awRfID[2] && 
                tRK100WorkMode.FuncMod[0].RfID[i][3] == awRfID[3] && 
                tRK100WorkMode.FuncMod[0].RfID[i][4] == awRfID[4])
            {

            }
            else
            {
                //判断重复
                for (unsigned int iIndex = 0 ; iIndex < i ; iIndex++)
                {
                    if ((awRfID[1] != 0 || awRfID[2] != 0 || awRfID[3] != 0 || awRfID[4] != 0) &&
                         awRfID[1] == tRK100WorkMode.FuncMod[0].RfID[iIndex][1] && 
                         awRfID[2] == tRK100WorkMode.FuncMod[0].RfID[iIndex][2] &&
                         awRfID[3] == tRK100WorkMode.FuncMod[0].RfID[iIndex][3] &&
                         awRfID[4] == tRK100WorkMode.FuncMod[0].RfID[iIndex][4] )
                    {
                        ShowMessageBox(_T("设备已存在，请确认ID信息重新添加"));
                        return false;
                    }
                }

                tRK100WorkMode.FuncMod[0].RfID[i][0] = awRfID[0];
                tRK100WorkMode.FuncMod[0].RfID[i][1] = awRfID[1];
                tRK100WorkMode.FuncMod[0].RfID[i][2] = awRfID[2];
                tRK100WorkMode.FuncMod[0].RfID[i][3] = awRfID[3];
                tRK100WorkMode.FuncMod[0].RfID[i][4] = awRfID[4];
                bIsChanged = true;
            }
        }
    }

    if (bIsChanged)
    {
        CRkcComInterface->SetWorkModeConfig(tRK100WorkMode);
    }
    return true;
}

bool CRadioSetupLogic::OnSaveRadioButClicked(TNotifyUI& msg)
{
    return OnSaveRadioButClicked();
}

bool CRadioSetupLogic::OnRadioSwitchOptSel(TNotifyUI& msg)
{
    COptionUI* pOp = (COptionUI*)msg.pSender;
    if (pOp)
    {
        if (pOp->IsSelected())
        {
            m_pm->DoCase(_T("RadioON"));
        }
        else
        {
            m_pm->DoCase(_T("RadioOFF"));
        }
    }
    SetSaveBtnEnable();
    return true;
}

bool CRadioSetupLogic::OnOpenRadioOptSel(TNotifyUI& msg)
{
    //IRkcToolCommonOp::OptionSelect(false, m_pm, _T("CloseRadioOpt"), msg.pSender->GetParent());
    SetSaveBtnEnable();
    return true;
}

bool CRadioSetupLogic::OnCloseRadioOptSel(TNotifyUI& msg)
{
    //IRkcToolCommonOp::OptionSelect(false, m_pm, _T("OpenRadioOpt"), msg.pSender->GetParent());
    SetSaveBtnEnable();
    return true;
}

bool CRadioSetupLogic::OnEditTextChange(TNotifyUI& msg)
{
    SetSaveBtnEnable();
    return true;
}

void CRadioSetupLogic::RefreshRadioList()
{

}

bool CRadioSetupLogic::OnRkcRadioReflesh( WPARAM wparam, LPARAM lparam, bool& bHandle )
{
    bool bGetSuccess = (bool)wparam;
    if (bGetSuccess == false)
    {
        return false;
    }
    m_pPeripheralList = (CListUI*)IRkcToolCommonOp::FindControl( m_pm, _T("PeripheralList") );
    if (m_pPeripheralList)
    {
        TRK100WorkMode tRK100WorkMode;
        memset(&tRK100WorkMode, 0, sizeof(TRK100WorkMode));
        CRkcComInterface->GetWorkModeConfig(tRK100WorkMode);
        
        if (tRK100WorkMode.FuncMod[0].RfFlag != 0)
        {
            IRkcToolCommonOp::OptionSelect(true , m_pm, _T("RadioSwitchOpt") );
            m_pm->DoCase(_T("RadioON"));
        }
        else
        {
            IRkcToolCommonOp::OptionSelect(false , m_pm, _T("RadioSwitchOpt") );
            m_pm->DoCase(_T("RadioOFF"));
        }
        
        m_pPeripheralList->RemoveAll();
        for (u8 i = 0 ; i < MAX_RADIO_COUNT ; i++)
        {
            CListContainerElementUI *pListContainer = (CListContainerElementUI*)CONTROLFACTORY()->GetControl( _T("PeripheralListItem") );
            m_pm->DoCase(_T("NormalRadio"),pListContainer);
            if (pListContainer)
            {
                COptionUI* pOpOpen = (COptionUI*)IRkcToolCommonOp::FindControl(m_pm,_T("OpenRadioOpt"),pListContainer);
                COptionUI* pOpClose = (COptionUI*)IRkcToolCommonOp::FindControl(m_pm,_T("CloseRadioOpt"),pListContainer);
                if (pOpClose && pOpOpen)
                {
                    CString strGroup = _T("");
                    strGroup.Format(_T("itemgroup%d"),i);
                    pOpOpen->SetGroup(strGroup);
                    pOpClose->SetGroup(strGroup);
                }

                if (tRK100WorkMode.FuncMod[0].RfID[i][1] != 0 || 
                    tRK100WorkMode.FuncMod[0].RfID[i][2] != 0 ||
                    tRK100WorkMode.FuncMod[0].RfID[i][3] != 0 ||
                    tRK100WorkMode.FuncMod[0].RfID[i][4] != 0 )
                {
                    if (tRK100WorkMode.FuncMod[0].RfID[i][0] != 0)
                    {
                        IRkcToolCommonOp::OptionSelect(true, m_pm, _T("OpenRadioOpt"), pListContainer);
                        IRkcToolCommonOp::OptionSelect(false, m_pm, _T("CloseRadioOpt"), pListContainer);
                    }
                    else
                    {
                        IRkcToolCommonOp::OptionSelect(false, m_pm, _T("OpenRadioOpt"), pListContainer);
                        IRkcToolCommonOp::OptionSelect(true, m_pm, _T("CloseRadioOpt"), pListContainer);
                    }

                    CString strID = _T("");
                    strID.Format(_T("%02X%02X%02X%02X"),    tRK100WorkMode.FuncMod[0].RfID[i][1], 
                                                            tRK100WorkMode.FuncMod[0].RfID[i][2], 
                                                            tRK100WorkMode.FuncMod[0].RfID[i][3], 
                                                            tRK100WorkMode.FuncMod[0].RfID[i][4]    );
                    IRkcToolCommonOp::SetControlText(strID, m_pm, _T("RadioIpEdt"), pListContainer);
                }
                else
                {
                    break;
                }
                m_pPeripheralList->Add(pListContainer);
            }
        }

        int nListCount = m_pPeripheralList->GetCount();
        if (nListCount == 0)
        {
            CListContainerElementUI *pListContainer = (CListContainerElementUI*)CONTROLFACTORY()->GetControl( _T("PeripheralListItem") );
            COptionUI* pOpOpen = (COptionUI*)IRkcToolCommonOp::FindControl(m_pm,_T("OpenRadioOpt"),pListContainer);
            COptionUI* pOpClose = (COptionUI*)IRkcToolCommonOp::FindControl(m_pm,_T("CloseRadioOpt"),pListContainer);
            if (pOpClose && pOpOpen)
            {
                CString strGroup = _T("");
                strGroup.Format(_T("itemgroup%d"),m_pPeripheralList->GetCount());
                pOpOpen->SetGroup(strGroup);
                pOpClose->SetGroup(strGroup);
            }

            m_pm->DoCase(_T("NoRadio"),pListContainer);
            m_pPeripheralList->Add(pListContainer);
        }
        else if (m_pPeripheralList->GetCount() < MAX_RADIO_COUNT)
        {
            CListContainerElementUI *pListContainer = (CListContainerElementUI*)m_pPeripheralList->GetItemAt(nListCount-1);
            m_pm->DoCase(_T("LastRadio"),pListContainer);
        }

    }
    
    IRkcToolCommonOp::EnableControl(false, m_pm, _T("SaveRadioBut"));

    return true;
}

bool CRadioSetupLogic::OnRkcWorkModeChangeRsp( WPARAM wparam, LPARAM lparam, bool& bHandle )
{
    bool bSuccess = (bool)wparam;
    if (bSuccess)
    {
        ShowTipBox(_T("保存成功"));
        CRkcComInterface->GetWorkModeConfig();
    }
    else
    {
        ShowTipBox(_T("保存失败"));
    }
    return true;
}

//保存按钮是否可用
void CRadioSetupLogic::SetSaveBtnEnable()
{
    TRK100WorkMode tRK100WorkMode;
    memset(&tRK100WorkMode, 0, sizeof(TRK100WorkMode));
    CRkcComInterface->GetWorkModeConfig(tRK100WorkMode);

    //射频开关
    bool bisopen = IRkcToolCommonOp::IsOptionSelected( m_pm , _T("RadioSwitchOpt") );
    if (bisopen)
    {
        if (tRK100WorkMode.FuncMod[0].RfFlag == 0)
        {
            IRkcToolCommonOp::EnableControl(true, m_pm, _T("SaveRadioBut"));
            return;
        }
    }
    else
    {
        if (tRK100WorkMode.FuncMod[0].RfFlag == 1)
        {
            IRkcToolCommonOp::EnableControl(true, m_pm, _T("SaveRadioBut"));
            return;
        }
    }
    //射频ID
    m_pPeripheralList = (CListUI*)IRkcToolCommonOp::FindControl( m_pm, _T("PeripheralList") );
    if (m_pPeripheralList)
    {
        for (u8 i = 0 ; i < MAX_RADIO_COUNT ; i++)
        {
            u8 awRfID[5] = {0};
            if (i >= m_pPeripheralList->GetCount())
            {
                awRfID[0] = 0;
                awRfID[1] = 0;
                awRfID[2] = 0;
                awRfID[3] = 0;
                awRfID[4] = 0;
            }
            else
            {
                CListContainerElementUI *pListContainer = (CListContainerElementUI*)m_pPeripheralList->GetItemAt(i);
                CButtonUI* pButtonAdd = (CButtonUI*)IRkcToolCommonOp::FindControl(m_pm,_T("itemaddbut"),pListContainer);
                if (pButtonAdd && pButtonAdd->GetTag() == 1)
                {
                    awRfID[0] = 0;
                    awRfID[1] = 0;
                    awRfID[2] = 0;
                    awRfID[3] = 0;
                    awRfID[4] = 0;
                }
                else
                {
                    string strID = CT2A(IRkcToolCommonOp::GetControlText(m_pm, _T("RadioIpEdt"), pListContainer).c_str());
                    if (strID.size() != 8 || strcmp(strID.c_str(), "00000000") == 0)
                    {
                        IRkcToolCommonOp::EnableControl(true, m_pm, _T("SaveRadioBut"));
                        return;
                    }
                    transform(strID.begin(), strID.end(), strID.begin(), ::toupper);
                    for (u8 Index = 0 ; Index < strID.size() ; Index++)
                    {
                        if (strID[Index] < '0' || (strID[Index] > '9' && strID[Index] < 'A') || strID[Index] > 'F')
                        {
                            IRkcToolCommonOp::EnableControl(true, m_pm, _T("SaveRadioBut"));
                            return;
                        }
                    }
                    awRfID[0] = (IRkcToolCommonOp::IsOptionSelected(m_pm,_T("OpenRadioOpt"),pListContainer) ? 1 : 0);
                    awRfID[1] = map16hex[strID[0]] * 16 + map16hex[strID[1]];
                    awRfID[2] = map16hex[strID[2]] * 16 + map16hex[strID[3]];
                    awRfID[3] = map16hex[strID[4]] * 16 + map16hex[strID[5]];
                    awRfID[4] = map16hex[strID[6]] * 16 + map16hex[strID[7]];
                }
            }

            if (tRK100WorkMode.FuncMod[0].RfID[i][0] == awRfID[0] &&
                tRK100WorkMode.FuncMod[0].RfID[i][1] == awRfID[1] && 
                tRK100WorkMode.FuncMod[0].RfID[i][2] == awRfID[2] && 
                tRK100WorkMode.FuncMod[0].RfID[i][3] == awRfID[3] && 
                tRK100WorkMode.FuncMod[0].RfID[i][4] == awRfID[4])
            {

            }
            else
            {
                IRkcToolCommonOp::EnableControl(true, m_pm, _T("SaveRadioBut"));
                return;
            }
        }
    }
    IRkcToolCommonOp::EnableControl(false, m_pm, _T("SaveRadioBut"));
    return;
}