#include "StdAfx.h"
#include "rkcinterface.h"

CRkcInterface* CRkcInterface::m_pMySelf = NULL;

CRkcInterface::CRkcInterface() :
                 m_pRkcSession(NULL),
	             m_pSysCtrlIf(NULL),
                 m_pConfigCtrlIf(NULL),
                 m_pSearchCtrlIf(NULL)
{
    m_hRecvWnd = ::CreateWindowEx(0, _T("Static"), _T("RckCommon"), WS_DISABLED,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL, NULL, 0, 0);

    if ( m_hRecvWnd != NULL )
    {
        m_wndprocOld = reinterpret_cast<WNDPROC>(GetWindowLong(m_hRecvWnd, GWL_WNDPROC));
        SetWindowLong(m_hRecvWnd, GWL_WNDPROC, reinterpret_cast<s32>(WndProc));
    } 
    else
    {
        m_wndprocOld = NULL;
    }
}

LRESULT CALLBACK CRkcInterface::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    NOTIFY_MSG( uMsg, wParam, lParam );
    return 0;
}

CRkcInterface* CRkcInterface::GetCommIF()
{
    if ( NULL != m_pMySelf )
    {
        return m_pMySelf ;
    }

    m_pMySelf = new CRkcInterface;
    return m_pMySelf;
}

void CRkcInterface::DestroyCommIF()
{   
    if ( NULL != m_pMySelf )
    {
        delete m_pMySelf;
        m_pMySelf = NULL;
    }

    DesdroySession();
}

void CRkcInterface::CreateSession()
{
    CRckLib::CreateSession( &m_pRkcSession );

    m_pRkcSession->RkcGetInterface( &m_pSysCtrlIf );
    if (m_pSysCtrlIf)
    {
        m_pSysCtrlIf->SetNotifyWnd(GetRecvWindow());
    }

    m_pRkcSession->RkcGetInterface( &m_pConfigCtrlIf );
    if (m_pConfigCtrlIf)
    {
        m_pConfigCtrlIf->SetNotifyWnd(GetRecvWindow());
    }

    m_pRkcSession->RkcGetInterface( &m_pSearchCtrlIf );
    if (m_pSearchCtrlIf)
    {
        m_pSearchCtrlIf->SetNotifyWnd(GetRecvWindow());
    }
}

void CRkcInterface::DesdroySession()
{   	
    CRckLib::DestroySession( &m_pRkcSession );
}