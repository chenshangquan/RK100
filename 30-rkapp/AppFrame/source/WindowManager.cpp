// UIManager.cpp: implementation of the CWindowManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WindowManager.h"
#include "WndObserver.h"
#include "ICommonOp.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace AppFrame
{

const tstring CWindowManager::strIndexName	= _T("index.xml");
const tstring CWindowManager::strFileTag		= _T("file");
const tstring CWindowManager::strParentTag	= _T("parent");
const tstring CWindowManager::strLogicTag	= _T("logic");
const tstring CWindowManager::strStyleTag    = _T("style");
const tstring CWindowManager::strChildStyle = _T("child");
const tstring CWindowManager::strDialogStyle = _T("dialog");
const tstring CWindowManager::strFrameStyle = _T("frame");
const tstring CWindowManager::strToolStyle = _T("tool");
CWindowManager::CWindowManager() 
{
}

CWindowManager::~CWindowManager()
{

}

// 函数名：		NewWindow
// 功能：		创建新窗口
// 参数说明：	strWindowName	[in] 窗口名
//				strWindowMould	[in] 窗口模板
//				strParentWidnow	[in] 父窗口
//				dwStyle			[in] 窗口风格

Window* CWindowManager::NewWindow(LPCTSTR lpstrWindowName, LPCTSTR lpstrWindowMould,
								  LPCTSTR lpstrParentWindow, DWORD dwStyle, DWORD dwExStyle, LPVOID lpData,
								   int x, int y, int cx, int cy )
{
	HWND hParentWnd = 0;
	if (lpstrParentWindow != NULL && _tcscmp(lpstrParentWindow,_T("") )!= 0 )
	{
		CAppWindow* pParent = Find(lpstrParentWindow);
		if ( pParent )
		{
			hParentWnd = pParent->GetHWND();
		}
	}
	return NewWindow(lpstrWindowName, lpstrWindowMould, hParentWnd, dwStyle, dwExStyle, lpData, x, y, cx, cy);
}

// 函数名：		NewWindow
// 功能：		创建新窗口
// 参数说明：	strWindowName	[in] 窗口名
//				strWindowMould	[in] 窗口模板
//				hParentWnd		[in] 父窗口
//				dwStyle			[in] 窗口风格
Window* CWindowManager::NewWindow( LPCTSTR lpstrWindowName, LPCTSTR lpstrWindowMould,
								   HWND hParentWnd, DWORD dwStyle, DWORD dwExStyle, LPVOID lpData,
								   int x, int y, int cx, int cy )
{
	tstring strFile = _T("");
	bool bRet = DOCMNGR()->GetDoc( CWindowManager::strIndexName, 
		CWindowManager::strFileTag, strFile, lpstrWindowMould);
	
	if ( bRet == true )
	{
		if ( dwStyle == UI_WNDSTYLE_CHILD && hParentWnd == 0 )
		{
			//LOGEVENT( _T("没有父窗口,无法创建子窗口") );
			return 0;
		}
		
		CAppWindow* pFrame = new CAppWindow( strFile.c_str(), lpData );
		
		if( pFrame == NULL ) return false;
		
		AddNotifier( pFrame, lpstrWindowMould );
		
		pFrame->Create( hParentWnd, lpstrWindowName, dwStyle, dwExStyle, x, y, cx, cy );
		
		Add( lpstrWindowName, pFrame );
	
		return pFrame;
	}
	return 0;
}


bool CWindowManager::ShowWindowCenter(LPCTSTR lpstrName)
{
	Window* pAppWindow = Find(lpstrName);
	if ( pAppWindow != NULL )
	{
		pAppWindow->ShowWindow();
		pAppWindow->CenterWindow();
		return true;
	}
	tstring strFile = _T("");
	tstring strParent = _T("");
	//从索引取窗口文件(file)
	bool bRet = DOCMNGR()->GetDoc( CWindowManager::strIndexName, 
		CWindowManager::strFileTag, strFile, lpstrName);

	if ( bRet == true )
	{
		DWORD dwStyle = 0;
		DWORD dwStyleEx = 0;
		tstring strStyle;

		//取父窗口文件(parent)	
		bRet = DOCMNGR()->GetDoc( CWindowManager::strIndexName,
			CWindowManager::strParentTag, strParent, lpstrName);
		bRet = DOCMNGR()->GetDoc( CWindowManager::strIndexName,
			CWindowManager::strStyleTag, strStyle, lpstrName);
		if ( strStyle == strChildStyle )
		{
			dwStyle = UI_WNDSTYLE_CHILD;
			dwStyleEx = 0;
		}
		else if ( strStyle == strDialogStyle )
		{
			dwStyle = UI_WNDSTYLE_DIALOG;
			dwStyleEx = UI_WNDSTYLE_EX_DIALOG;
		}
		else if ( strStyle == strToolStyle )
		{
			dwStyle = UI_WNDSTYLE_DIALOG;
			dwStyleEx = UI_WNDSTYLE_EX_TOOL;
		}
		else
		{
			dwStyle = UI_WNDSTYLE_FRAME;
			dwStyleEx = UI_WNDSTYLE_EX_FRAME;
		}

		Window* pFrame = NewWindow(lpstrName, lpstrName, strParent.c_str(), dwStyle, dwStyleEx);

		if ( pFrame != 0 && dwStyle != UI_WNDSTYLE_CHILD )
		{
			pFrame->CenterWindow();
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}

bool CWindowManager::HideWindow( LPCTSTR lpstrName )
{
	Window* pWnd = Find(lpstrName);
	if ( pWnd == NULL )
	{
	    LOGEVENT( _T("窗口未创建") )
		return false;
	}
	pWnd->ShowWindow( false );
	return true;
}

bool CWindowManager::AddNotifier( Window* pWnd, LPCTSTR lpstrName )
{
	if ( pWnd == NULL )
	{
		return false;
	}
	tstring strLogic = _T("");
	//取消logic字符串
	bool bRet = DOCMNGR()->GetDoc( CWindowManager::strIndexName, 
		CWindowManager::strLogicTag, strLogic, lpstrName);

	if ( bRet == true )
	{
		tstring sub_str;
		//根据logic字符串创建界面消息处理对象，并添加到notifier

		vector<tstring> vecSubStr;
		tstring strSpilt = _T("|");
		ICommonOp::StringSplit( strLogic, strSpilt, vecSubStr);
		unsigned int dwIdx = 0;
		while( dwIdx < vecSubStr.size())         
		{
			tstring sub_str = vecSubStr[dwIdx++];
			ILogic* pLogic = ILogicManager::GetSingletonPtr()->Create(sub_str.c_str());
			if ( pLogic != 0 )
			{
				pWnd->AddNotifier( pLogic );
			}
		}
	}
	return true;
}

bool CWindowManager::ShowModal( LPCTSTR lpstrName, LPCTSTR lpstrParentWindow )
{
	if (ShowWindowCenter(lpstrName))
	{
		Window *pWnd = Find(lpstrName);
		if ( pWnd != NULL )
		{
			if (lpstrParentWindow != NULL)
			{
				HWND hParentWnd = 0;

				CAppWindow* pParent = Find(lpstrParentWindow);
				if ( pParent )
				{
					hParentWnd = pParent->GetHWND();
					::SetWindowLong(pWnd->GetHWND(), GWL_HWNDPARENT,(LONG)hParentWnd);	
				}
			}
			
			return (pWnd->ShowModal() == IDOK);
		}
	}

	return false;
}

u8 CWindowManager::ShowModalGetRe( LPCTSTR lpstrName, LPCTSTR lpstrParentWindow )
{
    if (ShowWindowCenter(lpstrName))
    {
        Window *pWnd = Find(lpstrName);
        if ( pWnd != NULL )
        {
            if (lpstrParentWindow != NULL)
            {
                HWND hParentWnd = 0;

                CAppWindow* pParent = Find(lpstrParentWindow);
                if ( pParent )
                {
                    hParentWnd = pParent->GetHWND();
                    ::SetWindowLong(pWnd->GetHWND(), GWL_HWNDPARENT,(LONG)hParentWnd);	
                }
            }

            return pWnd->ShowModal();
        }
    }

    return false;
}

bool CWindowManager::CloseWindow( LPCTSTR lpstrName, UINT nRet )
{
	Window* pWnd = Find(lpstrName);
	if ( pWnd )
	{
		pWnd->Close(nRet);
		Remove(lpstrName);
	}
	return true;
}

Window* CWindowManager::GetWindow( LPCTSTR lpstrName )
{
	return Find(lpstrName);
}

Control* CWindowManager::GetControl(LPCTSTR lpstrWindow, LPCTSTR lpstrControl)
{
	Window* pWnd = Find(lpstrWindow);
	if ( pWnd != 0 )
	{
		return pWnd->m_pm.FindControl(lpstrControl);
	}
	return 0;
}

void CWindowManager::SetResourcePath(LPCTSTR lpstrFile)
{
	//CPaintManagerUI::SetResourcePath(strFile);
	CPaintManagerUI::SetResourceZip(lpstrFile);
}


bool CWindowManager::ShowWindow(LPCTSTR lpstrName, bool bShow)
{
	Window* pAppWindow = Find(lpstrName);
	if ( pAppWindow != NULL )
	{
		pAppWindow->ShowWindow( bShow );
		return true;
	}
	tstring strFile = _T("");
	tstring strParent = _T("");
	//从索引取窗口文件(file)
	bool bRet = DOCMNGR()->GetDoc( CWindowManager::strIndexName, 
		CWindowManager::strFileTag, strFile, lpstrName);

	if ( bRet == true )
	{
		DWORD dwStyle = 0;
		DWORD dwStyleEx = 0;
		tstring strStyle;

		//取父窗口文件(parent)	
		bRet = DOCMNGR()->GetDoc( CWindowManager::strIndexName,
			CWindowManager::strParentTag, strParent, lpstrName);
		bRet = DOCMNGR()->GetDoc( CWindowManager::strIndexName,
			CWindowManager::strStyleTag, strStyle, lpstrName);
		if ( strStyle == strChildStyle )
		{
			dwStyle = UI_WNDSTYLE_CHILD;
			dwStyleEx = 0;
		}
		else if ( strStyle == strDialogStyle )
		{
			dwStyle = UI_WNDSTYLE_DIALOG;
			dwStyleEx = UI_WNDSTYLE_EX_DIALOG;
		}
		else if ( strStyle == strToolStyle )
		{
			dwStyle = UI_WNDSTYLE_DIALOG;
			dwStyleEx = UI_WNDSTYLE_EX_TOOL;
		}
		else
		{
			dwStyle = UI_WNDSTYLE_FRAME;
			dwStyleEx = UI_WNDSTYLE_EX_FRAME;
		}

		Window* pFrame = NewWindow(lpstrName, lpstrName, strParent.c_str(), dwStyle, dwStyleEx, 0, 0, 0);
		if ( pFrame != 0  )
		{
			pFrame->ShowWindow( bShow );
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}

bool CWindowManager::ShowWindowFromLeftToRight(LPCTSTR lpstrName, bool bShow)
{
	Window* pAppWindow = Find(lpstrName);
	if ( pAppWindow != NULL )
	{
		pAppWindow->ShowWindowFromLeftToRight(bShow);
		return true;
	}
	return false;
}

bool CWindowManager::ShowWindowFromBottomToTop(LPCTSTR lpstrName, bool bShow)
{
	Window* pAppWindow = Find(lpstrName);
	if ( pAppWindow != NULL )
	{
		pAppWindow->ShowWindowFromBottomToTop(bShow);
		return true;
	}
	return false;
}

bool CWindowManager::ShowMainWindowLeftToRight(LPCTSTR lpstrName, bool bShow )
{
    Window* pAppWindow = Find(lpstrName);
    if ( pAppWindow != NULL )
    {
        pAppWindow->ShowMainWindowFromLeftToRight(bShow);
        return true;
    }
    return false;
}

bool CWindowManager::ShowWindowFromTopToBottom(LPCTSTR lpstrName, bool bShow )
{
    Window* pAppWindow = Find(lpstrName);
    if ( pAppWindow != NULL )
    {
        pAppWindow->ShowWindowFromTopToBottom(bShow);
        return true;
    }
    return false;
}

//针对移动显示的窗口 移回原本的位置
bool CWindowManager::ShowWindowInitLocation(LPCTSTR lpstrName)
{
	Window* pAppWindow = Find(lpstrName);
	if ( pAppWindow != NULL )
	{
		pAppWindow->ShowWindowInitLocation();
		return true;
	}
	return false;
}

bool CWindowManager::BringWindowTop(LPCTSTR lpstrName)
{
	Window* pAppWindow = Find(lpstrName);
	if ( pAppWindow != NULL )
	{
		::SetForegroundWindow( pAppWindow->GetHWND() );
		return true;
	}
	return false;
}

bool CWindowManager::DoCase(LPCTSTR lpstrName, LPCTSTR lpstrCaseName)
{
	Window* pAppWindow = Find(lpstrName);
	if ( pAppWindow != NULL )
	{
		pAppWindow->m_pm.DoCase(lpstrCaseName);
		return true;
	}
	return false;
}

bool CWindowManager::IsWindowVisible( LPCTSTR lpstrName)
{
	Window *pWnd = GetWindow(lpstrName);
	bool bVis = false;
	if (pWnd != NULL)
	{
		bVis = pWnd->IsWindowVisible();
	}
	return bVis;
}

void CWindowManager::ShowWindowMinsize(LPCTSTR lpstrName)
{
    Window *pWnd = GetWindow(lpstrName);
    if (pWnd != NULL)
    {
        ::ShowWindow(pWnd->GetHWND(),SW_MINIMIZE);
    }
}

bool CWindowManager::IsWindowMinsize(LPCTSTR lpstrName)
{
    Window *pWnd = GetWindow(lpstrName);
    if (pWnd != NULL)
    {
        return ::IsIconic(pWnd->GetHWND());
    }
    return false;
}

} // namespace AppFrame end 