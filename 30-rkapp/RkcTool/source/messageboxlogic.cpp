#include "stdafx.h"
#include "messageboxlogic.h"
#include "searchequipmentlogic.h"
#include "netchangelogic.h"

APP_BEGIN_MSG_MAP(CMessageBoxLogic, CNotifyUIImpl)
    MSG_CREATEWINDOW(_T("MessageBoxLayout"), OnCreate)
    MSG_INIWINDOW(_T("MessageBoxLayout"), OnInit)
    MSG_WINDOWDESTORY(_T("MessageBoxLayout"), OnDestroy)

    MSG_CLICK(_T("closebtn"), OnCloseBtnClicked)
    MSG_CLICK(_T("MsgBoxclosebtn"), OnCloseBtnClicked)

    MSG_CLICK(_T("OkBtn"), OnOKBtnClicked)
    MSG_CLICK(_T("CancelBtn"), OnCancelBtnClicked)
    MSG_CLICK(_T("MsgBoxOkBtn"), OnOKBtnClicked)
    MSG_CLICK(_T("MsgBoxCancelBtn"), OnCancelBtnClicked)

    MSG_CLICK(_T("NetChangeBtn"), OnNetChangeBtnClicked)
    //MSG_CLICK(_T("TopSpaceLayout"), OnSpaceLayoutClicked)
    //MSG_CLICK(_T("BottomSpaceLayout"), OnSpaceLayoutClicked)
    //MSG_CLICK(_T("LeftSpaceLayout"), OnSpaceLayoutClicked)
    //MSG_CLICK(_T("RigntSpaceLayout"), OnSpaceLayoutClicked)
    MSG_CLICK(_T("BackUpsLayout"), OnSpaceLayoutClicked)

    USER_MSG(UI_RKC_RESTONE , OnRkcRestone)
    USER_MSG(UI_RKC_DISCONNECTED , OnRkcDisconnected)
APP_END_MSG_MAP()

static u8       m_byBoxType = 0;//0 消息弹窗 1 导入升级弹窗

static CString  m_strText = _T("");
static CString  m_strLeftBtnText = _T("");
static u8       m_byType = 0;

static CString  m_strBackUpTime = _T("");
static CString  m_strBackUpModel = _T("");
static CString  m_strBackUpIniPath = _T("");

static CString  m_strUpdateModel = _T("");
static CString  m_strUpdateVer = _T("");
static CString  m_strUpdateVerNew = _T("");

u8 showMessageBox(LPCTSTR lpstrText, u8 byType, LPCTSTR lpstrLeftText)
{
    if (WINDOW_MGR_PTR->IsWindowMinsize(g_stcStrMainFrameDlg.c_str()))
    {
        return 0;
    }
    m_byBoxType = 0;

    m_strText = lpstrText;
    m_strLeftBtnText = lpstrLeftText;
    m_byType = byType;
    if (m_byType == 2)
    {
        CSearchEquipmentLogic::GetSingletonPtr()->OnShowBGWindow();
        return WINDOW_MGR_PTR->ShowModalGetRe(g_stcStrMessageBoxDlg.c_str());
    }
    else
    {
        CSearchEquipmentLogic::GetSingletonPtr()->OnShowBGWindow();
        return WINDOW_MGR_PTR->ShowWindowCenter(g_stcStrMessageBoxDlg.c_str());
    }
}

bool showBackUpBox(LPCTSTR lpstrTime, LPCTSTR lpstrModel, LPCTSTR lpstrIniPath)
{
    m_byBoxType = 1;

    m_strBackUpTime = lpstrTime;
    m_strBackUpModel = lpstrModel;
    m_strBackUpIniPath = lpstrIniPath;
    CSearchEquipmentLogic::GetSingletonPtr()->OnShowBGWindow();
    return WINDOW_MGR_PTR->ShowModal(g_stcStrMessageBoxDlg.c_str());
}

bool showUpDateBox(LPCTSTR lpstrModel, LPCTSTR lpstrVer, LPCTSTR lpstrVerN)
{
    m_byBoxType = 2;

    m_strUpdateModel = lpstrModel;
    m_strUpdateVer = lpstrVer;
    m_strUpdateVerNew = lpstrVerN;
    CSearchEquipmentLogic::GetSingletonPtr()->OnShowBGWindow();
    return WINDOW_MGR_PTR->ShowModal(g_stcStrMessageBoxDlg.c_str());
}

CMessageBoxLogic::CMessageBoxLogic()
{
    m_emOperation = Emue_None;
}

CMessageBoxLogic::~CMessageBoxLogic()
{
}

bool CMessageBoxLogic::OnCreate( TNotifyUI& msg )
{
    s32 nTop = 0;
    RECT rcParent;
    HWND hparent = GetParent(m_pm->GetPaintWindow());
    GetWindowRect(hparent,&rcParent);
    SetWindowPos( m_pm->GetPaintWindow(), HWND_TOPMOST, rcParent.left, rcParent.top, 0, 0, SWP_NOSIZE |SWP_NOACTIVATE );

    return false;
}


bool CMessageBoxLogic::OnInit( TNotifyUI& msg )
{
    REG_RCKTOOL_MSG_WND_OB(m_pm->GetPaintWindow());
    if (m_byBoxType == 1)//备份升级提示
    {
        CTabLayoutUI *pControl = (CTabLayoutUI*)IRkcToolCommonOp::FindControl( m_pm, _T("MessageBoxTab") );
        if (pControl)
        {
            pControl->SelectItem(1);
        }
        IRkcToolCommonOp::SetControlText( m_strBackUpModel, m_pm, _T("LabelModel") );
        IRkcToolCommonOp::SetControlText( m_strBackUpTime, m_pm, _T("LabelTime") );
        //原Net
        TRK100NetParam tRK100NetParam;
        memset(&tRK100NetParam, 0, sizeof(TRK100NetParam));
        CRkcComInterface->GetNetWorkConfig(tRK100NetParam);

        in_addr tAddrIP;
        tAddrIP.S_un.S_addr = tRK100NetParam.dwIP;
        IRkcToolCommonOp::SetControlText( (CA2T)inet_ntoa(tAddrIP), m_pm, _T("IPOldLab") );
        tAddrIP.S_un.S_addr = tRK100NetParam.dwSubMask;
        IRkcToolCommonOp::SetControlText( (CA2T)inet_ntoa(tAddrIP), m_pm, _T("SubOldLab") );
        tAddrIP.S_un.S_addr = tRK100NetParam.dwGateway;
        IRkcToolCommonOp::SetControlText( (CA2T)inet_ntoa(tAddrIP), m_pm, _T("GateOldLab") );
        //现Net
        TCHAR tchConfig[64] = {0};
        memset(tchConfig,0,sizeof(tchConfig));
        GetPrivateProfileString(_T("TRK100NetParam"), _T("dwIP"),_T(""), tchConfig, 32, m_strBackUpIniPath);
        IRkcToolCommonOp::SetControlText( tchConfig, m_pm, _T("IPNewLab") );
        memset(tchConfig,0,sizeof(tchConfig));
        GetPrivateProfileString(_T("TRK100NetParam"), _T("dwSubMask"),_T(""), tchConfig, 32, m_strBackUpIniPath);
        IRkcToolCommonOp::SetControlText( tchConfig, m_pm, _T("SubNewLab") );
        memset(tchConfig,0,sizeof(tchConfig));
        GetPrivateProfileString(_T("TRK100NetParam"), _T("dwGateway"),_T(""), tchConfig, 32, m_strBackUpIniPath);
        IRkcToolCommonOp::SetControlText( tchConfig, m_pm, _T("GateNewLab") );

        if (wcscmp(IRkcToolCommonOp::GetControlText(m_pm, _T("IPOldLab")).c_str() , IRkcToolCommonOp::GetControlText(m_pm, _T("IPNewLab")).c_str() ) != 0 ||
            wcscmp(IRkcToolCommonOp::GetControlText(m_pm, _T("SubOldLab")).c_str() , IRkcToolCommonOp::GetControlText(m_pm, _T("SubNewLab")).c_str() ) != 0 ||
            wcscmp(IRkcToolCommonOp::GetControlText(m_pm, _T("GateOldLab")).c_str() , IRkcToolCommonOp::GetControlText(m_pm, _T("GateNewLab")).c_str() ) != 0 )
        {
            IRkcToolCommonOp::ShowControl(true, m_pm , _T("NetChangeLab"));
            IRkcToolCommonOp::ShowControl(true, m_pm , _T("NetChangeBtn"));
        }
        else
        {
            IRkcToolCommonOp::ShowControl(false, m_pm , _T("NetChangeLab"));
            IRkcToolCommonOp::ShowControl(false, m_pm , _T("NetChangeBtn"));
        }
    }
    else if (m_byBoxType == 2)//设备升级提示
    {
        CTabLayoutUI *pControl = (CTabLayoutUI*)IRkcToolCommonOp::FindControl( m_pm, _T("MessageBoxTab") );
        if (pControl)
        {
            pControl->SelectItem(2);
        }
        IRkcToolCommonOp::SetControlText( m_strUpdateModel, m_pm, _T("LabelUPModel") );
        IRkcToolCommonOp::SetControlText( m_strUpdateVer, m_pm, _T("LabelUPVer") );
        IRkcToolCommonOp::SetControlText( m_strUpdateVerNew, m_pm, _T("LabelUPVerNew") );
    }
    else//普通消息弹窗
    {
        CTabLayoutUI *pControl = (CTabLayoutUI*)IRkcToolCommonOp::FindControl( m_pm, _T("MessageBoxTab") );
        if (pControl)
        {
            pControl->SelectItem(0);
        }
        switch (m_byType)
        {
        case 0:
            m_pm->DoCase(_T("caseTypeNoBtn"));
            break;
        case 1:
            m_pm->DoCase(_T("caseTypeOneBtn"));
            break;
        case 2:
            m_pm->DoCase(_T("caseTypeTwoBtn"));
            break;
        default:
            break;
        }
        IRkcToolCommonOp::SetControlText( m_strText, m_pm, _T("LabelTip") );
        IRkcToolCommonOp::SetControlText( m_strLeftBtnText, m_pm, _T("MsgBoxOkBtn") );
    }
    return true;
}

bool CMessageBoxLogic::OnDestroy( TNotifyUI& msg )
{
    UNREG_RCKTOOL_MSG_WND_OB(m_pm->GetPaintWindow());
    //关闭net change窗口
    WINDOW_MGR_PTR->CloseWindow(g_strNetChangeDlg.c_str());  

    return true;
}

bool CMessageBoxLogic::OnCloseBtnClicked(TNotifyUI& msg)
{
    WINDOW_MGR_PTR->ShowWindow(g_stcStrBackGroundDlg.c_str(), false);  
    WINDOW_MGR_PTR->CloseWindow(g_stcStrMessageBoxDlg.c_str(),IDNO);  
    return false;
}

bool CMessageBoxLogic::OnOKBtnClicked(TNotifyUI& msg)
{
    if (m_emOperation == Emue_Restore)
    {
        CRkcComInterface->ReBootRk();
    }
    WINDOW_MGR_PTR->ShowWindow(g_stcStrBackGroundDlg.c_str(), false);  
    WINDOW_MGR_PTR->CloseWindow(g_stcStrMessageBoxDlg.c_str(),IDOK);  
    return false;
}

bool CMessageBoxLogic::OnCancelBtnClicked(TNotifyUI& msg)
{
    WINDOW_MGR_PTR->ShowWindow(g_stcStrBackGroundDlg.c_str(), false);  
    WINDOW_MGR_PTR->CloseWindow(g_stcStrMessageBoxDlg.c_str(),IDCANCEL);  
    return false;
}

bool CMessageBoxLogic::OnNetChangeBtnClicked(TNotifyUI& msg)
{
    //m_pm->DoCase(_T("caseShowNetDetail"));
    RECT rc;
    GetWindowRect(m_pm->GetPaintWindow(),&rc);
    POINT ptMouse = msg.ptMouse;
    ptMouse.x += rc.left;
    ptMouse.y += rc.top;
    ShowNetChange(ptMouse, m_strBackUpIniPath);
    return true;
}

bool CMessageBoxLogic::OnSpaceLayoutClicked(TNotifyUI& msg)
{
    //m_pm->DoCase(_T("caseCloseNetDetail"));
    return true;
}

bool CMessageBoxLogic::OnRkcRestone( WPARAM wparam, LPARAM lparam, bool& bHandle )
{
    bool bIsSuccess = (bool)wparam;
    EMRK100OptRtn emErr = (EMRK100OptRtn)lparam;
    if (bIsSuccess == false)
    {
        m_pm->DoCase(_T("caseTypeOneBtn"));
        IRkcToolCommonOp::SetControlText( _T("恢复出厂失败，请稍后再试"), m_pm, _T("LabelTip") );
    }
    else
    {
        m_emOperation = Emue_Restore;
        m_pm->DoCase(_T("caseTypeOneBtn"));
        IRkcToolCommonOp::SetControlText( _T("恢复出厂成功，请重新登录"), m_pm, _T("LabelTip") );
    }
    return true;
}

bool CMessageBoxLogic::OnRkcDisconnected( WPARAM wparam, LPARAM lparam, bool& bHandle )
{
    if (wcscmp( IRkcToolCommonOp::GetControlText( m_pm, _T("LabelTip") ).c_str() , _T("设备升级成功，即将进入重启，请勿断电！") ) != 0 &&
        wcscmp( IRkcToolCommonOp::GetControlText( m_pm, _T("LabelTip") ).c_str() , _T("账号已在其他地方登录") ) != 0)
    {
        //关闭弹窗
        WINDOW_MGR_PTR->ShowWindow(g_stcStrBackGroundDlg.c_str(), false);  
        WINDOW_MGR_PTR->CloseWindow(g_stcStrMessageBoxDlg.c_str(),IDCANCEL);  
    }
    return true;
}