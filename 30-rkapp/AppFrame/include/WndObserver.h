// WndObserver.h: interface for the CWndObserver class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WNDOBSERVER_H__33732688_7A3B_430B_A809_05A6DE2085DC__INCLUDED_)
#define AFX_WNDOBSERVER_H__33732688_7A3B_430B_A809_05A6DE2085DC__INCLUDED_

#pragma once

namespace AppFrame
{
/*
	窗口类型的Ob，消息处理采用SendMessage/PostMessage
*/
class CWndObserver : public IObserver_MsgPrama
{
public:
	CWndObserver( HWND hWnd ) : m_hWnd(hWnd){}
	virtual ~CWndObserver(){}
	virtual bool Update( TMsgParam& tMsgParma );
	virtual bool UpdateAsyn(TMsgParam& tMsgParma);
protected:
	HWND m_hWnd;
};

/*
	添加一个HWND的Ob
*/
#define REG_MSG_OBSERVER_HWND( hWnd ) \
	IMsgManager::GetSingletonPtr()->AddObserver( new CWndObserver(hWnd) );

/*
	添加一个AppWindow的Ob
*/
#define REG_MSG_OBSERVER_APPWINDOW( pAppWindow ) \
	IMsgManager::GetSingletonPtr()->AddObserver( new CWndObserver( pAppWindow->GetHWND() ) );

} // namespace AppFrame end 

#endif // !defined(AFX_WNDOBSERVER_H__33732688_7A3B_430B_A809_05A6DE2085DC__INCLUDED_)
