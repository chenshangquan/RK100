// ControlFactory.cpp: implementation of the CControlFactory class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "structdef.h"
#include "ControlFactory.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
namespace AppFrame
{
	
const tstring CControlFactory::strSubControl = _T("subcontrol.xml");
Control* CControlFactory::GetControl(LPCTSTR lpstrName)
{
	DocNode xmlNode = DOCMNGR()->GetNode(CControlFactory::strSubControl.c_str(), lpstrName);
	if (xmlNode.IsValid())
	{
		CDialogBuilder cBuilder;

		Control* pControl = cBuilder.Create(&xmlNode);

		return pControl;
	}
	return NULL;
}

} // namespace AppFrame end 