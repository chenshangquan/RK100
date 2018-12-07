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
	���ڹ����࣬��Ҫ���𴰿ڵ���ʾ�����ء����ء�����
*/
class CWindowManager : public IWindowManager, public tmplContainer<tstring,CAppWindow*>
{
public:
	static const tstring strIndexName;	// ���������ļ�����
	static const tstring strFileTag;		// �ļ�·����ǩ
	static const tstring strParentTag;	// �ļ�·����ǩ
	static const tstring strLogicTag;	// logic��ǩ
	static const tstring strStyleTag;	// ��������
	static const tstring strChildStyle;
	static const tstring strDialogStyle;
	static const tstring strFrameStyle;
	static const tstring strToolStyle;//����Ľ���Ĵ���
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

	//����ƶ���ʾ�Ĵ��� �ƻ�ԭ����λ�� dyy 
	bool CWindowManager::ShowWindowInitLocation(LPCTSTR lpstrName);

	//���������ʾ dyy  2015-10-8
	bool CWindowManager::BringWindowTop(LPCTSTR lpstrName);

	virtual bool DoCase(LPCTSTR lpstrName, LPCTSTR lpstrCaseName);

	//�����Ƿ�ɼ� dyy 2015-5-4
	virtual bool IsWindowVisible(LPCTSTR lpstrName);

    //������С��
    virtual void ShowWindowMinsize(LPCTSTR lpstrName);
    virtual bool IsWindowMinsize(LPCTSTR lpstrName);
protected:
/** Ϊ�������observer 
 *  @param[in] 
 *  @node 
 *  @return �Ƿ�ɹ�
 */
	bool AddNotifier(Window* pWnd, LPCTSTR lpstrName);

/*  ��ԴZIP����Ŀ¼
*/
	tstring m_strZipPath;
};

} // namespace AppFrame end 

#endif // !defined(AFX_UIMANAGER_H__564A6AE2_AB5E_4103_ADF1_2186C00697C3__INCLUDED_)
