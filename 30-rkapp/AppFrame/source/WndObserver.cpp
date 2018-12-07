// WndObserver.cpp: implementation of the CWndObserver class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WndObserver.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
namespace AppFrame
{
	
bool CWndObserver::Update( TMsgParam& tMsgParma )
{
	return ::SendMessage( m_hWnd, tMsgParma.wMsgId, tMsgParma.pData, tMsgParma.lParam );
}

bool CWndObserver::UpdateAsyn(TMsgParam& tMsgParma)
{
	return ::PostMessage(m_hWnd, tMsgParma.wMsgId, tMsgParma.pData, tMsgParma.lParam );
}

} // namespace AppFrame end 
