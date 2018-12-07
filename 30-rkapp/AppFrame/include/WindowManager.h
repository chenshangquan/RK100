// UIManager.h: interface for the CUIManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UIMANAGER_H__564A6AE2_AB5E_4103_ADF1_2186C00697C3__INCLUDED_)
#define AFX_UIMANAGER_H__564A6AE2_AB5E_4103_ADF1_2186C00697C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace AppFrame
{
/*
	窗口管理类，主要负责窗口的显示、隐藏、加载、销毁
*/
class CWindowManager : public IWindowManager, public tmplContainer<tstring,CAppWindow*>
{
public:
	static const tstring strIndexName;	// 窗口索引文件名称
	static const tstring strFileTag;		// 文件路径标签
	static const tstring strParentTag;	// 文件路径标签
	static const tstring strLogicTag;	// logic标签
	static const tstring strStyleTag;	// 窗口类型
	static const tstring strChildStyle;
	static const tstring strDialogStyle;
	static const tstring strFrameStyle;
	static const tstring strToolStyle;//捕获的焦点的窗口
public:
	CWindowManager();
	virtual ~CWindowManager();
public:
	virtual void SetResourcePath(LPCTSTR lpstrFile);
	virtual bool ShowWindowCenter(LPCTSTR lpstrName);
	virtual bool ShowWindow(LPCTSTR lpstrName, bool bShow = true);
	virtual bool HideWindow(LPCTSTR lpstrName);
	virtual bool ShowModal(LPCTSTR lpstrName, LPCTSTR lpstrParentWindow = _T("") );
    virtual u8 ShowModalGetRe(LPCTSTR lpstrName, LPCTSTR lpstrParentWindow = _T("") );
	virtual bool CloseWindow(LPCTSTR lpstrName, UINT nRet = IDOK);
	virtual Window* GetWindow(LPCTSTR lpstrName);
	virtual Window* NewWindow(LPCTSTR lpstrWindowName, LPCTSTR lpstrWindowMould, HWND hParentWnd,
							   DWORD dwStyle, DWORD dwExStyle, LPVOID lpData = NULL,
							   int x = CW_USEDEFAULT, int y = CW_USEDEFAULT,
							   int cx = CW_USEDEFAULT, int cy = CW_USEDEFAULT);
	virtual Window* NewWindow(LPCTSTR lpstrWindowName, LPCTSTR lpstrWindowMould, LPCTSTR lpstrParentWindow,
							   DWORD dwStyle, DWORD dwExStyle, LPVOID lpData = NULL,
							   int x = CW_USEDEFAULT, int y = CW_USEDEFAULT,
							   int cx = CW_USEDEFAULT, int cy = CW_USEDEFAULT );
	virtual Control* GetControl(LPCTSTR lpstrWindow, LPCTSTR lpstrControl);

	virtual bool ShowWindowFromLeftToRight(LPCTSTR lpstrName, bool bShow = true );
	virtual bool ShowWindowFromBottomToTop(LPCTSTR lpstrName, bool bShow = true );
    virtual bool ShowWindowFromTopToBottom(LPCTSTR lpstrName, bool bShow = true);

    virtual bool ShowMainWindowLeftToRight(LPCTSTR lpstrName, bool bShow = true);

	//针对移动显示的窗口 移回原本的位置 dyy 
	bool CWindowManager::ShowWindowInitLocation(LPCTSTR lpstrName);

	//窗口最顶端显示 dyy  2015-10-8
	bool CWindowManager::BringWindowTop(LPCTSTR lpstrName);

	virtual bool DoCase(LPCTSTR lpstrName, LPCTSTR lpstrCaseName);

	//窗口是否可见 dyy 2015-5-4
	virtual bool IsWindowVisible(LPCTSTR lpstrName);

    //窗口最小化
    virtual void ShowWindowMinsize(LPCTSTR lpstrName);
    virtual bool IsWindowMinsize(LPCTSTR lpstrName);
protected:
/** 为窗口添加observer 
 *  @param[in] 
 *  @node 
 *  @return 是否成功
 */
	bool AddNotifier(Window* pWnd, LPCTSTR lpstrName);

/*  资源ZIP所在目录
*/
	tstring m_strZipPath;
};

} // namespace AppFrame end 

#endif // !defined(AFX_UIMANAGER_H__564A6AE2_AB5E_4103_ADF1_2186C00697C3__INCLUDED_)
