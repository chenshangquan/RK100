#pragma once
namespace DuiLib{
class CDragWnd : public CWindowWnd, public INotifyUI
{
	friend class CDragController;
protected:
	CDragWnd(CControlUI* pControl, POINT &pt);
	~CDragWnd();
	LPCTSTR GetWindowClassName() const { return _T("CDragWnd"); };
	UINT GetClassStyle() const { return CS_DBLCLKS ; };
	void OnFinalMessage(HWND /*hWnd*/) { delete this; }
	void Move(POINT &pt);
	void Notify(TNotifyUI& msg){}
	void SetSourceCtrl(CControlUI *pCtrl);
	bool IsVisible();
protected:
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	void Create(POINT &pt);
	void Init();
	//¿Ø¼þ½ØÍ¼
	HBITMAP GetCtrlShoot();
	CControlUI* m_pSourceControl;
	CPaintManagerUI m_pm;
	SIZE m_szShadowSize;
	HBITMAP m_hShadowBmp;
};
}


