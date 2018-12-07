#include "StdAfx.h"
#include "netchangelogic.h"

APP_BEGIN_MSG_MAP(CNetChangeLogic, CNotifyUIImpl)

	MSG_CREATEWINDOW(_T("NetDetailLayout"), OnCreate)
	MSG_INIWINDOW(_T("NetDetailLayout"), OnInit)
    MSG_WINDOWDESTORY(_T("NetDetailLayout"), OnDestroy)

APP_END_MSG_MAP()

static POINT pt_Mouse;//点击位置
static CString  m_strNetchangeIniPath = _T("");

bool showNetChange(POINT pt, LPCTSTR lpstrIniPath)
{
    m_strNetchangeIniPath = lpstrIniPath;
    pt_Mouse = pt;
    return WINDOW_MGR_PTR->ShowWindow(g_strNetChangeDlg.c_str());
}

CNetChangeLogic::CNetChangeLogic( void )
{
}


CNetChangeLogic::~CNetChangeLogic(void)
{
}


bool CNetChangeLogic::OnCreate( TNotifyUI& msg )
{
	REG_RCKTOOL_MSG_WND_OB(m_pm->GetPaintWindow());
	return false;
}

bool CNetChangeLogic::OnInit(TNotifyUI& msg)
{
    //位置
    SetPos();

    //内容
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
    GetPrivateProfileString(_T("TRK100NetParam"), _T("dwIP"),_T(""), tchConfig, 32, m_strNetchangeIniPath);
    IRkcToolCommonOp::SetControlText( tchConfig, m_pm, _T("IPNewLab") );
    memset(tchConfig,0,sizeof(tchConfig));
    GetPrivateProfileString(_T("TRK100NetParam"), _T("dwSubMask"),_T(""), tchConfig, 32, m_strNetchangeIniPath);
    IRkcToolCommonOp::SetControlText( tchConfig, m_pm, _T("SubNewLab") );
    memset(tchConfig,0,sizeof(tchConfig));
    GetPrivateProfileString(_T("TRK100NetParam"), _T("dwGateway"),_T(""), tchConfig, 32, m_strNetchangeIniPath);
    IRkcToolCommonOp::SetControlText( tchConfig, m_pm, _T("GateNewLab") );

	return true;
}

bool CNetChangeLogic::OnDestroy( TNotifyUI& msg )
{
    UNREG_RCKTOOL_MSG_WND_OB(m_pm->GetPaintWindow());
    return true;
}

bool CNetChangeLogic::SetPos()
{
	Window* pWnd = WINDOW_MGR_PTR->GetWindow(g_strNetChangeDlg.c_str());
	if ( pWnd != NULL )
	{
		pWnd->SetAutoHide( true );
	}
	RECT rt;
	GetWindowRect( m_pm->GetPaintWindow(),&rt );
	s32 nTop = pt_Mouse.y;
	s32 nLeft = pt_Mouse.x;
	SetWindowPos( m_pm->GetPaintWindow(), HWND_TOPMOST, nLeft, nTop, 0, 0, SWP_NOSIZE |SWP_NOACTIVATE );
	return true;
}
