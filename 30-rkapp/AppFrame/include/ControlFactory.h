// ControlFactory.h: interface for the CControlFactory class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONTROLFACTORY_H__E0D5A9EA_6767_4FDC_BF81_D225144B7D0B__INCLUDED_)
#define AFX_CONTROLFACTORY_H__E0D5A9EA_6767_4FDC_BF81_D225144B7D0B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace AppFrame
{

class CControlFactory : public IControlFactory, public tmplContainer<tstring,Control>
{
public:
	static const tstring strSubControl;		//×Ó¿Ø¼þÂ·¾¶
public:
	virtual Control* GetControl( LPCTSTR lpstrName );
};

} // namespace AppFrame end 

#endif // !defined(AFX_CONTROLFACTORY_H__E0D5A9EA_6767_4FDC_BF81_D225144B7D0B__INCLUDED_)
