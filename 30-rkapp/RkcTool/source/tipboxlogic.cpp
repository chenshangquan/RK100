#include "stdafx.h"
#include "tipboxlogic.h"

static UINT     g_nShowTipTimerID;              //timer 的id,用于控制显示时间
#define         TIME_SHOWTIP        2000        //定时器时间间隔

VOID  CALLBACK  CTipTimerFun(  HWND   hwnd,   UINT   uMsg, UINT_PTR  idEvent, DWORD   dwTime  )
{
    if ( idEvent == g_nShowTipTimerID )
    {
        KillTimer( NULL, g_nShowTipTimerID );
        g_nShowTipTimerID = 0;
        WINDOW_MGR_PTR->CloseWindow(g_stcStrTipBoxDlg.c_str());  
    }
}

APP_BEGIN_MSG_MAP(CTipBoxLogic, CNotifyUIImpl)
    MSG_CREATEWINDOW(_T("TipBoxLayout"), OnCreate)
    MSG_INIWINDOW(_T("TipBoxLayout"), OnInit)
    MSG_WINDOWDESTORY(_T("TipBoxLayout"), OnDestroy)
APP_END_MSG_MAP()

static CString m_strText = _T("");

bool showTipBox(LPCTSTR lpstrText)
{
    if (WINDOW_MGR_PTR->IsWindowVisible(g_stcStrTipBoxDlg.c_str()))
    {
        return false;
    }
    m_strText = lpstrText;
    return WINDOW_MGR_PTR->ShowModal(g_stcStrTipBoxDlg.c_str());
}

CTipBoxLogic::CTipBoxLogic()
{
    g_nShowTipTimerID = 0;
}

CTipBoxLogic::~CTipBoxLogic()
{
}

bool CTipBoxLogic::OnCreate( TNotifyUI& msg )
{
    SetWindowPos( m_pm->GetPaintWindow(), NULL, 512, 475, 0, 0, SWP_NOSIZE |SWP_NOACTIVATE );
    return false;
}


bool CTipBoxLogic::OnInit( TNotifyUI& msg )
{
    REG_RCKTOOL_MSG_WND_OB(m_pm->GetPaintWindow());
    IRkcToolCommonOp::SetControlText( m_strText, m_pm, _T("LabelTip") );

    //开始定时器 到达时间后关闭窗口
    g_nShowTipTimerID = SetTimer( NULL, 0, TIME_SHOWTIP, CTipTimerFun );

    return true;
}

bool CTipBoxLogic::OnDestroy( TNotifyUI& msg )
{
    UNREG_RCKTOOL_MSG_WND_OB(m_pm->GetPaintWindow());
    return true;
}

