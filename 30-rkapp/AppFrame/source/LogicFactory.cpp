// LogicManager.cpp: implementation of the CLogicManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "logicfactory.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

using namespace AppFrame;

CLogicFactory::CLogicFactory()
{
} 

CLogicFactory::~CLogicFactory()
{

}

ILogic* CLogicFactory::Create(LPCTSTR lpszLogic)
{
	PFnCreateLogic pFunc = Find(lpszLogic);
	if ( pFunc != NULL )
	{
		return (*pFunc)();
	}
	return NULL;
}

void CLogicFactory::Register( LPCTSTR lpszLogic, PFnCreateLogic pFunc )
{
	if ( pFunc != 0 )
	{
		Add(lpszLogic, pFunc);
	}
}
