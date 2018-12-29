#include "stdafx.h"
#include "toolframelogic.h"
#include "modifypasswordlogic.h"
#include "tipboxlogic.h"
#include "messageboxlogic.h"

#define HELPWIND_LEFT_POS   (435 + 221)   //帮助窗口到toolframe左侧位置
#define HELPWIND_TOP_POS    110           //帮助窗口到toolframe顶部位置
 
template<> CModifyPasswordLogic* Singleton<CModifyPasswordLogic>::ms_pSingleton  = NULL;

APP_BEGIN_MSG_MAP(CModifyPasswordLogic, CNotifyUIImpl)
    MSG_SETFOCUS(_T("InputCurPwd"), OnInputCurPassword)
    MSG_SETFOCUS(_T("InputNewPwd"), OnInputNewPassword)
    MSG_SETFOCUS(_T("InputCfmPwd"), OnInputCfmPassword)

    MSG_TEXTCHANGED(_T("InputNewPwd"), OnInputNewPwdChange)

    MSG_CLICK(_T("CurPwdVisSwitchBtn"), OnCurPwdVisibleClicked)
    MSG_CLICK(_T("NewPwdVisSwitchBtn"), OnNewPwdVisibleClicked)
    MSG_CLICK(_T("CfmPwdVisSwitchBtn"), OnCfmPwdVisibleClicked)
    MSG_CLICK(_T("TextHelp"), OnShowPasswordHelp)
    MSG_CLICK(_T("SaveBtn"), OnSaveNewPwdClicked)

    USER_MSG(UI_RKC_MODIFY_PASSWORD , OnRkcPasswordModified)
    USER_MSG(UI_RKC_DISCONNECTED , OnRkcDisconnected)
APP_END_MSG_MAP()

CModifyPasswordLogic::CModifyPasswordLogic()
{
    m_bCurPwdIsJudged   = false;
    m_bCurPwdIsRight    = false;
    m_bNewPwdIsJudged   = false;
    m_bNewPwdIsStandard = false;
    m_bBack2HomePage    = true;
    m_bPwdIsSameAsBefore = false;
}

CModifyPasswordLogic::~CModifyPasswordLogic()
{
}

bool CModifyPasswordLogic::OnSaveNewPwdClicked()
{
    // 设置焦点，检验当前密码和新密码
    CEditUI *pControl = (CEditUI*)IRkcToolCommonOp::FindControl( m_pm, _T("InputCfmPwd") );
    if (pControl)
    {
        m_pm->SetFocus(pControl);
    }

    if (!m_bNewPwdIsJudged)
    {
        // 判断新密码的密码规范
        if (!OnJudgeNewPassword())
        {
            m_pm->DoCase(_T("caseNewPwdIsNonstandard"));
            return false;
        }
    }

    if (!m_bCurPwdIsRight || !m_bNewPwdIsStandard )
    {
        return false;
    }

    // 设置焦点到保存按键
    CButtonUI *pBtnCtl = (CButtonUI*)IRkcToolCommonOp::FindControl( m_pm, _T("SaveBtn") );
    if (pBtnCtl)
    {
        m_pm->SetFocus(pBtnCtl);
    }

    if (!OnJudgeCfmPassword())
    {
        m_pm->DoCase(_T("caseConfirmNewPwdFail"));
        return false;
    }

    m_pm->DoCase(_T("caseConfirmNewPwdPass"));

    // 设置新密码
    CString strPassWord = (IRkcToolCommonOp::GetControlText( m_pm ,_T("InputCfmPwd"))).c_str();
    if (!CRkcComInterface->SetLoginInfo(CT2A(strPassWord)))
    {
        CRkcComInterface->SendModifyPasswordReq();
    }

    return true;
}

bool CModifyPasswordLogic::IsConfigChange()
{
    String strCurPwd = (IRkcToolCommonOp::GetControlText( m_pm ,_T("InputCurPwd"))).c_str();
    String strNewPwd = (IRkcToolCommonOp::GetControlText( m_pm ,_T("InputNewPwd"))).c_str();
    String strCfmPwd = (IRkcToolCommonOp::GetControlText( m_pm ,_T("InputCfmPwd"))).c_str();

    if (strCurPwd == _T("") && strNewPwd == _T("") && strCfmPwd == _T(""))
    {
        OnResetAllInput();
        return true;
    }
    else
    {
        int nBoxRe = ShowMessageBox(_T("是否保存当前修改内容"),2);
        if (nBoxRe == IDOK)
        {
            m_bBack2HomePage = false;
            if (OnSaveNewPwdClicked() == false)
            {
                m_bBack2HomePage = true;
                return false;
            }
            return true;
        }
        else if (nBoxRe == IDNO)
        {
            return false;
        }
        else
        {
            OnResetAllInput();
            return true;
        }
    }
}

u8 CModifyPasswordLogic::ExitCheckChange()
{
    String strCurPwd = (IRkcToolCommonOp::GetControlText( m_pm ,_T("InputCurPwd"))).c_str();
    String strNewPwd = (IRkcToolCommonOp::GetControlText( m_pm ,_T("InputNewPwd"))).c_str();
    String strCfmPwd = (IRkcToolCommonOp::GetControlText( m_pm ,_T("InputCfmPwd"))).c_str();

    if (strCurPwd == _T("") && strNewPwd == _T("") && strCfmPwd == _T(""))
    {
        OnResetAllInput();
        return 2;
    }
    else
    {
        int nBoxRe = ShowMessageBox(_T("是否保存当前修改内容"),2);
        if (nBoxRe == IDOK)
        {
            return OnSaveNewPwdClicked() ? 3 : 1;
        }
        else if (nBoxRe == IDNO)
        {
            return 1;
        }
        else
        {
            OnResetAllInput();
            return 2;
        }
    }
}

bool CModifyPasswordLogic::OnInputCurPassword(TNotifyUI& msg)
{
    m_pm->DoCase(_T("caseInputCurPwd"));
    m_bCurPwdIsJudged = false;
    m_bCurPwdIsRight = false;
    m_bNewPwdIsJudged = false;
    m_bNewPwdIsStandard = false;

    return true;
}

bool CModifyPasswordLogic::OnInputNewPassword(TNotifyUI& msg)
{
    m_pm->DoCase(_T("caseInputNewPwd"));
    m_bCurPwdIsJudged = false;
    m_bCurPwdIsRight = false;
    m_bNewPwdIsJudged = false;
    m_bNewPwdIsStandard = false;

    //判断当前密码的正确性，密码为空
    String strGetInputCurPwd = IRkcToolCommonOp::GetControlText( m_pm ,_T("InputCurPwd"));
    if (strGetInputCurPwd == _T(""))
    {
        m_pm->DoCase(_T("caseCurPwdIsEmpty"));
        OnInputNewPwdChange(msg);
        return false;
    }
    else
    {
        //判断当前密码的正确性，密码不为空
        if (!OnJudgeCurPassword())
        {
            m_pm->DoCase(_T("caseIsPwdFalse"));
            OnInputNewPwdChange(msg);
            return false;
        }

        //当前密码输入正确
        m_pm->DoCase(_T("caseIsPwdTrue"));
        OnInputNewPwdChange(msg);
        return true;
    }
}

bool CModifyPasswordLogic::OnInputCfmPassword(TNotifyUI& msg)
{
    if (!m_bCurPwdIsJudged)
    {
        //判断当前密码的正确性，密码为空
        String strGetInputCurPwd = IRkcToolCommonOp::GetControlText( m_pm ,_T("InputCurPwd"));
        if (strGetInputCurPwd == _T(""))
        {
            m_pm->DoCase(_T("caseCurPwdIsEmpty"));
        }
        else
        {
            //判断当前密码的正确性，密码不为空
            if (!OnJudgeCurPassword())
            {
                m_pm->DoCase(_T("caseIsPwdFalse"));
            }
            else
            {
                m_pm->DoCase(_T("caseIsPwdTrue"));
            }
        }
    }

    if (!m_bNewPwdIsJudged)
    {
        OnInputNewPwdChange(msg);
    }

    m_pm->DoCase(_T("caseInputCfmNewPwd"));

    // 判断新密码的密码规范
    if (!OnJudgeNewPassword())
    {
        if (m_bPwdIsSameAsBefore)
        {
            m_pm->DoCase(_T("caseNewPwdIsSameAsCurPwd"));
        }
        else
        {
            m_pm->DoCase(_T("caseNewPwdIsNonstandard"));
        }
    }

    if (!m_bCurPwdIsRight || !m_bNewPwdIsStandard)
    {
        m_pm->DoCase(_T("caseSaveBtnDisable"));
    }

    return true;    
}

bool CModifyPasswordLogic::OnInputNewPwdChange(TNotifyUI& msg)
{
    bool bIsContainNum = false;
    bool bIsContainAlp = false;
    bool bIsContainSym = false;
    bool bIsForbiddenChar = false;           // 非"."和"_"的特殊字符
    u32  dwSymbolCnt = 0;                    // 特殊字符计数

    CString strGetInputNewPwd = (IRkcToolCommonOp::GetControlText( m_pm ,_T("InputNewPwd"))).c_str();
    if (strGetInputNewPwd != _T(""))
    {
        s32 nStrLength = strGetInputNewPwd.GetLength();
        for (s32 nIndex = 0; nIndex < nStrLength; nIndex++)
        {
            s32 nUnit = strGetInputNewPwd.GetAt(nIndex);
            if (nUnit > 127)
            {
                m_pm->DoCase(_T("caseNewPwdIsNonstandard"));
                return false;
            }

            if (isalpha(nUnit))
            {
                bIsContainAlp = true;
            }
            else if (!isalnum(nUnit))
            {
                bIsContainSym = true;

                if (nUnit == '.' || nUnit == '_')
                {
                    dwSymbolCnt++;
                }
                else
                {
                    bIsForbiddenChar = true;
                }
            }
            else
            {
                bIsContainNum = true;
            }
        }

        // 新密码规范性判断
        //m_bNewPwdIsJudged = true;
        m_bNewPwdIsStandard = false;

        if (nStrLength < 8)
        {
            m_pm->DoCase(_T("caseInputNewPwd"));
            return false;
        }

        if (!bIsContainSym)
        {
            // 口令中仅包含数字、字母时，密码强度弱
            if (bIsContainAlp && bIsContainNum)
            {
                m_pm->DoCase(_T("caseNewPwdIsWeak"));
                m_bNewPwdIsStandard = true;
                return true;
            }

            // 密码不符合规范
            m_pm->DoCase(_T("caseNewPwdIsNonstandard"));
            return false;
        }
        else if (!bIsForbiddenChar)
        {
            if (bIsContainAlp || bIsContainNum)
            {
                if (dwSymbolCnt == 1)
                {
                    // 口令中包含数字、字母和任一特殊字符时，密码强度中
                    m_pm->DoCase(_T("caseNewPwdIsMedium"));
                    m_bNewPwdIsStandard = true;
                    return true;
                }

                if (dwSymbolCnt > 1)
                {
                    // 口令中包含数字、字母和多个特殊字符时，密码强度强
                    m_pm->DoCase(_T("caseNewPwdIsStrong"));
                    m_bNewPwdIsStandard = true;
                    return true;
                }

                // 密码不符合规范
                m_pm->DoCase(_T("caseNewPwdIsNonstandard"));
                return false;
            }

            // 密码不符合规范
            m_pm->DoCase(_T("caseNewPwdIsNonstandard"));
            return false;
        }
        else
        {
            // 密码不符合规范
            m_pm->DoCase(_T("caseNewPwdIsNonstandard"));
            return false;
        }
    }

    //m_pm->DoCase(_T("caseInputNewPwd"));
    return true;
}

bool CModifyPasswordLogic::OnJudgeCurPassword()
{
    TRK100LoginInfo tLoginInfo;
    CRkcComInterface->GetLoginInfo(tLoginInfo);
    m_bCurPwdIsJudged = true;

    CString strGetInputCurPwd = (IRkcToolCommonOp::GetControlText( m_pm ,_T("InputCurPwd"))).c_str();
    if (!strcmp(tLoginInfo.szPwd, (CT2A)strGetInputCurPwd))
    {
        m_bCurPwdIsRight = true;
        return true;
    }

    return false;
}

bool CModifyPasswordLogic::OnJudgeNewPassword()
{
    m_bNewPwdIsJudged = true;
    m_bPwdIsSameAsBefore = false;

    CString strGetInputCurPwd = (IRkcToolCommonOp::GetControlText( m_pm ,_T("InputCurPwd"))).c_str();
    CString strGetInputNewPwd = (IRkcToolCommonOp::GetControlText( m_pm ,_T("InputNewPwd"))).c_str();
    if (strGetInputNewPwd.GetLength() < 8)
    {
        m_bNewPwdIsStandard = false;
        return false;
    }

    if (m_bCurPwdIsRight)
    {
        if (!strcmp((CT2A)strGetInputCurPwd, (CT2A)strGetInputNewPwd))
        {
            m_bNewPwdIsStandard = false;
            m_bPwdIsSameAsBefore = true;
            return false;
        }
    }

    return true;
}

bool CModifyPasswordLogic::OnJudgeCfmPassword()
{
    CString strGetInputNewPwd = (IRkcToolCommonOp::GetControlText( m_pm ,_T("InputNewPwd"))).c_str();
    CString strGetConfirmNewPwd = (IRkcToolCommonOp::GetControlText( m_pm ,_T("InputCfmPwd"))).c_str();

    if (strGetInputNewPwd != strGetConfirmNewPwd)
    {
        return false;
    }

    return true;
}

bool CModifyPasswordLogic::OnCurPwdVisibleClicked(TNotifyUI& msg)
{
    CEditUI *pControl = (CEditUI*)IRkcToolCommonOp::FindControl( m_pm, _T("InputCurPwd") );
    if (pControl)
    {
        if (pControl->IsPasswordMode())
        {
            m_pm->DoCase(_T("caseCurPwdIsVisible"));
            m_pm->SetFocus(pControl);
            return true;
        }

        m_pm->DoCase(_T("caseCurPwdIsInvisible"));
        m_pm->SetFocus(pControl);
    }

    return true;
}

bool CModifyPasswordLogic::OnNewPwdVisibleClicked(TNotifyUI& msg)
{
    CEditUI *pControl = (CEditUI*)IRkcToolCommonOp::FindControl( m_pm, _T("InputNewPwd") );
    if (pControl)
    {
        if (pControl->IsPasswordMode())
        {
            m_pm->DoCase(_T("caseNewPwdIsVisible"));
            m_pm->SetFocus(pControl);
            return true;
        }

        m_pm->DoCase(_T("caseNewPwdIsInvisible"));
        m_pm->SetFocus(pControl);
    }

    return true;
}

bool CModifyPasswordLogic::OnCfmPwdVisibleClicked(TNotifyUI& msg)
{
    CEditUI *pControl = (CEditUI*)IRkcToolCommonOp::FindControl( m_pm, _T("InputCfmPwd") );
    if (pControl)
    {
        if (pControl->IsPasswordMode())
        {
            m_pm->DoCase(_T("caseCfmPwdIsVisible"));
            m_pm->SetFocus(pControl);
            return true;
        }

        m_pm->DoCase(_T("caseCfmPwdIsInvisible"));
        m_pm->SetFocus(pControl);
    }

    return true;
}

bool CModifyPasswordLogic::OnShowPasswordHelp(TNotifyUI& msg)
{
    // 帮助窗口位置更新，保持与toolframe的相对位置
    Window* pAppWindow = WINDOW_MGR_PTR->GetWindow(g_stcStrPwdHelpDlg.c_str());
    if ( pAppWindow != NULL )
    {
        OnUpdatePwdHelpWindPos();
    }

    WINDOW_MGR_PTR->ShowWindow(g_stcStrPwdHelpDlg.c_str(), true);

    return true;
}

bool CModifyPasswordLogic::OnSaveNewPwdClicked(TNotifyUI& msg)
{
    return OnSaveNewPwdClicked();
}

bool CModifyPasswordLogic::OnRkcPasswordModified( WPARAM wparam, LPARAM lparam, bool& bHandle )
{
    bool bIsModified = (bool)wparam;
    EMRK100OptRtn emErr = (EMRK100OptRtn)lparam;
    if (bIsModified == false)
    {
        /*switch (emErr)
        {
        case RK100_OPT_ERR_USER:
            ShowTip(_T("用户名错误"));
            break;
        case RK100_OPT_ERR_PASSWORD:
            ShowTip(_T("密码错误"));
            break;
        default:
            ShowTip(_T("登录失败"));
            break;
        }*/
    }
    else
    {
        CToolFrameLogic::GetSingletonPtr()->SetFirstLogin(false);
        ShowTipBox(_T("密码修改成功"));

        // 回到默认主页：网络设置
        if (m_bBack2HomePage)
        {
            CTabLayoutUI *pControl = (CTabLayoutUI*)IRkcToolCommonOp::FindControl( m_pm, _T("ToolFrameSlideTab") );
            if (pControl)
            {
                pControl->SelectItem(emTabID_NetworkSetup);
                IRkcToolCommonOp::OptionSelectNoMsg(true,m_pm,_T("NetworkSetupOpt"));
            }
        }
        m_bBack2HomePage = true;
    }
    return true;
}

bool CModifyPasswordLogic::OnRkcDisconnected( WPARAM wparam, LPARAM lparam, bool& bHandle )
{
    OnResetAllInput();
    return true;
}

void CModifyPasswordLogic::OnResetAllInput()
{
    m_pm->DoCase(_T("casePageInit"));

    m_bCurPwdIsJudged = false;
    m_bCurPwdIsRight  = false;
    m_bNewPwdIsJudged = false;
    m_bNewPwdIsStandard = false;
    m_bBack2HomePage  = true;

    IRkcToolCommonOp::SetControlText(_T(""), m_pm, _T("InputCurPwd"));
    IRkcToolCommonOp::SetControlText(_T(""), m_pm, _T("InputNewPwd"));
    IRkcToolCommonOp::SetControlText(_T(""), m_pm, _T("InputCfmPwd"));

    return;
}

void CModifyPasswordLogic::OnGreatePwdHelpWind()
{
    WINDOW_MGR_PTR->ShowWindow(g_stcStrPwdHelpDlg.c_str(), false);

    Window* pWnd = WINDOW_MGR_PTR->GetWindow(g_stcStrPwdHelpDlg.c_str());
    if ( pWnd != NULL )
    {
        pWnd->SetAutoHide( true );
    }

    RECT rcParent;
    HWND hparent = m_pm->GetPaintWindow();
    GetWindowRect(hparent,&rcParent);

    m_nHelpWindLeft = rcParent.left + HELPWIND_LEFT_POS;
    m_nHelpWindTop  = rcParent.top + HELPWIND_TOP_POS;

    HWND hAppWind = FindWindow(NULL, g_stcStrPwdHelpDlg.c_str());
    SetWindowPos( hAppWind, NULL, m_nHelpWindLeft, m_nHelpWindTop, 0, 0, SWP_NOSIZE |SWP_NOACTIVATE);
}

void CModifyPasswordLogic::OnUpdatePwdHelpWindPos()
{
    RECT rcParent;
    HWND hparent = m_pm->GetPaintWindow();
    GetWindowRect(hparent,&rcParent);

    s32 nLeft = rcParent.left + HELPWIND_LEFT_POS;
    s32 nTop  = rcParent.top + HELPWIND_TOP_POS;

    // 帮助窗口位置更新，保持与toolframe的相对位置
    if (nLeft != m_nHelpWindLeft || nTop != m_nHelpWindTop)
    {
        HWND hAppWind = FindWindow(NULL, g_stcStrPwdHelpDlg.c_str());
        if (hAppWind)
        {
            m_nHelpWindLeft = nLeft;
            m_nHelpWindTop  = nTop;
            SetWindowPos( hAppWind, NULL, m_nHelpWindLeft, m_nHelpWindTop, 0, 0, SWP_NOSIZE |SWP_NOACTIVATE);
        }
    }
}