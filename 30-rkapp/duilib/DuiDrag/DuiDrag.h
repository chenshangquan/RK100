#pragma once
#include "DragInterface.h"
#include "DragDef.h"
namespace DuiLib{
class CVerticalLayoutUI;
class CHorizontalLayoutUI;
class CContainerUI;
class CTreeNodeUI;
class CTreeViewUI;
//定义拖拽控件的相关数据 by zh.
class UILIB_API CDuiDragControlUI
{
public:
	CDuiDragControlUI();
	~CDuiDragControlUI();
	//添加拖放支持   add by zh. 20130822  
	virtual bool IsDrop() const;
	virtual void SetDrop(bool bDrop);
	virtual bool IsDrag() const;
	virtual void SetDrag(bool bDrag);
	virtual LPCTSTR GetDropData() const;
	virtual void SetDropData(LPCTSTR lpData);
    virtual void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

	//拖拽“影子”属性自定义
	//自定义影子大小
	virtual void SetDragShadowSize(SIZE szShadow);             
	virtual SIZE GetDragShadowSize();
	 //自定义影子背景，HBITMAP由控件释放
	virtual void SetDragShadowBmp(HBITMAP hBmp);          
	virtual HBITMAP GetDragShadowBmp();


	virtual void SetDragWndAlpha(byte byWndAlpha);
	virtual byte GetDragWndAlpha();

	//设置/获取是否自动响应
	virtual void SetAutoRespond(bool bAuto);
	virtual bool GetAutoRespond();
	//设置虚拟控件的属性(大小/背景/边距颜色)
	virtual void SetVirtualCtrlSize(SIZE szCtrl);
	virtual SIZE GetVirtualCtrlSize();
	virtual void SetVirtualCtrlBkColor(DWORD dwColor);
	virtual DWORD GetVirtualCtrlBkColor();
	virtual void SetVirtualCtrlPadding(RECT rcPadding);
	virtual RECT GetVirtualCtrlPadding();
	virtual void DoEvent(TEventUI& event);
	//这一类函数后边提到一个外部类
	//获取光标在布局中的索引
	int GetVVirtualIdx( CVerticalLayoutUI *pList ,POINT pt);
	int GetHVirtualIdx( CHorizontalLayoutUI *pList ,POINT pt);
	CTreeNodeUI* GetTreeNode( CTreeViewUI *pTree, POINT pt );

protected:
	virtual void OnDragEnter();
	virtual void OnDragMove(CControlUI *pSourceCtrl, POINT pt);
	virtual void OnDragLeave();
	//设置虚拟控件
	void SetVirtualControl( int nIdx, CContainerUI *pContainer, CControlUI *pSourceCtrl );
	CControlUI *m_pVirtualCtrl;
protected:
	SIZE m_szDragShadow;
	SIZE m_szVirtualCtrl;
	DWORD m_dwVirtualColor;
	CDuiRect	m_rcVirtualPadding;
	CDuiString m_sDropData;
	HBITMAP m_hDragShawdowBmp;
	bool m_bDrag;
	bool m_bDrop;
	bool m_bAutoRespond;			//是否自动响应拖拽
	byte m_byAlpha;                 //设置拖拽窗口的透明度
};

//该类的目的是自动初始化拖拽相关模块
class CDuiDrag{
protected:
	CDuiDrag(){InitDuiDrag();}
	~CDuiDrag(){FreeDuiDrag();}
	void InitDuiDrag();
	void FreeDuiDrag();
	static CDuiDrag s_cDuiDrag;
};
IDragDataMgr* GetDragDataMgr();
}

