#include "stdafx.h"
#include "loginlogic.h"
#include "searchequipmentlogic.h"

#define TIMER_LENGTH  4000
#define TIMER_SHOWTIP 200

APP_BEGIN_MSG_MAP(CLoginLogic, CNotifyUIImpl)
    MSG_CREATEWINDOW(_T("login"), OnCreate)
    MSG_INIWINDOW(_T("login"), OnInit)
    MSG_WINDOWDESTORY(_T("login"), OnDestroy)

    MSG_CLICK(_T("closebtn"), OnCloseBtnClicked)
    MSG_CLICK(_T("LoginBtn"), OnLoginBtnClicked)

    MSG_SELECTCHANGE(_T("CheckAutoLogin"), OnCheckAutoLoginSel)
    MSG_SELECTCHANGE(_T("CheckRemPassWord"), OnCheckRemPassWordSel)

    MSG_TIMER(_T("LoginTipLeb"), OnShowTipTimer)

    USER_MSG(UI_RKC_CONNECTED , OnRkcConnected)
    USER_MSG(UI_RKC_DISCONNECTED , OnRkcDisconnected)
APP_END_MSG_MAP()

CLoginLogic::CLoginLogic()
{
}

CLoginLogic::~CLoginLogic()
{
}

bool CLoginLogic::OnCreate( TNotifyUI& msg )
{
    s32 nTop = 0;
    RECT rcParent;
    HWND hparent = GetParent(m_pm->GetPaintWindow());
    GetWindowRect(hparent,&rcParent);
    SetWindowPos( m_pm->GetPaintWindow(), HWND_TOPMOST, rcParent.left, rcParent.top, 0, 0, SWP_NOSIZE |SWP_NOACTIVATE );
    return false;
}


bool CLoginLogic::OnInit( TNotifyUI& msg )
{
    REG_RCKTOOL_MSG_WND_OB(m_pm->GetPaintWindow());
    //选中的设备
    TDevItem tDevItem = CSearchEquipmentLogic::GetSingletonPtr()->GetDevItem();
    in_addr tAddrIP;
    tAddrIP.S_un.S_addr = htonl(tDevItem.tDevInfo.tAddr.dwIpaddr);
    CString strLoginIP = (CA2T)inet_ntoa(tAddrIP);
    //配置文件里保存上一次登录的设备
    CString strIniPath = CSearchEquipmentLogic::GetSingletonPtr()->GetIniFilePath();
    TCHAR tchLoginIP[MAX_NAME_LEN]={0};
    GetPrivateProfileString(_T("LoginInfo"),_T("LoginIP"),_T(""), tchLoginIP, MAX_NAME_LEN-1, strIniPath);
    if (wcscmp( tchLoginIP , strLoginIP ) == 0)
    {
        TCHAR tchUserName[MAX_NAME_LEN]={0};
        TCHAR tchPassWord[MAX_NAME_LEN]={0};
        GetPrivateProfileString(_T("LoginInfo"),_T("UserName"),_T(""), tchUserName, MAX_NAME_LEN-1, strIniPath);
        GetPrivateProfileString(_T("LoginInfo"), _T("PassWord"),_T(""), tchPassWord, MAX_NAME_LEN-1, strIniPath);

        IRkcToolCommonOp::SetControlText(tchUserName, m_pm, _T("edtUserName"));
        int wRemPW = GetPrivateProfileInt(_T("LoginInfo"),_T("RemberPW"), 0,strIniPath);
        int wAutoL = GetPrivateProfileInt(_T("LoginInfo"),_T("AutoLogin"), 0,strIniPath);
        COptionUI *pCheckRemPassWord = (COptionUI*)IRkcToolCommonOp::FindControl( m_pm, _T("CheckRemPassWord") );
        COptionUI *pCheckAutoLogin = (COptionUI*)IRkcToolCommonOp::FindControl( m_pm, _T("CheckAutoLogin") );
        if (wRemPW == 0)
        {
            IRkcToolCommonOp::SetControlText(_T(""), m_pm, _T("edtPassWord"));
            if (pCheckRemPassWord)
            {
                pCheckRemPassWord->Selected(false);
            }
        }
        else
        {
            IRkcToolCommonOp::SetControlText(tchPassWord, m_pm, _T("edtPassWord"));
            if (pCheckRemPassWord)
            {
                pCheckRemPassWord->Selected(true);
            }
        }
        pCheckAutoLogin->Selected(wAutoL != 0);
        //自动登录
        if (wAutoL != 0) 
        {
            m_pm->DoCase(_T("caseIsLogining"));
            CRkcComInterface->SocketConnect(CSearchEquipmentLogic::GetSingletonPtr()->GetDevItem(), CT2A(tchUserName), CT2A(tchPassWord));
        }
    }
    return true;
}

bool CLoginLogic::OnDestroy( TNotifyUI& msg )
{
    UNREG_RCKTOOL_MSG_WND_OB(m_pm->GetPaintWindow());
    return true;
}

bool CLoginLogic::OnCloseBtnClicked(TNotifyUI& msg)
{
    WINDOW_MGR_PTR->ShowWindow(g_stcStrBackGroundDlg.c_str(), false);
    WINDOW_MGR_PTR->CloseWindow(g_stcStrLoginDlg.c_str());  
    return false;
}

bool CLoginLogic::OnLoginBtnClicked(TNotifyUI& msg)
{
    CString strUserName = (IRkcToolCommonOp::GetControlText( m_pm ,_T("edtUserName"))).c_str();
    CString strPassWord = (IRkcToolCommonOp::GetControlText( m_pm ,_T("edtPassWord"))).c_str();
    if (strUserName.IsEmpty())
    {
        ShowTip(_T("请输入账号、密码"));
        return false;
    }
    if(strPassWord.IsEmpty())
    {
        ShowTip(_T("请输入账号、密码"));
        return false;
    }
    m_pm->DoCase(_T("caseIsLogining"));
    CRkcComInterface->SocketConnect(CSearchEquipmentLogic::GetSingletonPtr()->GetDevItem(), CT2A(strUserName), CT2A(strPassWord));
    return true;
}

bool CLoginLogic::OnShowTipTimer(TNotifyUI& msg)
{
    m_pm->DoCase(_T("caseCloseTip"));
    m_pm->KillTimer(msg.pSender, TIMER_SHOWTIP);
    return true;
}

bool CLoginLogic::OnCheckAutoLoginSel(TNotifyUI& msg)
{
    COptionUI *pCheckRemPassWord = (COptionUI*)IRkcToolCommonOp::FindControl( m_pm, _T("CheckRemPassWord") );
    COptionUI *pCheckAutoLogin = (COptionUI*)IRkcToolCommonOp::FindControl( m_pm, _T("CheckAutoLogin") );
    if (pCheckRemPassWord && pCheckAutoLogin)
    {
        if (pCheckAutoLogin->IsSelected())
        {
            pCheckRemPassWord->Selected(true);
        }
    }
    return true;
}

bool CLoginLogic::OnCheckRemPassWordSel(TNotifyUI& msg)
{
    COptionUI *pCheckRemPassWord = (COptionUI*)IRkcToolCommonOp::FindControl( m_pm, _T("CheckRemPassWord") );
    COptionUI *pCheckAutoLogin = (COptionUI*)IRkcToolCommonOp::FindControl( m_pm, _T("CheckAutoLogin") );
    if (pCheckRemPassWord && pCheckAutoLogin)
    {
        if (pCheckRemPassWord->IsSelected() == false)
        {
            pCheckAutoLogin->Selected(false);
        }
    }
    return true;
}

bool CLoginLogic::OnRkcConnected( WPARAM wparam, LPARAM lparam, bool& bHandle )
{
    m_pm->DoCase(_T("caseNormal"));

    bool bIsLogin = (bool)wparam;
    EMRK100OptRtn emErr = (EMRK100OptRtn)lparam;
    if (bIsLogin == false && emErr != RK100_OPT_ERR_FIRST_LOGIN)
    {
        switch (emErr)
        {
        case RK100_OPT_ERR_USER:
//             ShowTip(_T("账号/密码错误，请重新输入"));
//             break;
        case RK100_OPT_ERR_PASSWORD:
            {
                TRK100MsgHead tRK100MsgHead;
                memset(&tRK100MsgHead,0,sizeof(tRK100MsgHead));
                CRkcComInterface->GetLoginBackInfo(tRK100MsgHead);
                CString strtmp = _T("");
                if ((5 - tRK100MsgHead.wReserved1) == 0)
                {
                    strtmp.Format(_T("账号/密码输入错误，账号已锁定，请稍后再试"), 5 - tRK100MsgHead.wReserved1);
                }
                else
                {
                    strtmp.Format(_T("账号/密码输入错误，还有%d次输入机会，否则将会锁定账号"), 5 - tRK100MsgHead.wReserved1);
                }
                ShowTip(strtmp); 
            }
            //ShowTip(_T("密码错误"));
            break;
        case RK100_OPT_ERR_LOCKED:
            ShowTip(_T("账号已锁定，请稍后再试"));
            break;
        case RK100_OPT_ERR_UNKNOWN:
            ShowTip(_T("未知错误，请稍后再试"));
            break;
        default:
            ShowTip(_T("连接到主机失败"));
            break;
        }
    }
    else
    {
        CString strIniPath = CSearchEquipmentLogic::GetSingletonPtr()->GetIniFilePath();
        TDevItem tLoginDevitem;
        CRkcComInterface->GetLoginDevItem(tLoginDevitem);
        in_addr tAddrIP;
        tAddrIP.S_un.S_addr = htonl(tLoginDevitem.tDevInfo.tAddr.dwIpaddr);
        CString strLoginIP = (CA2T)inet_ntoa(tAddrIP);
        CString strUserName = (IRkcToolCommonOp::GetControlText( m_pm ,_T("edtUserName"))).c_str();
        CString strPassWord = (IRkcToolCommonOp::GetControlText( m_pm ,_T("edtPassWord"))).c_str();
        WritePrivateProfileString(_T("LoginInfo"),_T("LoginIP"),strLoginIP,strIniPath);
        WritePrivateProfileString(_T("LoginInfo"),_T("UserName"),strUserName,strIniPath);
        COptionUI *pCheckRemPassWord = (COptionUI*)IRkcToolCommonOp::FindControl( m_pm, _T("CheckRemPassWord") );
        COptionUI *pCheckAutoLogin = (COptionUI*)IRkcToolCommonOp::FindControl( m_pm, _T("CheckAutoLogin") );
        if (pCheckRemPassWord)
        {
            if (pCheckRemPassWord->IsSelected())
            {
                WritePrivateProfileString(_T("LoginInfo"),_T("PassWord"),strPassWord,strIniPath);
                WritePrivateProfileString(_T("LoginInfo"),_T("RemberPW"),_T("1"),strIniPath);
            }
            else
            {
                WritePrivateProfileString(_T("LoginInfo"),_T("PassWord"),_T(""),strIniPath);
                WritePrivateProfileString(_T("LoginInfo"),_T("RemberPW"),_T("0"),strIniPath);
            }
        }
        if (pCheckAutoLogin)
        {
            if (pCheckAutoLogin->IsSelected())
            {
                WritePrivateProfileString(_T("LoginInfo"),_T("AutoLogin"),_T("1"),strIniPath);
            }
            else
            {
                WritePrivateProfileString(_T("LoginInfo"),_T("AutoLogin"),_T("0"),strIniPath);
            }
        }
    }
    return true;
}

bool CLoginLogic::OnRkcDisconnected( WPARAM wparam, LPARAM lparam, bool& bHandle )
{
    m_pm->DoCase(_T("caseNormal"));
    return true;
}

void CLoginLogic::ShowTip(CString strTip)
{
    m_pm->DoCase(_T("caseShowTip"));
    CLabelUI *pControl = (CLabelUI*)IRkcToolCommonOp::FindControl( m_pm, _T("LoginTipLeb") );
    if (pControl)
    {
        pControl->SetText(strTip);
        m_pm->SetTimer(pControl, TIMER_SHOWTIP, TIMER_LENGTH);
    }
}

