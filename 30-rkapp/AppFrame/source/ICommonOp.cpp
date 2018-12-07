// ICommonOp.cpp: implementation of the ICommonOp class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ICommonOp.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace AppFrame
{
	
tstring ICommonOp::GetNodeValueStr( DocNode Node, LPCTSTR lpszTag)
{
	return Node.GetAttributeValue( lpszTag );
}

bool ICommonOp::IsDigit( LPCTSTR lpszDig )
{
	u32 dwLen = _tcslen(lpszDig);
	if (dwLen == 0)
		return false;
	for (u32 dwIdx = 0; dwIdx < dwLen; dwIdx++)
	{
		if (lpszDig[dwIdx] < _T('0') || lpszDig[dwIdx] > _T('9'))
			return false;
	}
	return true;
}

CControlUI* ICommonOp::FindControl( CPaintManagerUI *pManager, LPCTSTR lpszControlName, CControlUI *pParent /*= NULL*/)
{
	if (pManager == NULL)
	{
		return NULL;
	}

	if (pParent == NULL)
	{
		return pManager->FindControl(lpszControlName);
	}
	else
	{
		return pManager->FindSubControlByName(pParent, lpszControlName);
	}
}
bool ICommonOp::EnableControl(bool bEnabled, CPaintManagerUI *pManager, LPCTSTR lpszControlName, CControlUI *pParent /*= NULL*/)
{
	CControlUI *pControl = FindControl(pManager, lpszControlName, pParent);
	if ( pControl != NULL )
	{
		pControl->SetEnabled ( bEnabled );
		return true;
	}
	return false;
}

bool ICommonOp::ShowControl( bool bVisible, CPaintManagerUI *pManager ,LPCTSTR lpszControlName, CControlUI *pParent /*= NULL*/ )
{
	CControlUI *pControl = FindControl(pManager, lpszControlName, pParent);
	if ( pControl != NULL )
	{
		pControl->SetVisible(bVisible);
		return true;
	}
	return false;

}

bool ICommonOp::SetControlText( LPCTSTR lpszText, CPaintManagerUI *pManager, LPCTSTR lpszControlName, CControlUI *pParent  /*= NULL*/)
{
	CControlUI *pControl = FindControl(pManager, lpszControlName, pParent);
	if ( pControl != NULL )
	{
		pControl->SetText( lpszText );
		return true;
	}
	return false;
}

tstring ICommonOp::GetControlText( CPaintManagerUI *pManager , LPCTSTR lpszControlName, CControlUI *pParent /*= NULL*/ )
{
	CControlUI *pControl = FindControl(pManager, lpszControlName, pParent);
	if ( pControl != NULL )
	{
	    return pControl->GetText().GetData();
	}
	return _T("");
}

bool ICommonOp::OptionSelectNoMsg(bool bSelect, CPaintManagerUI *pManager, LPCTSTR lpszControlName, CControlUI *pParent  /*= NULL*/)
{
    COptionUI *pOpt = (COptionUI*)FindControl(pManager, lpszControlName, pParent);
    if ( pOpt != NULL )
    {
        pOpt->SetCheckNoMsg( bSelect );
        return true;
    }
    return false;
}

bool ICommonOp::OptionSelect(bool bSelect, CPaintManagerUI *pManager, LPCTSTR lpszControlName, CControlUI *pParent  /*= NULL*/)
{
	COptionUI *pOpt = (COptionUI*)FindControl(pManager, lpszControlName, pParent);
	if ( pOpt != NULL )
	{
		pOpt->Selected( bSelect );
		return true;
	}
	return false;
}

bool ICommonOp::IsOptionSelected(CPaintManagerUI *pManager, LPCTSTR lpszControlName, CControlUI *pParent /*= NULL*/)
{
    COptionUI *pControl = (COptionUI*)FindControl(pManager, lpszControlName, pParent);
    if ( pControl != NULL )
    {
        return pControl->IsSelected();
    }
    return false;
}

bool ICommonOp::SetControlBkImg(LPCTSTR lpszFile, CPaintManagerUI *pManager, LPCTSTR lpszControlName, CControlUI *pParent /* = NULL */)
{
	CControlUI *pControl = FindControl(pManager, lpszControlName, pParent);
	if ( pControl != NULL )
	{
		pControl->SetBkImage(lpszFile);
		return true;
	}
	return false;
}

bool ICommonOp::SetControlBkColor(LPCTSTR lpszColor, CPaintManagerUI *pManager, LPCTSTR lpszControlName, CControlUI *pParent /*= NULL*/)
{
	CControlUI *pControl = FindControl(pManager, lpszControlName, pParent);
	if ( pControl != NULL )
	{
		pControl->SetAttribute(_T("bkcolor"), lpszColor);
		return true;
	}
	return false;
}

tstring ICommonOp::GetFolderDir(const tstring strNotify )
{
	TCHAR achDir[MAX_PATH_LENTH];
	memset( achDir, 0, sizeof(achDir) );
	BROWSEINFO bInfo = {0};  
	bInfo.hwndOwner = GetForegroundWindow();	//父窗口  
	bInfo.lpszTitle = strNotify.c_str();  
	bInfo.ulFlags = BIF_RETURNONLYFSDIRS;  
	//关于更多的 ulFlags 参考 http://msdn.microsoft.com/en-us/library/bb773205(v=vs.85).aspx  
	LPITEMIDLIST lpDlist;  
	lpDlist = SHBrowseForFolder( &bInfo );  
	if ( lpDlist != NULL )	//单击了确定按钮  
	{  
		SHGetPathFromIDList( lpDlist, achDir ); 
	}
	return achDir;
};

void ICommonOp::StringSplit(const tstring& str, const tstring& delim, std::vector< tstring >& ret)
{
	size_t last = 0;
	size_t index = str.find_first_of(delim, last);
	while (index != tstring::npos)
	{
		tstring strSub = str.substr(last, index - last);
		ret.push_back(strSub);
		last = index + 1;
		index = str.find_first_of(delim, last);
	}
	if (index - last > 0)
	{
		ret.push_back(str.substr(last, index - last));
	}
}

BOOL32 ICommonOp::ModifyStyle(HWND hWnd, DWORD dwRemove, DWORD dwAdd, UINT nFlags)
{
	ASSERT(::IsWindow(hWnd));
	ASSERT(hWnd != NULL);
	DWORD dwStyle = ::GetWindowLong(hWnd, GWL_STYLE);
	DWORD dwNewStyle = (dwStyle & ~dwRemove) | dwAdd;
	if (dwStyle == dwNewStyle)
		return FALSE;

	::SetWindowLong(hWnd, GWL_STYLE, dwNewStyle);
	if (nFlags != 0)
	{
		::SetWindowPos(hWnd, NULL, 0, 0, 0, 0,
			SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE | nFlags);
	}
	return TRUE;
}

void ICommonOp::SetTag(CControlUI* pControl, UINT_PTR tag, bool bRecursion )
{
	if ( pControl )
	{
		pControl->SetTag(tag);
		if ( bRecursion )
		{
			CContainerUI* pContainer = dynamic_cast<CContainerUI*>(pControl);
			if ( pContainer )
			{
				s32 i = 0;
				for (; i < pContainer->GetCount(); ++i )
				{
					CControlUI* pSubControl = pContainer->GetItemAt(i);
					SetTag(pSubControl, tag, bRecursion);
				}
			}
		}
	}
}

bool ICommonOp::SetControlTextColor( LPCTSTR lpszColor, CPaintManagerUI *pManager, LPCTSTR lpszControlName, CControlUI *pParent /*= NULL*/ )
{
	CControlUI *pControl = FindControl(pManager, lpszControlName, pParent);
	if ( pControl != NULL )
	{
		pControl->SetAttribute(_T("textcolor"), lpszColor);
		return true;
	}
	return false;
}

} // namespace AppFrame end 