#pragma once
#include "DragInterface.h"
#include "DragDef.h"
namespace DuiLib{
class CVerticalLayoutUI;
class CHorizontalLayoutUI;
class CContainerUI;
class CTreeNodeUI;
class CTreeViewUI;
//������ק�ؼ���������� by zh.
class UILIB_API CDuiDragControlUI
{
public:
	CDuiDragControlUI();
	~CDuiDragControlUI();
	//����Ϸ�֧��   add by zh. 20130822  
	virtual bool IsDrop() const;
	virtual void SetDrop(bool bDrop);
	virtual bool IsDrag() const;
	virtual void SetDrag(bool bDrag);
	virtual LPCTSTR GetDropData() const;
	virtual void SetDropData(LPCTSTR lpData);
    virtual void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

	//��ק��Ӱ�ӡ������Զ���
	//�Զ���Ӱ�Ӵ�С
	virtual void SetDragShadowSize(SIZE szShadow);             
	virtual SIZE GetDragShadowSize();
	 //�Զ���Ӱ�ӱ�����HBITMAP�ɿؼ��ͷ�
	virtual void SetDragShadowBmp(HBITMAP hBmp);          
	virtual HBITMAP GetDragShadowBmp();


	virtual void SetDragWndAlpha(byte byWndAlpha);
	virtual byte GetDragWndAlpha();

	//����/��ȡ�Ƿ��Զ���Ӧ
	virtual void SetAutoRespond(bool bAuto);
	virtual bool GetAutoRespond();
	//��������ؼ�������(��С/����/�߾���ɫ)
	virtual void SetVirtualCtrlSize(SIZE szCtrl);
	virtual SIZE GetVirtualCtrlSize();
	virtual void SetVirtualCtrlBkColor(DWORD dwColor);
	virtual DWORD GetVirtualCtrlBkColor();
	virtual void SetVirtualCtrlPadding(RECT rcPadding);
	virtual RECT GetVirtualCtrlPadding();
	virtual void DoEvent(TEventUI& event);
	//��һ�ຯ������ᵽһ���ⲿ��
	//��ȡ����ڲ����е�����
	int GetVVirtualIdx( CVerticalLayoutUI *pList ,POINT pt);
	int GetHVirtualIdx( CHorizontalLayoutUI *pList ,POINT pt);
	CTreeNodeUI* GetTreeNode( CTreeViewUI *pTree, POINT pt );

protected:
	virtual void OnDragEnter();
	virtual void OnDragMove(CControlUI *pSourceCtrl, POINT pt);
	virtual void OnDragLeave();
	//��������ؼ�
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
	bool m_bAutoRespond;			//�Ƿ��Զ���Ӧ��ק
	byte m_byAlpha;                 //������ק���ڵ�͸����
};

//�����Ŀ�����Զ���ʼ����ק���ģ��
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

