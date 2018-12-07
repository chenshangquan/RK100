#include "StdAfx.h"
#include "rkctoolmsgmanager.h"
#include "WndObserver.h"

CRkcToolMsgManager::CRkcToolMsgManager(void)
{
}


CRkcToolMsgManager::~CRkcToolMsgManager(void)
{
}

void CRkcToolMsgManager::AddObserver(IObserver_MsgPrama* pObserver)
{
	m_cMsgManager.AddObserver(pObserver);
}


void CRkcToolMsgManager::RemoveObserver(IObserver_MsgPrama* pObserver)
{
	m_cMsgManager.RemoveObserver(pObserver);
}

void CRkcToolMsgManager::SendMsg(TMsgParam& tMsgParam)
{
	m_cMsgManager.SendMsg(tMsgParam);
}

void CRkcToolMsgManager::PostMsg( TMsgParam& tMsgParam )
{
	m_cMsgManager.PostMsg(tMsgParam);
}

void CRkcToolMsgManager::AddWindowObserver(HWND hwnd)
{
	WndObMap::iterator itr = m_mapWndObs.find(hwnd);
	if (itr != m_mapWndObs.end())
	{
		return;
	}
	CWndObserver *pWndOb = new CWndObserver(hwnd);
	m_mapWndObs[hwnd] = pWndOb;
	m_cMsgManager.AddObserver(pWndOb);
}

void CRkcToolMsgManager::RemoveWindowObserver( HWND hwnd )
{
	WndObMap::iterator itr = m_mapWndObs.find(hwnd);
	if (itr == m_mapWndObs.end())
	{
		return;
	}
	IObserver_MsgPrama *pWndOb = itr->second;
	m_cMsgManager.RemoveObserver(pWndOb);
	delete pWndOb;
	m_mapWndObs.erase(itr);
}
