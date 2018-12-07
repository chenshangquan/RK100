

#if !defined _LOGICFACTORY_H_
#define _LOGICFACTORY_H_

#pragma once

namespace AppFrame
{

class CLogicFactory : public ILogicFactory ,public tmplContainer<tstring, PFnCreateLogic>
{
public:
	CLogicFactory();
	virtual ~CLogicFactory();
	ILogic* Create(LPCTSTR lpszLogic);
	void Register(LPCTSTR lpszLogic, PFnCreateLogic pFunc);
};

}

#endif // !defined(AFX_LOGICMANAGER_H__ABF252B5_153E_42CE_BF88_AF7A88EE9E7B__INCLUDED_)
