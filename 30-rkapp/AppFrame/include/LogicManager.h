// LogicManager.h: interface for the CLogicManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOGICMANAGER_H__ABF252B5_153E_42CE_BF88_AF7A88EE9E7B__INCLUDED_)
#define AFX_LOGICMANAGER_H__ABF252B5_153E_42CE_BF88_AF7A88EE9E7B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace AppFrame
{
	
class CLogicManager : public ILogicManager 
{
public:
	CLogicManager();
	virtual ~CLogicManager();
	ILogic* Create( LPCTSTR lpszLogic );
};

} // namespace AppFrame end 

#endif // !defined(AFX_LOGICMANAGER_H__ABF252B5_153E_42CE_BF88_AF7A88EE9E7B__INCLUDED_)
