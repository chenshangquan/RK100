#include "stdafx.h"
//#include "searchequipmentlogic.h"
//#include "setmenulogic.h"
//#include "toolframelogic.h"
//#include "modifypasswordlogic.h"
//#include "messageboxlogic.h"
//#include "tipboxlogic.h"
#include "backgroundlogic.h"

template<> CBackGroundLogic* Singleton<CBackGroundLogic>::ms_pSingleton  = NULL;

APP_BEGIN_MSG_MAP(CBackGroundLogic, CNotifyUIImpl)
    MSG_CREATEWINDOW(_T("BackGroundLayout"), OnCreate)
    MSG_INIWINDOW(_T("BackGroundLayout"), OnInit)

APP_END_MSG_MAP()

CBackGroundLogic::CBackGroundLogic()
{
}

CBackGroundLogic::~CBackGroundLogic()
{
}

bool CBackGroundLogic::OnCreate( TNotifyUI& msg )
{
    s32 nTop = 0;
    RECT rcParent;
    HWND hparent = GetParent(m_pm->GetPaintWindow());
    GetWindowRect(hparent,&rcParent);
    SetWindowPos( m_pm->GetPaintWindow(), NULL, rcParent.left, rcParent.top, 0, 0, SWP_NOSIZE |SWP_NOACTIVATE );
    return false;
}

bool CBackGroundLogic::OnInit( TNotifyUI& msg )
{
    REG_RCKTOOL_MSG_WND_OB(m_pm->GetPaintWindow());

    return true;
}
