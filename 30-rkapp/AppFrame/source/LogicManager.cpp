// LogicManager.cpp: implementation of the CLogicManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LogicManager.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace AppFrame
{
	
CLogicManager::CLogicManager()
{

}

CLogicManager::~CLogicManager()
{

}

ILogic* CLogicManager::Create(LPCTSTR lpszLogic)
{
	ILogic* pLogic = LOGFACTORY()->Create(lpszLogic);
	if ( pLogic != 0 )
	{
		Add(lpszLogic, pLogic);
	}
	return pLogic;
}

} // namespace AppFrame end 