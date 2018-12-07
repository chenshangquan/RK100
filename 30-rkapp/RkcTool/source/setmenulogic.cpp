#include "stdafx.h"
#include "searchequipmentlogic.h"
#include "setmenulogic.h"
#include "toolframelogic.h"
#include "modifypasswordlogic.h"
#include "messageboxlogic.h"
#include "tipboxlogic.h"

#define MENU_LEFT_POS   964           //菜单窗口到主窗口左侧位置
#define MENU_TOP_POS    82            //菜单窗口到主窗口顶部位置

template<> CSetMenuLogic* Singleton<CSetMenuLogic>::ms_pSingleton  = NULL;

APP_BEGIN_MSG_MAP(CSetMenuLogic, CNotifyUIImpl)
    MSG_CREATEWINDOW(_T("SetMenuLayout"), OnCreate)
    MSG_INIWINDOW(_T("SetMenuLayout"), OnInit)

    MSG_ITEMDOWN(_T("ModifyPasswrd"), OnMdPwdItemClicked)
    MSG_ITEMDOWN(_T("Reboot"), OnRebootItemClicked)
    MSG_ITEMDOWN(_T("About"), OnAboutInfoItemClicked)
APP_END_MSG_MAP()

CSetMenuLogic::CSetMenuLogic()
{
}

CSetMenuLogic::~CSetMenuLogic()
{
}

bool CSetMenuLogic::OnCreate( TNotifyUI& msg )
{
    m_nLeft = MENU_LEFT_POS;
    m_nTop  = MENU_TOP_POS;

    RECT rcParent;
    HWND hparent = GetParent(m_pm->GetPaintWindow());
    GetWindowRect(hparent,&rcParent);

    if ( CPaintManagerUI::IsSelfAdaption() )
    {
        float fAdpX, fAdpY;
        CPaintManagerUI::GetAdpResolution( &fAdpX, &fAdpY );
        m_nLeft = s32(m_nLeft * fAdpX);
        m_nTop = s32(m_nTop * fAdpY);
    }

    m_nLeft += rcParent.left;
    m_nTop  += rcParent.top;

    SetWindowPos( m_pm->GetPaintWindow(), NULL, m_nLeft, m_nTop, 0, 0, SWP_NOSIZE |SWP_NOACTIVATE );

    return false;
}

bool CSetMenuLogic::OnInit( TNotifyUI& msg )
{
    REG_RCKTOOL_MSG_WND_OB(m_pm->GetPaintWindow());

    //启用自动隐藏
    Window* pAppWindow = WINDOW_MGR_PTR->GetWindow(g_stcStrSetMenuDlg.c_str());
    if ( pAppWindow != NULL )
    {
        pAppWindow->SetAutoHide( true );
    }

    return true;
}

bool CSetMenuLogic::OnMdPwdItemClicked(TNotifyUI& msg)
{
    //隐藏菜单
    WINDOW_MGR_PTR->ShowWindow(g_stcStrSetMenuDlg.c_str(), false);

    //密码修改
    CToolFrameLogic::GetSingletonPtr()->OnTabModifyPassword();

    return true;
}

bool CSetMenuLogic::OnRebootItemClicked(TNotifyUI& msg)
{
    //隐藏菜单
    WINDOW_MGR_PTR->ShowWindow(g_stcStrSetMenuDlg.c_str(), false);

    int nBoxRe = ShowMessageBox(_T("确定重启设备？"),2);
    if (nBoxRe == IDOK)
    {
        CRkcComInterface->ReBootRk();
    }

    return true;
}

bool CSetMenuLogic::OnAboutInfoItemClicked(TNotifyUI& mst)
{
    //隐藏菜单
    WINDOW_MGR_PTR->ShowWindow(g_stcStrSetMenuDlg.c_str(), false);

    //关于信息
    CToolFrameLogic::GetSingletonPtr()->OnTabAboutInfo();

    return true;
}

void CSetMenuLogic::OnUpdateWindowPos()
{
    s32 nLeft = MENU_LEFT_POS;
    s32 nTop  = MENU_TOP_POS;

    RECT rcParent;
    HWND hparent = GetParent(m_pm->GetPaintWindow());
    GetWindowRect(hparent,&rcParent);

    if ( CPaintManagerUI::IsSelfAdaption() )
    {
        float fAdpX, fAdpY;
        CPaintManagerUI::GetAdpResolution( &fAdpX, &fAdpY );
        nLeft = s32(nLeft * fAdpX);
        nTop = s32(nTop * fAdpY);
    }

    nLeft += rcParent.left;
    nTop  += rcParent.top;

    // 
    if (nLeft != m_nLeft || nTop != m_nTop)
    {
        SetWindowPos( m_pm->GetPaintWindow(), NULL, nLeft, nTop, 0, 0, SWP_NOSIZE |SWP_NOACTIVATE );
        m_nLeft = nLeft;
        m_nTop  = nTop;
    }
}

void CSetMenuLogic::OnMenuShowInit()
{
    CListLabelElementUI *pControl = (CListLabelElementUI*)IRkcToolCommonOp::FindControl( m_pm, _T("Empty") );
    if (pControl)
    {
        m_pm->SetFocus(pControl);
    }

    m_pm->DoCase(_T("caseMenuInit"));

    return;
}

