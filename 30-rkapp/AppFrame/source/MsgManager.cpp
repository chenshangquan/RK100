// MsgManager.cpp: implementation of the CMsgManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MsgManager.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace AppFrame
{
	
vector<IObserver_MsgPrama*>::iterator CMsgManager::FindObserver( IObserver_MsgPrama* pObserver )
{
	ObserverList::iterator begin = m_observers.begin();
	while ( begin != m_observers.end() )
	{
		if ( *begin == pObserver )
		{
			return begin;
		}
		begin++;
	}
	return begin;
}

void CMsgManager::AddObserver( IObserver_MsgPrama* pObserver )
{
	ObserverList::iterator begin = FindObserver( pObserver );
	if ( begin == m_observers.end() )
	{
		m_observers.push_back( pObserver );
	}
}

void CMsgManager::RemoveObserver( IObserver_MsgPrama* pObserver )
{
	ObserverList::iterator begin = FindObserver( pObserver );
	if ( begin != m_observers.end() )
	{
		m_observers.erase( begin );
	}	
}

void CMsgManager::SendMsg( TMsgParam& tMsgParam )
{
	ObserverList::iterator begin = m_observers.begin();
	while ( begin != m_observers.end() )
	{
		IObserver_MsgPrama* pObserver = *begin;
		if ( pObserver != 0 )
		{
			pObserver->Update( tMsgParam );
		}
		begin++;
	}
}

void CMsgManager::PostMsg(TMsgParam& tMsgParam)
{
	ObserverList::iterator begin = m_observers.begin();
	while (begin != m_observers.end())
	{
		IObserver_MsgPrama* pObserver = *begin;
		if (pObserver != 0)
		{
			pObserver->UpdateAsyn(tMsgParam);
		}
		begin++;
	}
}

CMsgManager::~CMsgManager()
{
	ObserverList::iterator begin = m_observers.begin();
	while (begin != m_observers.end())
	{
		IObserver_MsgPrama* pObserver = *begin;
		delete pObserver;
		begin++;
	}
	m_observers.clear();
}

} // namespace AppFrame end 